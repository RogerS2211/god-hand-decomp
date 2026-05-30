#!/usr/bin/env python3
"""compiler_for_function.py — address-band → compiler-pin lookup tool.

Given a function name (``func_HHHHHHHH``) or address (``0xHHHHHH``), prints
the recommended compiler tag for that function's text-section address.
Based on the empirical address-band layout (the "Address-band predictor").

This is the canonical CLI for the address → compiler decision that future
hand-author / smoke / bulk-migration work would otherwise re-derive
empirically per-candidate (which cost ~3 hours of probing).

Examples::

    $ python3 scripts/compiler_for_function.py func_002772A8
    sn-2.95.3-136  (band 1, 0x00100280-0x0031DA28, 4113 funcs)

    $ python3 scripts/compiler_for_function.py 0x0034F6C0
    cygnus-2.96  (band 2, 0x0031DA48-0x0036F048, 1224 funcs)

    $ python3 scripts/compiler_for_function.py func_FFFFFFFF
    UNKNOWN  (address 0xFFFFFFFF is outside all known bands)

    $ python3 scripts/compiler_for_function.py --json func_002772A8
    {"name": "func_002772A8", "address": 2585256, "address_hex": "0x002772A8",
     "compiler": "sn-2.95.3-136", "band": 1, ...}

Exit codes:
  0  matched band found, compiler tag printed
  1  argument parse error or function/address outside all bands
  2  internal error

The band table provenance and revalidation procedure are documented
alongside the band scan.
"""
from __future__ import annotations

import argparse
import json
import re
import sys
from dataclasses import dataclass
from typing import Sequence

# --------------------------------------------------------------------------- #
# Band table — the Address-band predictor.
#
# Updating this table:
#   1. Re-run the band scan.
#   2. Update the table here.
#   3. Re-run tests/test_compiler_for_function.py.
# --------------------------------------------------------------------------- #

_COMPILER_SN = "sn-2.95.3-136"
_COMPILER_CYGNUS = "cygnus-2.96"


@dataclass(frozen=True)
class Band:
    index: int  # 1-based band number
    start: int
    end: int   # inclusive
    compiler: str
    func_count: int  # empirical count from the band scan


_BANDS: tuple[Band, ...] = (
    # Band 1 end extended 0x0031D928 -> 0x0031DA28:
    # func_0031DA28 was matched under SN (carved into the SN-pinned
    # src/cod/merged_orphans_d.c) and sits in what used to be the
    # band-1/band-2 gap, ending exactly at band 2's start (0x0031DA48).
    # The intervening stubs (func_0031D9C8/F0/DA20) carry no Cygnus
    # tail-call shape, so SN territory provably runs through 0x0031DA28.
    Band(1, 0x00100280, 0x0031DA28, _COMPILER_SN,     4113),
    Band(2, 0x0031DA48, 0x0036F048, _COMPILER_CYGNUS, 1224),
    Band(3, 0x00372CB0, 0x00387430, _COMPILER_SN,      243),
    Band(4, 0x003875A8, 0x00393F30, _COMPILER_CYGNUS,  167),
    Band(5, 0x00393FD8, 0x00394F20, _COMPILER_SN,       10),
    Band(6, 0x003951F8, 0x003A4AF0, _COMPILER_CYGNUS,  117),
    Band(7, 0x003A53A8, 0x003AF7B8, _COMPILER_SN,       62),
    Band(8, 0x003B0268, 0x003BAD08, _COMPILER_CYGNUS,  112),
    Band(9, 0x003BAFF8, 0x003BBA10, _COMPILER_SN,        7),
)


# --------------------------------------------------------------------------- #
# Parsing.
# --------------------------------------------------------------------------- #

_FUNC_NAME_RE = re.compile(r"^func_([0-9A-Fa-f]{6,8})$", re.IGNORECASE)


def parse_target(target: str) -> int:
    """Return the integer address parsed from ``target``.

    Accepts:
      * ``func_HHHHHHHH`` (case-insensitive; 6-8 hex digits)
      * ``0xHHHHHH`` / ``0xHHHHHHHH`` (case-insensitive)
      * bare decimal integer
      * bare hex integer with no 0x prefix (8 hex digits, no other meaning)

    Raises ``ValueError`` with a human-readable message on parse failure.
    """
    target = target.strip()
    if not target:
        raise ValueError("empty target")

    # func_HHHHHHHH
    m = _FUNC_NAME_RE.match(target)
    if m is not None:
        return int(m.group(1), 16)

    # 0xHHHHHHHH
    if target.lower().startswith("0x"):
        try:
            return int(target, 16)
        except ValueError:
            raise ValueError(f"invalid hex literal: {target!r}") from None

    # Decimal or bare hex
    try:
        return int(target)
    except ValueError:
        pass
    try:
        # Bare hex (8 digits)
        return int(target, 16)
    except ValueError:
        raise ValueError(
            f"could not parse {target!r} as func_HHHHHHHH, 0xHHHH..., "
            "decimal, or bare hex"
        ) from None


# --------------------------------------------------------------------------- #
# Lookup.
# --------------------------------------------------------------------------- #


def lookup_band(address: int) -> Band | None:
    """Return the :class:`Band` whose range contains ``address``, else ``None``."""
    for band in _BANDS:
        if band.start <= address <= band.end:
            return band
    return None


def lookup_compiler(address: int) -> str | None:
    """Return the compiler tag for ``address``, or ``None`` if no band matches."""
    band = lookup_band(address)
    return band.compiler if band is not None else None


# --------------------------------------------------------------------------- #
# CLI.
# --------------------------------------------------------------------------- #


def _format_human(address: int, band: Band | None) -> str:
    if band is None:
        return (
            f"UNKNOWN  (address 0x{address:08X} is outside all known bands; "
            f"re-run the band scan to extend coverage)"
        )
    return (
        f"{band.compiler}  (band {band.index}, "
        f"0x{band.start:08X}-0x{band.end:08X}, {band.func_count} funcs)"
    )


def _format_json(target: str, address: int, band: Band | None) -> str:
    payload = {
        "name": target if target.startswith("func_") else None,
        "address": address,
        "address_hex": f"0x{address:08X}",
        "compiler": band.compiler if band else None,
        "band": band.index if band else None,
        "band_start_hex": f"0x{band.start:08X}" if band else None,
        "band_end_hex": f"0x{band.end:08X}" if band else None,
        "band_func_count": band.func_count if band else None,
    }
    return json.dumps(payload, indent=2)


def main(argv: Sequence[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        prog="compiler_for_function.py",
        description=(
            "Look up the recommended compiler pin (SN ee-gcc 2.95.3-136 vs "
            "Cygnus 2.96) for a function based on its text-section address. "
            "Uses the empirical Address-band predictor table."
        ),
    )
    parser.add_argument(
        "target",
        help=(
            "Function name (func_HHHHHHHH) or address (0xHHHH... / decimal). "
            "Case-insensitive."
        ),
    )
    parser.add_argument(
        "--json",
        action="store_true",
        help="emit JSON instead of human-readable text",
    )
    parser.add_argument(
        "--quiet",
        "-q",
        action="store_true",
        help="emit only the compiler tag, no surrounding context",
    )
    args = parser.parse_args(argv)

    try:
        address = parse_target(args.target)
    except ValueError as exc:
        print(f"compiler_for_function: {exc}", file=sys.stderr)
        return 1

    band = lookup_band(address)

    if args.json:
        print(_format_json(args.target, address, band))
        return 0 if band else 1

    if args.quiet:
        if band is None:
            print("UNKNOWN")
            return 1
        print(band.compiler)
        return 0

    print(_format_human(address, band))
    return 0 if band else 1


if __name__ == "__main__":
    sys.exit(main())
