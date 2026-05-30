#!/usr/bin/env bash
# objdiff ratchet sub-check.
#
# Regenerates progress/report.json (via scripts/progress.sh) and
# compares matched_code / matched_data against progress/report.prev.json.
# Fails if either *byte count* regressed; passes (and updates
# report.prev.json) if the byte count rose or stayed equal.
#
# Why bytes and not percent: byte counts are exact integers; percent
# carries rounding error.  The ratchet must never trip on rounding.
#
# Skip semantics:
#   - if tools/objdiff-cli or objdiff.json is missing → exit 77.
#   - if no progress/report.prev.json exists (first run on this clone),
#     write it from the current report and pass.
set -uo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "$ROOT"

CLI="$ROOT/tools/objdiff-cli"
CONFIG="$ROOT/objdiff.json"
REPORT="$ROOT/progress/report.json"
PREV="$ROOT/progress/report.prev.json"

if [[ ! -x "$CLI" ]]; then
    echo "tools/objdiff-cli missing — run scripts/setup_toolchain.sh."
    exit 77
fi
if [[ ! -f "$CONFIG" ]]; then
    echo "objdiff.json missing — run: python compile.py --setup."
    exit 77
fi

# Regenerate the report (silent unless it fails).
if ! out=$("$ROOT/scripts/progress.sh" --quiet 2>&1); then
    echo "scripts/progress.sh failed:"
    printf "%s\n" "$out"
    exit 1
fi

if [[ ! -f "$REPORT" ]]; then
    echo "$REPORT was not produced."
    exit 1
fi

read_field() {
    # $1 = report path, $2 = field
    python3 - "$1" "$2" <<'PY'
import json, sys
with open(sys.argv[1]) as fh:
    m = json.load(fh).get("measures", {})
v = m.get(sys.argv[2], 0)
# objdiff writes byte counts as strings; coerce to int.
try:
    print(int(v))
except (TypeError, ValueError):
    print(0)
PY
}

cur_code=$(read_field "$REPORT" matched_code)
cur_data=$(read_field "$REPORT" matched_data)
cur_tot_code=$(read_field "$REPORT" total_code)
cur_tot_data=$(read_field "$REPORT" total_data)

# Pretty percent (4dp), for output only.
pct() {
    python3 -c "n,d=$1,$2; print(f'{0.0 if d==0 else 100.0*n/d:.4f}')"
}
cur_code_pct=$(pct "$cur_code" "$cur_tot_code")
cur_data_pct=$(pct "$cur_data" "$cur_tot_data")

if [[ ! -f "$PREV" ]]; then
    cp "$REPORT" "$PREV"
    echo "no progress/report.prev.json — seeded baseline."
    echo "  matched_code = $cur_code / $cur_tot_code bytes  ($cur_code_pct %)"
    echo "  matched_data = $cur_data / $cur_tot_data bytes  ($cur_data_pct %)"
    exit 0
fi

prev_code=$(read_field "$PREV" matched_code)
prev_data=$(read_field "$PREV" matched_data)

fail=0
if (( cur_code < prev_code )); then
    echo "matched_code REGRESSED: $cur_code < $prev_code bytes"
    fail=1
fi
if (( cur_data < prev_data )); then
    echo "matched_data REGRESSED: $cur_data < $prev_data bytes"
    fail=1
fi
if [[ $fail -ne 0 ]]; then
    exit 1
fi

# Only update prev when current is *higher*.
if (( cur_code > prev_code )) || (( cur_data > prev_data )); then
    cp "$REPORT" "$PREV"
    echo "ratchet advanced — progress/report.prev.json updated."
fi

echo "matched_code = $cur_code bytes ($cur_code_pct %)  prev=$prev_code"
echo "matched_data = $cur_data bytes ($cur_data_pct %)  prev=$prev_data"
exit 0
