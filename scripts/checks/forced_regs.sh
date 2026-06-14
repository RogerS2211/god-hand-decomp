#!/usr/bin/env bash
# forced_regs sub-check (DECISIONS.md).
#
# Ratchet gate on forced-register variables (`register T x __asm__("$N");`).
# These are a matching-decompile anti-pattern: they reproduce a register-
# field bit without recovering the C structure that caused it, and they
# are fragile under any nearby change.  Permitted ONLY as a documented
# last resort, recorded per-file in config/forced_regs_allowlist.txt.
#
# Wraps `python3 scripts/check_forced_regs.py`.  Fails (exit 1) if any
# src/ or include/ file has more pins than allowlisted, or has any while
# absent from the allowlist.  Counts may only ratchet down.
#
# Skip semantics: if src/ is missing (fresh clone pre-checkout), the
# python checker returns 77 and we propagate it.
set -uo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "$ROOT"

exec python3 "$ROOT/scripts/check_forced_regs.py"
