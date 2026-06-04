#!/usr/bin/env bash
# score_nm.sh — regenerate the published progress report from the NON_MATCHING
# build, so the decomp.dev "decompiled" (fuzzy) number credits clean-C partials.
#
# This is the report-generation step to run before committing progress/report.json
# (it replaces a plain `scripts/progress.sh` run for the published report). It:
#   1. derives config/nm/ (a -DNON_MATCHING build into build-nm/ + its objdiff project)
#   2. compiles every unit into build-nm/ with NON_MATCHING (the guarded clean-C
#      bodies compile instead of their INCLUDE_ASM fallback)
#   3. writes progress/report.json from that build
#   4. refreshes docs/ (tracker + badges)
#
# What does and does NOT change:
#   - fuzzy_match_percent ("decompiled" on decomp.dev) rises with partials.
#   - matched_code / matched_functions stay 100%-exact-only (partials don't count).
#   - The default `python compile.py` build (the byte-identical retail ELF that
#     contributors verify) is untouched — it still compiles the #else INCLUDE_ASM.
#
# Requires the toolchain (setup_toolchain.sh) + expected/build target objects.
# Usage: scripts/score_nm.sh
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

echo "[1/4] generate config/nm/ (compile_config + objdiff project)"
python3 scripts/gen_nm_config.py

echo "[2/4] build all units into build-nm/ with -DNON_MATCHING (--no-link)"
python compile.py --config config/nm/compile_config.json --no-link >/dev/null

echo "[3/4] fill non-C objects objdiff needs (REL etc.; NON_MATCHING-invariant)"
if [ -d build/rel ]; then mkdir -p build-nm/rel && cp -r build/rel/. build-nm/rel/ 2>/dev/null || true; fi

echo "[4/4] objdiff report -> progress/report.json  +  fully-linked axis  +  refresh docs/"
tools/objdiff-cli report generate -p config/nm -o progress/report.json -f json-pretty >/dev/null
python3 scripts/mark_complete.py >/dev/null
python tools/gen_progress_page.py >/dev/null

python3 - <<'PY'
import json
m = json.load(open("progress/report.json"))["measures"]
print(f'  decompiled (fuzzy_match_percent): {m["fuzzy_match_percent"]:.4f}%')
print(f'  fully matched (matched_code):     {m["matched_code"]} B  ({m["matched_functions"]} fns)')
print(f'  fully linked (complete_code):     {m.get("complete_code", 0)} B  ({m.get("complete_code_percent", 0):.4f}%)')
PY
echo "done. Commit progress/report.json + docs/ to publish."
