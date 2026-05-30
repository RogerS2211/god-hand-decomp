#!/usr/bin/env bash
# build sub-check.
#
# 1. Runs `python compile.py` and confirms it succeeds.
# 2. Confirms build/SLUS_215.03.elf sha256 == disc_extract/SLUS_215.03
#    (the byte-level invariant).
#
# Skip semantics:
#   - if compile.py is missing, exit 77.
#   - if disc_extract/SLUS_215.03 is missing, fail the sha256 check
#     loudly: that file is required for the invariant and the user
#     should re-run scripts/extract_iso.sh.
set -uo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "$ROOT"

if [[ ! -f "$ROOT/compile.py" ]]; then
    echo "compile.py missing — not yet landed."
    exit 77
fi

# Skip when splat output is missing (worktree or fresh clone before first splat).
if [[ ! -f "$ROOT/asm/cod/000000.s" ]]; then
    echo "asm/cod/000000.s missing — run splat first."
    exit 77
fi

# Build (capture all output; only show on failure)
build_log=$(python3 compile.py 2>&1)
rc=$?
if [[ $rc -ne 0 ]]; then
    echo "compile.py exited with rc=$rc:"
    printf "%s\n" "$build_log"
    exit 1
fi

ELF="$ROOT/build/SLUS_215.03.elf"
RETAIL="$ROOT/disc_extract/SLUS_215.03"

if [[ ! -f "$ELF" ]]; then
    echo "compile.py succeeded but $ELF is missing."
    exit 1
fi
if [[ ! -f "$RETAIL" ]]; then
    echo "disc_extract/SLUS_215.03 missing — run scripts/extract_iso.sh."
    exit 1
fi

got=$(sha256sum "$ELF" | awk '{print $1}')
want=$(sha256sum "$RETAIL" | awk '{print $1}')

if [[ "$got" != "$want" ]]; then
    echo "ELF sha256 mismatch:"
    echo "  build : $got"
    echo "  retail: $want"
    exit 1
fi

echo "compile.py OK; sha256 ${got:0:12}… matches retail."
exit 0
