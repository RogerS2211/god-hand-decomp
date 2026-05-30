#!/usr/bin/env python3
"""Inventory the 39 .DVP.overlay payloads.

Walks `bin/elf_metadata/sec*_DVP_overlay*.bin` and reports a per-payload
table:

    idx | name (from ovlytab)              | size | elf? | sha256(8) | first_nonzero

For non-ELF payloads (the universal case so far observed — all overlays
start with leading zeros, consistent with VU microcode load images) we
record file size, the truncated sha256 fingerprint, and the offset +
hex of the first non-zero stretch, since the leading zeros make a raw
"first 32 bytes" fingerprint uninformative.

The .DVP.ovlytab descriptor (39 × 12 B entries) is parsed to map each
overlay section name to its (name_offset_in_strtab, addr_b, addr_c)
descriptor; these fields are tentatively interpreted as
(EE-virtual load address, VU-microcode local address) based on the
naming convention `.DVP.overlay..0x<c>.<namehash>.<count>.<chunk>`
embedded in the section names.  Confirmation of the precise semantics
is later work; here we are pure recon.

Pure read-only.  Output is a Markdown table written to stdout.
"""

from __future__ import annotations

import hashlib
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
META = ROOT / "bin" / "elf_metadata"


def _first_nonzero(data: bytes, span: int = 16) -> str:
    for i, b in enumerate(data):
        if b != 0:
            chunk = data[i : i + span]
            hexs = " ".join(f"{c:02x}" for c in chunk)
            return f"@0x{i:x}: {hexs}"
    return "(all zeros)"


def main() -> int:
    manifest_path = META / "manifest.json"
    if not manifest_path.exists():
        sys.stderr.write(f"missing {manifest_path}\n")
        return 2
    manifest = json.loads(manifest_path.read_text())

    # Find ovlytab + ovlystrtab payloads.
    ovlytab_path = ovlystrtab_path = None
    overlay_sections = []
    for s in manifest["sections"]:
        if s["name"] == ".DVP.ovlytab":
            ovlytab_path = ROOT / s["payload"]
        elif s["name"] == ".DVP.ovlystrtab":
            ovlystrtab_path = ROOT / s["payload"]
        elif s["name"].startswith(".DVP.overlay"):
            overlay_sections.append(s)

    if ovlytab_path is None or ovlystrtab_path is None:
        sys.stderr.write("manifest missing ovlytab/ovlystrtab\n")
        return 2

    ovlytab = ovlytab_path.read_bytes()
    strtab = ovlystrtab_path.read_bytes()
    n_entries = len(ovlytab) // 12
    print(f"<!-- gap-g: {n_entries} overlay descriptors, "
          f"ovlytab={len(ovlytab)} B, strtab={len(strtab)} B -->")
    print()
    print("| idx | name                                   | size  | elf? | "
          "load_b      | vu_c   | sha256(8) | first non-zero |")
    print("|-----|----------------------------------------|-------|------|"
          "-------------|--------|-----------|----------------|")

    rows = 0
    for i in range(n_entries):
        name_off, addr_b, addr_c = struct.unpack(
            "<3I", ovlytab[i * 12 : (i + 1) * 12]
        )
        end = strtab.find(b"\x00", name_off)
        name = strtab[name_off:end].decode("ascii", "replace")
        # Find matching payload file via manifest.
        match = None
        for s in overlay_sections:
            if s["name"] == name:
                match = s
                break
        if match is None:
            # Some overlays have ' ' / ',' differences in the manifest;
            # match leniently on suffix.
            for s in overlay_sections:
                if s["name"].endswith(name.split(".overlay.", 1)[-1]):
                    match = s
                    break
        if match is None:
            short = name.replace(".DVP.overlay.", "").replace(".", "_")
            print(
                f"| {i:>3} | {name[:38]:<38} | (n/a) |  -   | "
                f"0x{addr_b:09x} | 0x{addr_c:04x} | (no file) | -- |"
            )
            continue
        path = ROOT / match["payload"]
        data = path.read_bytes()
        size = len(data)
        is_elf = data[:4] == b"\x7fELF"
        sha = hashlib.sha256(data).hexdigest()[:8]
        fnz = _first_nonzero(data, span=12)
        # Trim name for column width.
        short = name.replace(".DVP.overlay..", "").strip()
        print(
            f"| {i:>3} | {short:<38.38} | {size:>5} | "
            f"{'yes' if is_elf else 'no':>4} | "
            f"0x{addr_b:09x} | 0x{addr_c:04x} | {sha:>9} | {fnz:<14.40} |"
        )
        rows += 1

    print()
    n_elf = sum(
        1 for s in overlay_sections
        if (ROOT / s["payload"]).read_bytes()[:4] == b"\x7fELF"
    )
    total = len(overlay_sections)
    total_bytes = sum(
        (ROOT / s["payload"]).stat().st_size for s in overlay_sections
    )
    print(f"<!-- summary: {total} overlay payloads, "
          f"{n_elf} are ELF, {total - n_elf} are raw payloads "
          f"(VU microcode load images), {total_bytes} B total -->")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
