#!/usr/bin/env python3
"""auto_carve_func.py — single-function auto-carve helper for
``scripts/match_and_commit.sh`` (Bug B, 2026-05-24).

The matched-but-uncarved path threads matched candidates through the
carve helpers in :mod:`scripts.carver` (:func:`_atomic_auto_carve` +
:func:`_auto_carve_uncarved`) before invoking
``integrate_match.py``.  That carve step writes:

  1. A new ``carved_funcs[]`` entry in ``compile_config.json``.
  2. An ``INCLUDE_ASM("nonmatching", <name>);`` line in the target TU.

Without those two writes, ``integrate_match.py`` rejects the match
with::

    integrate_match: no carve entry for '<name>' in compile_config.json;
    add one before integrating.

The worker-self-commit path (``.pi/agents/decomp-matcher.md`` ->
``scripts/match_and_commit.sh``) historically did NOT auto-carve,
which meant matched-but-uncarved candidates (e.g. cascade tier-4
``func_003B9F60``, 2026-05-23) would land as
``matched-but-not-committed, commit_rc: 2`` and require a manual
harvest.  This helper closes that gap: ``match_and_commit.sh`` now
calls it before ``integrate_match.py`` so the wrapper is autonomous
end-to-end.

Behaviour:

- Look up the candidate dict from ``progress/decomp_targets.json``
  (canonical source).  Fall back to ``prompts/<name>/settings.yaml``
  + best-effort defaults when the canonical corpus has aged out
  (mirrors ``scripts/harvest_bakeoff_matches.load_candidate_dict``).
- Idempotent: re-running on an already-carved function exits 0 with
  no writes (the underlying ``_auto_carve_uncarved`` returns
  ``"already_carved"``).
- Exit codes:

  * ``0`` — carve already present OR newly written; ``compile_config.json``
    + the TU now have what ``integrate_match.py`` needs.
  * ``2`` — candidate metadata could not be resolved (not in
    ``decomp_targets.json``, no usable ``prompts/<name>/settings.yaml``,
    etc.).  Stable rc so the bash caller can branch.
  * ``3`` — auto-carve raised :exc:`scripts.carver.CarveError` (I/O
    or structural failure).  The wrapper's ``cleanup_on_fail`` trap
    reverts any partial writes. (Pre-Phase 2 the carve primitive lived
    elsewhere; an earlier refactor moved it to `scripts.carver` and
    reclassified the exception class.)

Stdout: ``carved`` or ``already_carved`` on success, mirroring
:func:`_auto_carve_uncarved`'s return value (handy for the bash log).
Stderr: human-readable diagnostic on failure.
"""
from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

# Use the carver module's primitives as the single source of truth so
# this script stays in sync with the carving behaviour.  A later
# refactor moved the carve helpers to ``scripts.carver``; the import
# ``from scripts.carver import ...`` requires the **repo root** (parent
# of ``scripts/``) on ``sys.path`` so the ``scripts`` package is
# discoverable.  When ``match_and_commit.sh`` invokes us via
# ``python3 scripts/auto_carve_func.py NAME``, Python auto-prepends only
# ``scripts/`` to ``sys.path`` (the script's own directory), which is why
# the pre-extraction bare-module import worked but
# ``from scripts.carver`` does not without this insertion.  Discovered by
# the deferred-smoke validation when worker subprocesses hit
# ``ModuleNotFoundError: scripts``.  We insert ``ROOT`` first and keep
# ``ROOT / "scripts"`` for any legacy bare-module imports that may still
# live downstream.
sys.path.insert(0, str(ROOT))
sys.path.insert(1, str(ROOT / "scripts"))

DECOMP_TARGETS = ROOT / "progress" / "decomp_targets.json"
PROMPTS_DIR = ROOT / "prompts"


def _load_from_decomp_targets(name: str) -> dict | None:
    if not DECOMP_TARGETS.exists():
        return None
    try:
        data = json.loads(DECOMP_TARGETS.read_text())
    except (OSError, json.JSONDecodeError):
        return None
    for c in data.get("candidates", []) or []:
        if c.get("name") == name:
            return c
    return None


def _load_from_settings_yaml(name: str) -> dict | None:
    settings = PROMPTS_DIR / name / "settings.yaml"
    if not settings.exists():
        return None
    try:
        import yaml  # noqa: PLC0415
    except ImportError:
        return None
    try:
        s = yaml.safe_load(settings.read_text()) or {}
    except (OSError, yaml.YAMLError):
        return None
    asm = s.get("asm", "") or ""
    addr_hex = "0x00000000"
    for line in asm.splitlines():
        if "/*" in line and "*/" in line:
            try:
                parts = line.split("/*", 1)[1].split("*/", 1)[0].split()
                if len(parts) >= 2 and len(parts[1]) == 8:
                    int(parts[1], 16)
                    addr_hex = "0x" + parts[1]
                    break
            except (ValueError, IndexError):
                continue
    insns = sum(1 for ln in asm.splitlines() if "/*" in ln and "*/" in ln)
    size = max(insns * 4, 4)
    return {
        "name": name,
        "address": addr_hex,
        "size_bytes": size,
        "instruction_count": insns,
        "asm_module_path": s.get("targetObjectPath_asm")
            or "asm/cod/000000.s",
        "tier": "auto-carve-fallback",
        "shape_class": "",
    }


def load_candidate_dict(name: str) -> dict | None:
    cand = _load_from_decomp_targets(name)
    if cand is not None:
        return cand
    return _load_from_settings_yaml(name)


def main(argv: list[str]) -> int:
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("name", help="canonical function name, e.g. func_003B9F60")
    ap.add_argument(
        "--config",
        default=str(ROOT / "compile_config.json"),
        help="compile_config.json path (default: project root)",
    )
    args = ap.parse_args(argv)

    name = args.name.strip()
    if not name:
        print("auto_carve_func: empty FUNCTION_NAME", file=sys.stderr)
        return 2

    cand = load_candidate_dict(name)
    if cand is None:
        print(
            f"auto_carve_func: no candidate metadata for {name!r}; "
            f"not found in {DECOMP_TARGETS.name} or "
            f"{PROMPTS_DIR.name}/{name}/settings.yaml",
            file=sys.stderr,
        )
        return 2

    # Carving primitives now live in `scripts.carver`; this script
    # consumes the module's
    # `CarveSession.carve_one()` (behaviour-preserving — no internal
    # atomic wrap, the bash `cleanup_on_fail` trap in
    # `scripts/match_and_commit.sh` continues to handle worker-side
    # rollback). The exception class becomes `CarveError`.
    try:
        from scripts.carver import (  # noqa: PLC0415
            CarveSession,
            CarveError,
        )
    except ImportError as e:
        print(f"auto_carve_func: failed to import scripts.carver: {e}",
              file=sys.stderr)
        return 3

    session = CarveSession(root=ROOT)
    try:
        result = session.carve_one(
            name, cand, config_path=Path(args.config),
        )
    except CarveError as exc:
        print(f"auto_carve_func: {exc}", file=sys.stderr)
        return 3
    except Exception as exc:  # noqa: BLE001
        print(f"auto_carve_func: unexpected: {type(exc).__name__}: {exc}",
              file=sys.stderr)
        return 3

    print(result)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
