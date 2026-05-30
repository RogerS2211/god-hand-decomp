#!/usr/bin/env bash
# Generate progress/report.json via objdiff-cli, then print a one-screen
# headline summary suitable for commit messages or the session-end
# ratchet harness.
#
# Usage:
#     scripts/progress.sh           # regenerate + print summary
#     scripts/progress.sh --quiet   # regenerate, print only matched_code_percent
#     scripts/progress.sh --no-regen   # use existing progress/report.json
#
# Wraps `tools/objdiff-cli report generate`.  No other state mutated; the
# only output on disk is progress/report.json.  All scoring conventions
# (NON_MATCHING markers, byte-level invariant elsewhere) are stable.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

OBJDIFF_CLI="$ROOT/tools/objdiff-cli"
REPORT="$ROOT/progress/report.json"
QUIET=0
REGEN=1

for arg in "$@"; do
    case "$arg" in
        --quiet)    QUIET=1 ;;
        --no-regen) REGEN=0 ;;
        -h|--help)
            sed -n '2,18p' "$0"
            exit 0
            ;;
        *)
            echo "unknown flag: $arg" >&2
            exit 2
            ;;
    esac
done

if [[ $REGEN -eq 1 ]]; then
    if [[ ! -x "$OBJDIFF_CLI" ]]; then
        echo "error: $OBJDIFF_CLI missing or not executable." >&2
        echo "  run scripts/setup_toolchain.sh to install it." >&2
        exit 1
    fi
    if [[ ! -f "$ROOT/objdiff.json" ]]; then
        echo "error: objdiff.json missing." >&2
        echo "  run: python compile.py --setup" >&2
        exit 1
    fi
    mkdir -p "$(dirname "$REPORT")"
    "$OBJDIFF_CLI" report generate -o "$REPORT" -f json-pretty >/dev/null 2>&1 \
        || { echo "objdiff-cli report generate failed" >&2; exit 1; }
fi

if [[ ! -f "$REPORT" ]]; then
    echo "error: $REPORT does not exist (re-run without --no-regen)." >&2
    exit 1
fi

# Pull headline numbers via python -- jq isn't a guaranteed dep here.
# Treat missing matched_* fields as 0 (objdiff omits them when nothing
# matches, which is exactly the zero-match baseline state).
read -r MATCHED_CODE TOTAL_CODE MATCHED_DATA TOTAL_DATA UNITS FUNCS \
    < <(python3 - "$REPORT" <<'PY'
import json, sys
with open(sys.argv[1]) as fh:
    m = json.load(fh).get("measures", {})
def num(k): return int(m.get(k, 0))
print(num("matched_code"), num("total_code"),
      num("matched_data"), num("total_data"),
      num("total_units"), num("total_functions"))
PY
)

pct() { python3 -c "n, d = $1, $2; print(f'{0.0 if d == 0 else 100.0 * n / d:.4f}')"; }

CODE_PCT="$(pct "$MATCHED_CODE" "$TOTAL_CODE")"
DATA_PCT="$(pct "$MATCHED_DATA" "$TOTAL_DATA")"

if [[ $QUIET -eq 1 ]]; then
    echo "$CODE_PCT"
    exit 0
fi

cat <<EOF
objdiff progress @ $(date -u +%Y-%m-%dT%H:%M:%SZ)
  units                 : $UNITS
  functions             : $FUNCS
  matched_code          : $MATCHED_CODE / $TOTAL_CODE bytes  ($CODE_PCT %)
  matched_data          : $MATCHED_DATA / $TOTAL_DATA bytes  ($DATA_PCT %)
  report                : $(realpath --relative-to="$ROOT" "$REPORT")
EOF
