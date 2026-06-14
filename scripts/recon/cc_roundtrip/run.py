#!/usr/bin/env python3
"""M6 preflight — cc-roundtrip vs decomp.me.

For each probe under this directory:

1. Compile locally through `scripts/ee-cc-wrap.py -O2 -G0 -c`
   (which drives `cpp0 → cc1 → ee-as` directly).
2. Extract `.text` bytes via `mipsel-linux-gnu-objcopy -O binary`.
3. Create a decomp.me scratch with the same source, compiler
   `ee-gcc2.96`, flags `-O2 -G0`.  decomp.me's preset invokes
   the upstream `ee-gcc` driver.
4. GET the compiled `.o` from decomp.me (`right_object`,
   base64-encoded), extract its `.text` bytes the same way.
5. Compare.  Exit 0 on byte-equality for every probe, non-zero
   if any probe diverges.

Run from the repo root::

    python scripts/recon/cc_roundtrip/run.py [--keep-tmp] [--no-network]

`--no-network` skips the decomp.me round-trip and only prints the
local `.text` bytes — useful when you've already captured a
reference and just want to re-verify the local side.

`--keep-tmp` preserves the temp working dir for inspection.
The scratch slugs (`https://decomp.me/scratch/<slug>`) are
printed so they're recoverable for the M6 note.

This script is part of the M6-preflight-cc-roundtrip task.
It is not invoked by `compile.py` or any session sub-check —
it's a one-shot preflight gate.
"""
from __future__ import annotations

import argparse
import base64
import hashlib
import json
import shutil
import subprocess
import sys
import tempfile
import time
import urllib.error
import urllib.request
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
SCRIPTS = ROOT / "scripts"
PROBE_DIR = Path(__file__).resolve().parent
EE_CC_WRAP = SCRIPTS / "ee-cc-wrap.py"

DECOMPME_API = "https://decomp.me/api"
# Cloudflare in front of decomp.me rejects unidentified UAs on some
# read paths; a browser-shaped UA + Origin/Referer is sufficient.
HTTP_HEADERS = {
    "Content-Type": "application/json",
    "Accept": "application/json",
    "User-Agent": (
        "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 "
        "(KHTML, like Gecko) Chrome/120.0 Safari/537.36 "
        "godhand-recomp/M6-preflight"
    ),
    "Origin": "https://decomp.me",
}

# Target asm placeholder.  decomp.me's scratch model requires either
# `target_asm` or `target_obj`; we don't care about the diff against
# this — we only consume `right_object` (our compilation).  Any valid
# MIPS asm works; we pick one that matches the trivial probes so the
# diff happens to be 100% for both, which makes the response sane
# but is not load-bearing here.
TARGET_ASM_LEAF = "\n".join([
    "leaf_identity:",
    "    jr $ra",
    "    move $v0, $a0",
    "",
])
TARGET_ASM_SUM = "\n".join([
    "sum_two:",
    "    jr $ra",
    "    addu $v0, $a0, $a1",
    "",
])


PROBES = [
    {
        "name": "leaf_identity",
        "diff_label": "leaf_identity",
        "target_asm": TARGET_ASM_LEAF,
        "expected_disasm": "jr $ra; move $v0, $a0",
    },
    {
        "name": "sum_two",
        "diff_label": "sum_two",
        "target_asm": TARGET_ASM_SUM,
        "expected_disasm": "jr $ra; addu $v0, $a0, $a1",
    },
]


def run(cmd, **kw):
    """Subprocess wrapper that surfaces stderr on failure."""
    res = subprocess.run(cmd, capture_output=True, text=True, **kw)
    if res.returncode != 0:
        sys.stderr.write(f"[run.py] command failed: {' '.join(map(str, cmd))}\n")
        sys.stderr.write(res.stdout)
        sys.stderr.write(res.stderr)
        sys.exit(res.returncode)
    return res


def local_compile(probe_c: Path, out_o: Path) -> bytes:
    """Compile a probe through ee-cc-wrap.py and return its .text bytes."""
    run([
        sys.executable, str(EE_CC_WRAP),
        "-c", "-O2", "-G0",
        "-o", str(out_o),
        str(probe_c),
    ])
    text_bin = out_o.with_suffix(".text.bin")
    run([
        "mipsel-linux-gnu-objcopy",
        "-O", "binary", "--only-section=.text",
        str(out_o), str(text_bin),
    ])
    return text_bin.read_bytes()


def decompme_create_scratch(probe: dict, source_code: str) -> str:
    """POST /api/scratch and return the slug."""
    payload = {
        "compiler": "ee-gcc2.96",
        "platform": "ps2",
        "compiler_flags": "-O2 -G0",
        "target_asm": probe["target_asm"],
        "diff_label": probe["diff_label"],
        "source_code": source_code,
        "context": "",
    }
    req = urllib.request.Request(
        f"{DECOMPME_API}/scratch",
        data=json.dumps(payload).encode(),
        headers=HTTP_HEADERS,
        method="POST",
    )
    with urllib.request.urlopen(req, timeout=30) as resp:
        d = json.loads(resp.read().decode())
    return d["slug"]


def decompme_compile(slug: str) -> tuple[bytes, str]:
    """POST /api/scratch/<slug>/compile?include_objects=true.

    Returns (compiled_object_bytes, compiler_output_for_diagnostics).
    """
    headers = dict(HTTP_HEADERS)
    headers["Referer"] = f"https://decomp.me/scratch/{slug}"
    req = urllib.request.Request(
        f"{DECOMPME_API}/scratch/{slug}/compile",
        data=json.dumps({"include_objects": True}).encode(),
        headers=headers,
        method="POST",
    )
    with urllib.request.urlopen(req, timeout=60) as resp:
        d = json.loads(resp.read().decode())
    if not d.get("success"):
        raise RuntimeError(f"decomp.me compile failed for {slug}: {d.get('compiler_output')}")
    obj = base64.b64decode(d["right_object"])
    if obj[:4] != b"\x7fELF":
        raise RuntimeError(f"decomp.me right_object not ELF: {obj[:8].hex()}")
    return obj, d.get("compiler_output", "")


def extract_text(o_path: Path) -> bytes:
    text_bin = o_path.with_suffix(".text.bin")
    run([
        "mipsel-linux-gnu-objcopy",
        "-O", "binary", "--only-section=.text",
        str(o_path), str(text_bin),
    ])
    return text_bin.read_bytes()


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--keep-tmp", action="store_true", help="preserve scratch tempdir")
    ap.add_argument("--no-network", action="store_true",
                    help="only compile locally, print bytes, exit")
    args = ap.parse_args()

    tmp = Path(tempfile.mkdtemp(prefix="ccprobe-"))
    print(f"[run.py] tmp dir: {tmp}")

    all_ok = True
    results = []
    for probe in PROBES:
        name = probe["name"]
        probe_c = PROBE_DIR / f"{name}.c"
        if not probe_c.is_file():
            print(f"[run.py] {name}: source missing at {probe_c}", file=sys.stderr)
            all_ok = False
            continue
        source_code = probe_c.read_text()

        # Local
        local_o = tmp / f"{name}.local.o"
        local_text = local_compile(probe_c, local_o)
        print(f"\n=== {name} ({probe['expected_disasm']}) ===")
        print(f"  source bytes: {len(source_code)}")
        print(f"  local .text:    {local_text.hex(' ')} ({len(local_text)} B)")

        if args.no_network:
            results.append((name, local_text, None, None, None))
            continue

        # decomp.me
        try:
            slug = decompme_create_scratch(probe, source_code)
            # Tiny pause so we don't hammer Cloudflare.  The compile
            # endpoint serializes on the backend anyway.
            time.sleep(0.5)
            decomp_o_bytes, compiler_output = decompme_compile(slug)
        except urllib.error.HTTPError as e:
            print(f"  [decomp.me] HTTP {e.code}: {e.read().decode()[:300]}", file=sys.stderr)
            all_ok = False
            results.append((name, local_text, None, None, None))
            continue
        except Exception as e:
            print(f"  [decomp.me] {type(e).__name__}: {e}", file=sys.stderr)
            all_ok = False
            results.append((name, local_text, None, None, None))
            continue

        decomp_o = tmp / f"{name}.decompme.o"
        decomp_o.write_bytes(decomp_o_bytes)
        decomp_text = extract_text(decomp_o)

        scratch_url = f"https://decomp.me/scratch/{slug}"
        print(f"  decomp.me URL:  {scratch_url}")
        print(f"  decomp.me .text:{decomp_text.hex(' ')} ({len(decomp_text)} B)")
        if compiler_output.strip():
            print(f"  decomp.me cc output: {compiler_output.strip()!r}")

        match = local_text == decomp_text
        print(f"  → {'✅ MATCH' if match else '❌ DIFFER'}")
        if not match:
            all_ok = False
        results.append((name, local_text, decomp_text, scratch_url, match))

    print("\n=== Summary ===")
    for r in results:
        name, lt, dt, url, match = r
        if dt is None:
            print(f"  {name:16s} local={lt.hex()} [no decomp.me reference]")
        else:
            mark = "✅" if match else "❌"
            print(f"  {mark} {name:16s} {lt.hex()}  ({url})")

    if not args.keep_tmp:
        shutil.rmtree(tmp, ignore_errors=True)
    else:
        print(f"\n[run.py] kept tmp dir at {tmp}")

    return 0 if all_ok else 1


if __name__ == "__main__":
    sys.exit(main())
