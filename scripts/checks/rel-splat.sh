#!/usr/bin/env bash
# rel-splat sub-check.
#
# Per-REL splat round-trip: every byte of every configured REL must be
# reproducible from the splat-emitted (asm/, bin/rel/) tree.  Wraps
# scripts/verify_rel_splat_roundtrip.py.  Does NOT re-run splat; the
# asm/rel/ and bin/rel/ trees on disk are what it scores.
#
# Skip semantics: the underlying script returns exit 77 (handled by
# session_check.sh as "skipped, non-fatal") when no REL has been split
# yet.  That lets this check land before any REL config exists (e.g.
# on a fresh clone, before the REL splat is applied) without breaking
# the 8-of-8 ratchet.
set -uo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "$ROOT"

VERIFIER="$ROOT/scripts/verify_rel_splat_roundtrip.py"
if [[ ! -x "$VERIFIER" ]]; then
    echo "$VERIFIER missing or not executable — not yet landed."
    exit 77
fi

exec python3 "$VERIFIER"
