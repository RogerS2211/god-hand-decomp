#!/usr/bin/env bash
# Verify the expected/build/ objdiff baseline really
# is the retail-equal build.
#
# Runs scripts/checks/verify_expected_vs_retail.py in deep mode
# (G1 byte-mirror + G2 ld-only relink → retail-equal ELF).  G2 costs
# ~133 ms and is the only gate that catches a stale objdiff baseline
# that drifted away from a still-byte-equal current build (e.g. a
# hand-edited expected/build/<u>.o), so it runs unconditionally.
#
# The previous `--fast` flag (skip G2) was removed: it had no
# performance argument and was an innocently-named footgun.  No
# callers in-repo used it.
#
# Skip semantics: if expected/build/ has no objects, exit 77 (fresh
# clone before `python compile.py --setup`).
set -uo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "$ROOT"

if [[ -z "$(find expected/build -name '*.o' -type f -print -quit 2>/dev/null)" ]]; then
    echo "expected/build/ empty — run \`python compile.py --setup\` first."
    exit 77
fi

exec python3 "$ROOT/scripts/checks/verify_expected_vs_retail.py" --deep
