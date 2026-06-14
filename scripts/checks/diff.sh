#!/usr/bin/env bash
# diff sub-check.
#
# Mechanically enforces the third clause of the per-function diff gate:
#
#     per-function diff reachable via
#       `tools/objdiff-cli diff -p . -u <unit> <symbol>`.
#
# Clauses 1 and 2 of the gate are already session-checked:
#     1. carved_funcs non-empty — inspection at session_check time
#     2. ELF byte-equality vs retail — `scripts/checks/build.sh`
#
# The third clause was not — a future `objdiff-cli` bump that broke
# the diff-CLI invocation shape would slip past the harness until a
# human ran the diff manually.  This sub-check pins the invocation:
# it pulls the first entry from `compile_config.json::carved_funcs`,
# derives its objdiff unit name, and asks `objdiff-cli diff` to emit
# a JSON report to /dev/null.  Exit code 0 = the CLI surface is
# intact; we deliberately do **not** parse the diff JSON (the bytes
# are scored by `score.sh`, this check is about CLI surface stability).
#
# Unit derivation: if the carve has a `tu:` field (TU-owned carve,
# the universal shape), strip the C/C++ extension to get the objdiff
# unit name (e.g. "src/cod/000000.c" → "src/cod/000000").
# Otherwise fall back to the `unit` field verbatim.  The TU-first
# rule is what every live carve uses today and is what the
# worked example pinned ("src/cod/000000" for func_00100000); the
# fallback exists so a future asm-only carve (no C wrapper) still
# diffs against the standalone `build/asm/nonmatching/<name>.o`.
#
# Diffing only the **first** carve is deliberate: the gate clause is
# about the CLI surface, not coverage.  If the first carve diffs
# cleanly, the invocation shape is intact; iterating all 19 carves
# would add wall time without proportional value (the bytes are
# already in the `score` ratchet).
#
# Skip semantics (exit 77):
#   - tools/objdiff-cli missing            (fresh clone, pre-toolchain)
#   - objdiff.json missing                 (pre `compile.py --setup`)
#   - compile_config.json::carved_funcs    is empty (rollback / fresh)
#   - build/<unit>.o missing               (build hasn't run yet — `build`
#                                          sub-check runs before us and
#                                          will have failed loudly)
#
# Fail (exit 1):
#   - objdiff-cli exits non-zero, with the full stderr surfaced and a
#     `objdiff-cli diff failed for <unit>/<symbol>` lead line.
#
# Documented in the session-check notes (§ "12. `diff.sh`").
set -uo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "$ROOT"

CLI="$ROOT/tools/objdiff-cli"
CONFIG="$ROOT/objdiff.json"
CARVE_CFG="$ROOT/compile_config.json"

if [[ ! -x "$CLI" ]]; then
    echo "tools/objdiff-cli missing — run scripts/setup_toolchain.sh."
    exit 77
fi
if [[ ! -f "$CONFIG" ]]; then
    echo "objdiff.json missing — run: python compile.py --setup."
    exit 77
fi
if [[ ! -f "$CARVE_CFG" ]]; then
    echo "compile_config.json missing."
    exit 1
fi

# Pull (symbol, unit) for the first carved_funcs entry.  Empty list
# is a clean skip (we tolerate it during fresh-clone / milestone-
# rollback even though live development never has it).
read_first_carve=$(
    python3 - <<'PY'
import json, sys
try:
    with open("compile_config.json") as fh:
        cfg = json.load(fh)
except Exception as exc:
    print(f"__error__\t{exc}")
    sys.exit(0)

carves = cfg.get("carved_funcs", [])
# Defensive: filter out non-dict entries (e.g. comment shims).
carves = [c for c in carves if isinstance(c, dict) and c.get("name")]
if not carves:
    print("__empty__")
    sys.exit(0)

first = carves[0]
name = first.get("name", "")
tu = first.get("tu", "")
unit_field = first.get("unit", "")

# TU-owned carve (the universal shape): the symbol's
# objdiff unit is the C TU stripped of its C/C++ source extension.
# Fallback: the `unit` field verbatim (asm-only carves with no C
# wrapper).
if tu:
    for ext in (".cpp", ".cc", ".c"):
        if tu.endswith(ext):
            unit = tu[: -len(ext)]
            break
    else:
        unit = tu
else:
    unit = unit_field

print(f"{name}\t{unit}")
PY
)

case "$read_first_carve" in
    __error__*)
        err="${read_first_carve#__error__$'\t'}"
        echo "error reading compile_config.json: $err"
        exit 1
        ;;
    __empty__)
        echo "compile_config.json::carved_funcs is empty — nothing to diff."
        echo "(live development should never see this; tolerated during"
        echo " fresh-clone / milestone-rollback.)"
        exit 77
        ;;
esac

IFS=$'\t' read -r symbol unit <<<"$read_first_carve"

if [[ -z "$symbol" || -z "$unit" ]]; then
    echo "could not derive (symbol, unit) from carved_funcs[0]"
    echo "  raw: $read_first_carve"
    exit 1
fi

# The unit's base .o must exist or objdiff has nothing to diff
# against.  In normal session_check ordering `build` runs before
# `diff`, so if we land here without a .o the build sub-check is
# already FAILED — but emit a clear skip just in case the operator
# invoked us standalone.
BASE_O="$ROOT/build/${unit}.o"
if [[ ! -f "$BASE_O" ]]; then
    echo "build/${unit}.o missing — run \`python compile.py\` first."
    exit 77
fi

# Invoke objdiff-cli diff.  `-o /dev/null --format json` makes the
# CLI emit a structured report it would otherwise render to a TTY;
# we discard the bytes — exit code is the truth.  Warnings on stderr
# (e.g. "Failed to parse MIPS mdebug line info") are tolerated; the
# CLI still exits 0 in that case.
out=$("$CLI" diff -p . -u "$unit" "$symbol" -o /dev/null --format json 2>&1)
rc=$?

if [[ $rc -ne 0 ]]; then
    echo "objdiff-cli diff failed for ${unit}/${symbol} (rc=$rc):"
    printf "%s\n" "$out" | sed 's/^/    /'
    exit 1
fi

echo "objdiff-cli diff OK for ${unit}/${symbol}."
exit 0
