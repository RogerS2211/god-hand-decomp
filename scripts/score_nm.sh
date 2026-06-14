#!/usr/bin/env bash
# score_nm.sh — regenerate the NON_MATCHING *scored* report (two-build).
#
# The default `us` build keeps each unmatched function's `#else INCLUDE_ASM`
# fallback, so its linked ELF is byte-identical to retail (the sha256 ratchet).
# This scored build defines NON_MATCHING, so `#ifdef NON_MATCHING` clean-C bodies
# compile instead, letting objdiff bank their fuzzy %% into progress/report.nm.json.
# It NEVER touches the matching build/, the canonical progress/report.json, or the
# retail sha256 — report.nm.json is a separate, honest "WIP incl. partials" view.
#
#   matched_code / matched_functions  -> 100%-exact only (unchanged by partials)
#   fuzzy_match_percent (report.nm)   -> fuzzy-weighted, banks clean-C partials
#
# Usage: scripts/score_nm.sh
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

echo "[1/4] generate config/us-nm/ (compile_config + objdiff project)"
python3 scripts/gen_nm_config.py

echo "[2/4] build all objects into build-nm/ with -DNON_MATCHING (--no-link)"
python compile.py --config config/us-nm/compile_config.json --no-link >/dev/null

echo "[3/4] fill non-C objects objdiff needs (REL r207 etc.; NON_MATCHING-invariant)"
mkdir -p build-nm/rel && cp -r build/rel/. build-nm/rel/ 2>/dev/null || true

echo "[4/4] objdiff report -> progress/report.nm.json"
tools/objdiff-cli report generate -p config/us-nm -o progress/report.nm.json -f json-pretty >/dev/null

python3 - <<'PY'
import json
a=json.load(open("progress/report.json"))["measures"]
b=json.load(open("progress/report.nm.json"))["measures"]
print(f"  matching   fuzzy_match_percent: {a['fuzzy_match_percent']:.6f}%  (matched_code {a['matched_code']} B / {a['matched_functions']} fns)")
print(f"  NON_MATCH  fuzzy_match_percent: {b['fuzzy_match_percent']:.6f}%  (matched_code {b['matched_code']} B / {b['matched_functions']} fns)")
PY
echo "done. (matching build/ + report.json + retail sha256 untouched)"
