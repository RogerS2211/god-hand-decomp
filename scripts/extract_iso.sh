#!/usr/bin/env bash
# Extract the boot ELF and small tables from the user's own ISO dump.
# Idempotent: safe to re-run; verifies hashes against the expected NTSC-U build.
#
# Usage:   ./scripts/extract_iso.sh [path/to/iso]
# Default: ./God\ Hand\ \(USA\).iso

set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
ISO="${1:-${ROOT}/God Hand (USA).iso}"
OUT="${ROOT}/disc_extract"

EXPECTED_ELF_SHA256="1742f95bef65bdb2aa57b7a77df4ac7619a092e9646e1ea325bc32ec8a64f3cd"

if [[ ! -f "$ISO" ]]; then
  echo "ERROR: ISO not found at: $ISO" >&2
  echo "Pass a path as the first argument, or place 'God Hand (USA).iso' at the repo root." >&2
  exit 1
fi

if ! command -v 7z >/dev/null 2>&1; then
  echo "ERROR: 7z is required (sudo pacman -S p7zip / apt install p7zip-full)" >&2
  exit 1
fi

mkdir -p "$OUT"

echo "[extract_iso] Extracting boot ELF and tables from: $ISO"
7z e -o"$OUT" "$ISO" \
  SLUS_215.03 \
  SYSTEM.CNF \
  0FLISTDV.DIR \
  GODHAND.FST \
  -y >/dev/null

echo "[extract_iso] Verifying ELF hash"
actual_sha256="$(sha256sum "$OUT/SLUS_215.03" | cut -d' ' -f1)"
if [[ "$actual_sha256" != "$EXPECTED_ELF_SHA256" ]]; then
  echo "ERROR: ELF SHA-256 mismatch." >&2
  echo "  expected: $EXPECTED_ELF_SHA256" >&2
  echo "  actual:   $actual_sha256" >&2
  echo "Your ISO does not match the NTSC-U release this project targets (SLUS-21503)." >&2
  exit 2
fi

echo "[extract_iso] OK"
echo "  $OUT/SLUS_215.03   ($(stat -c%s "$OUT/SLUS_215.03") bytes, sha256 ${actual_sha256:0:12}…)"
echo "  $OUT/SYSTEM.CNF"
echo "  $OUT/GODHAND.FST"
echo "  $OUT/0FLISTDV.DIR"
