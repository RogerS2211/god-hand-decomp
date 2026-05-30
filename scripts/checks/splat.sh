#!/usr/bin/env bash
# splat round-trip sub-check.
#
# Validates that every byte of every splat-emitted .s file re-encodes
# back to the bytes splat read from build/SLUS_215.03.rom.  Wraps
# scripts/verify_splat_roundtrip.py.  Does NOT re-run splat;
# the asm/ tree on disk is what it scores.
#
# Skip semantics: if asm/cod/000000.s is missing (fresh clone before
# `splat split`), exit 77.  Otherwise verify_splat_roundtrip.py is
# authoritative.
set -uo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "$ROOT"

if [[ ! -f "$ROOT/asm/cod/000000.s" ]]; then
    echo "asm/cod/000000.s missing — run splat first."
    exit 77
fi
if [[ ! -f "$ROOT/build/SLUS_215.03.rom" ]]; then
    echo "build/SLUS_215.03.rom missing — run splat first."
    exit 77
fi

exec python3 "$ROOT/scripts/verify_splat_roundtrip.py"
