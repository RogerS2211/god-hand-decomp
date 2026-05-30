#!/usr/bin/env bash
# Dual-compiler regression harness — thin shell dispatcher over
# the Python implementation.
#
# Iterates every `src/cod/*.c`, compiles with both
#   - `cygnus-2.96` (the default; load-bearing back-compat contract
#     for all 735+ currently-matched functions)
#   - `sn-2.95.3-136` (the opt-in)
# and reports per-section byte-match against `expected/build/<rel>.o`.
#
# Exit semantics (forwarded from the Python implementation):
#   0  default compiler (cygnus-2.96) reproduces every section of every
#      TU; SN is informational and may report misses or even per-TU
#      failures (e.g. unsupported wide-integer arithmetic in SN cc1).
#   1  default compiler drifted on at least one section \u2014 the
#      compiler-dispatch plumbing has a real regression that must be
#      diagnosed before shipping further changes.
#   2  setup error (missing expected/build/, missing toolchain, etc.).
#
# Skip semantics: if `expected/build/` is empty (fresh clone before
# `python compile.py --setup`), exit 77 so session_check.sh shows it
# as skipped rather than failed.
set -uo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "$ROOT"

if [[ -z "$(find expected/build/src -name '*.o' -type f -print -quit 2>/dev/null)" ]]; then
    echo "expected/build/src empty \u2014 run \`python compile.py --setup\` first."
    exit 77
fi

exec python3 "$ROOT/scripts/checks/dual_compiler_regress.py" "$@"
