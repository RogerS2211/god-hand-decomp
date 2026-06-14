#!/usr/bin/env bash
# Extract the boot ELF and small tables from your own ISO dump.
# Idempotent: safe to re-run; verifies the boot-ELF hash against the registry.
#
# Multi-version: the disc layout for every release is described in
# config/versions.json. Select one with --version (default: the registry's
# default version, us).
#
# Usage:
#   ./scripts/extract_iso.sh                       # us, from God Hand (USA).iso
#   ./scripts/extract_iso.sh --version eu          # eu, from its registered ISO
#   ./scripts/extract_iso.sh --version jp /path/to/jp.iso
#   ./scripts/extract_iso.sh /path/to/usa.iso      # us, explicit ISO path
#
# The boot ELF lands at disc_extract/<boot_elf> (e.g. disc_extract/SLUS_215.03);
# us keeps the historical disc_extract/ layout untouched.

set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
VERSIONS="${ROOT}/config/versions.json"
OUT="${ROOT}/disc_extract"

# ---- parse args ----------------------------------------------------------
VERSION=""
ISO=""
while [[ $# -gt 0 ]]; do
  case "$1" in
    --version) VERSION="$2"; shift 2 ;;
    --version=*) VERSION="${1#*=}"; shift ;;
    -h|--help) sed -n '2,18p' "$0"; exit 0 ;;
    *) ISO="$1"; shift ;;
  esac
done

if ! command -v 7z >/dev/null 2>&1; then
  echo "ERROR: 7z is required (sudo pacman -S p7zip / apt install p7zip-full)" >&2
  exit 1
fi
if [[ ! -f "$VERSIONS" ]]; then
  echo "ERROR: registry not found: $VERSIONS" >&2
  exit 1
fi

# ---- pull this version's fields out of the registry ----------------------
# Emits: VERSION BOOT_ELF ELF_SHA256 ISO_NAME (tab-separated)
read -r VERSION BOOT_ELF ELF_SHA256 ISO_NAME < <(python3 - "$VERSIONS" "$VERSION" <<'PY'
import json, sys
reg = json.load(open(sys.argv[1]))
key = sys.argv[2] or reg.get("default", "us")
versions = reg.get("versions", {})
if key not in versions:
    sys.exit(f"unknown --version {key!r}; known: {', '.join(sorted(versions))}")
v = versions[key]
print("\t".join([key, v["boot_elf"], v["elf_sha256"], v.get("iso_name", "")]))
PY
)

if [[ -z "$ISO" ]]; then
  ISO="${ROOT}/${ISO_NAME}"
fi
if [[ ! -f "$ISO" ]]; then
  echo "ERROR: ISO not found at: $ISO" >&2
  echo "Pass a path as an argument, or place '${ISO_NAME}' at the repo root." >&2
  exit 1
fi

mkdir -p "$OUT"
echo "[extract_iso] version=$VERSION  boot=$BOOT_ELF"
echo "[extract_iso] Extracting from: $ISO"

# Boot ELF is always extracted. SYSTEM.CNF / disc tables share filenames
# across regions, so only the default (us) version writes them into the flat
# disc_extract/ dir — that keeps the historical us layout intact and avoids
# clobbering it when extracting a sibling region's disc.
7z e -o"$OUT" "$ISO" "$BOOT_ELF" -y >/dev/null
if [[ "$VERSION" == "us" ]]; then
  7z e -o"$OUT" "$ISO" SYSTEM.CNF 0FLISTDV.DIR GODHAND.FST -y >/dev/null 2>&1 || true
fi

echo "[extract_iso] Verifying ELF hash"
actual_sha256="$(sha256sum "$OUT/$BOOT_ELF" | cut -d' ' -f1)"
if [[ "$actual_sha256" != "$ELF_SHA256" ]]; then
  echo "ERROR: boot-ELF SHA-256 mismatch for version '$VERSION'." >&2
  echo "  expected: $ELF_SHA256" >&2
  echo "  actual:   $actual_sha256" >&2
  echo "Your ISO does not match the release registered as '$VERSION'." >&2
  exit 2
fi

echo "[extract_iso] OK"
echo "  $OUT/$BOOT_ELF   ($(stat -c%s "$OUT/$BOOT_ELF") bytes, sha256 ${actual_sha256:0:12}…)"
