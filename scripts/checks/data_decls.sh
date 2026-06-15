#!/usr/bin/env bash
# data_decls sub-check.
#
# Verifies that asm/data/cod/*.s is in sync with the data-decl policy:
# `nonmatching <SYM>` macros are emitted iff there is no `extern <type>
# <SYM>;` declaration under include/ (or in config/data_decls_extra.txt).
#
# Wraps `python tools/strip_data_nonmatching.py --check`.  Exit 1 if
# the asm tree drifted from include/.
#
# Skip semantics: if asm/data/cod/2BBF80.data.s is missing (fresh
# clone before `splat split`), exit 77.
set -uo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "$ROOT"

if [[ ! -f "$ROOT/asm/data/cod/2BBF80.data.s" ]]; then
    echo "asm/data/cod/2BBF80.data.s missing — run splat first."
    exit 77
fi

exec python3 "$ROOT/tools/strip_data_nonmatching.py" --check
