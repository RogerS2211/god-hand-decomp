"""Unit tests for scripts/compiler_for_function.py."""
from __future__ import annotations

import io
import json
import sys
from contextlib import redirect_stderr, redirect_stdout
from pathlib import Path

import pytest

# Make ``scripts/`` importable as a package root.
_ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(_ROOT))
sys.path.insert(0, str(_ROOT / "scripts"))

from scripts import compiler_for_function as cff  # noqa: E402


# --------------------------------------------------------------------------- #
# parse_target — input shapes.
# --------------------------------------------------------------------------- #


class TestParseTarget:
    @pytest.mark.parametrize(
        "target,expected",
        [
            ("func_002772A8", 0x002772A8),
            ("func_0034F6C0", 0x0034F6C0),
            ("func_0012CF00", 0x0012CF00),
            # Case-insensitivity.
            ("func_002772a8", 0x002772A8),
            ("FUNC_002772A8", 0x002772A8),
        ],
    )
    def test_func_name_form(self, target: str, expected: int) -> None:
        assert cff.parse_target(target) == expected

    @pytest.mark.parametrize(
        "target,expected",
        [
            ("0x002772A8", 0x002772A8),
            ("0x12CF00", 0x12CF00),
            ("0X12CF00", 0x12CF00),
            ("0x100280", 0x100280),
        ],
    )
    def test_hex_literal_form(self, target: str, expected: int) -> None:
        assert cff.parse_target(target) == expected

    def test_decimal_form(self) -> None:
        assert cff.parse_target("2585256") == 0x002772A8

    def test_whitespace_is_stripped(self) -> None:
        assert cff.parse_target("  func_002772A8  \n") == 0x002772A8

    @pytest.mark.parametrize(
        "target",
        [
            "",
            "  ",
            "not_a_function",
            "func_XYZ",
            "func_",
            "0xZZZZ",
        ],
    )
    def test_invalid_target_raises(self, target: str) -> None:
        with pytest.raises(ValueError):
            cff.parse_target(target)


# --------------------------------------------------------------------------- #
# Band table sanity.
# --------------------------------------------------------------------------- #


class TestBandTable:
    def test_bands_are_in_address_order(self) -> None:
        for i in range(len(cff._BANDS) - 1):
            assert cff._BANDS[i].end < cff._BANDS[i + 1].start, (
                f"Bands {i + 1} and {i + 2} overlap or out of order"
            )

    def test_bands_have_consistent_indexing(self) -> None:
        for i, band in enumerate(cff._BANDS):
            assert band.index == i + 1

    def test_each_band_has_positive_func_count(self) -> None:
        for band in cff._BANDS:
            assert band.func_count > 0, f"Band {band.index} has 0 funcs"

    def test_each_band_uses_known_compiler_tag(self) -> None:
        for band in cff._BANDS:
            assert band.compiler in {
                cff._COMPILER_SN,
                cff._COMPILER_CYGNUS,
            }


# --------------------------------------------------------------------------- #
# lookup_band / lookup_compiler — empirical-fact tests.
#
# Each test case is anchored to a function whose compiler we KNOW
# empirically (because it's currently a carved match in compile_config.json
# or has been demonstrated in a prior session).
# --------------------------------------------------------------------------- #


class TestLookupBandEmpiricalCases:
    @pytest.mark.parametrize(
        "name,addr,expected_compiler,expected_band",
        [
            # Representative band-scan samples:
            ("func_002772A8", 0x002772A8, cff._COMPILER_SN, 1),
            ("func_0012CF00", 0x0012CF00, cff._COMPILER_SN, 1),
            # R-VU0 / R-VU0-2 (matched, SN-pinned):
            ("func_0027B768", 0x0027B768, cff._COMPILER_SN, 1),
            ("func_0028B0F0", 0x0028B0F0, cff._COMPILER_SN, 1),
            # R1 (matched, Cygnus default — Band 2):
            ("func_0034F6C0", 0x0034F6C0, cff._COMPILER_CYGNUS, 2),
            # Early band-1 SN territory:
            ("func_00100280", 0x00100280, cff._COMPILER_SN, 1),
            # Band-1 / band-2 boundary:
            ("func_0031D928", 0x0031D928, cff._COMPILER_SN, 1),
            # func_0031DA28: SN match in the former band-1/band-2 gap;
            # band 1's end was extended to its start so the predictor
            # agrees with the carved reality (regression guard).
            ("func_0031DA28", 0x0031DA28, cff._COMPILER_SN, 1),
            ("func_0031DA48", 0x0031DA48, cff._COMPILER_CYGNUS, 2),
        ],
    )
    def test_known_compiler(
        self, name: str, addr: int, expected_compiler: str, expected_band: int
    ) -> None:
        band = cff.lookup_band(addr)
        assert band is not None, f"{name} (0x{addr:08X}) should map to a band"
        assert band.compiler == expected_compiler
        assert band.index == expected_band

    def test_address_in_inter_band_gap_returns_none(self) -> None:
        # Between band 1 (ends 0x31DA28) and band 2 (starts 0x31DA48).
        gap_addr = 0x0031DA38
        assert cff.lookup_band(gap_addr) is None
        assert cff.lookup_compiler(gap_addr) is None

    def test_address_before_all_bands_returns_none(self) -> None:
        assert cff.lookup_band(0x00000000) is None
        assert cff.lookup_compiler(0x00000000) is None

    def test_address_after_all_bands_returns_none(self) -> None:
        assert cff.lookup_band(0xFFFFFFFF) is None
        assert cff.lookup_compiler(0xFFFFFFFF) is None


# --------------------------------------------------------------------------- #
# CLI integration.
# --------------------------------------------------------------------------- #


class TestCLI:
    def _run(self, argv: list[str]) -> tuple[int, str, str]:
        stdout, stderr = io.StringIO(), io.StringIO()
        with redirect_stdout(stdout), redirect_stderr(stderr):
            rc = cff.main(argv)
        return rc, stdout.getvalue(), stderr.getvalue()

    def test_human_output_for_known_band(self) -> None:
        rc, out, err = self._run(["func_002772A8"])
        assert rc == 0
        assert cff._COMPILER_SN in out
        assert "band 1" in out
        assert "0x00100280" in out
        assert err == ""

    def test_quiet_output_strips_context(self) -> None:
        rc, out, err = self._run(["-q", "func_002772A8"])
        assert rc == 0
        assert out.strip() == cff._COMPILER_SN

    def test_json_output_for_known_band(self) -> None:
        rc, out, err = self._run(["--json", "func_002772A8"])
        assert rc == 0
        payload = json.loads(out)
        assert payload["name"] == "func_002772A8"
        assert payload["address_hex"] == "0x002772A8"
        assert payload["compiler"] == cff._COMPILER_SN
        assert payload["band"] == 1

    def test_unknown_address_exits_1_with_helpful_message(self) -> None:
        rc, out, err = self._run(["0xFFFFFFFF"])
        assert rc == 1
        assert "UNKNOWN" in out
        assert "band scan" in out

    def test_invalid_target_returns_1_with_stderr_message(self) -> None:
        rc, out, err = self._run(["not_a_function"])
        assert rc == 1
        assert out == ""
        assert "compiler_for_function" in err
        assert "could not parse" in err.lower()

    def test_quiet_unknown_prints_unknown_and_exits_1(self) -> None:
        rc, out, err = self._run(["-q", "0xFFFFFFFF"])
        assert rc == 1
        assert out.strip() == "UNKNOWN"

    def test_json_unknown_includes_null_compiler(self) -> None:
        rc, out, err = self._run(["--json", "0xFFFFFFFF"])
        assert rc == 1
        payload = json.loads(out)
        assert payload["compiler"] is None
        assert payload["band"] is None
        assert payload["address_hex"] == "0xFFFFFFFF"


# --------------------------------------------------------------------------- #
# Coverage-completeness check against compile_config.json::carved_funcs.
#
# Confidence-building integration: every currently-carved function whose TU
# is SN-pinned should land in an SN-band, and every Cygnus-pinned TU's
# functions should land in a Cygnus-band (or band-1 lucky-neutrals).
#
# The 132 band-predicted-SN funcs currently carved into Cygnus-pinned
# src/cod/000000.c (lucky-neutral matches) are the documented exception.
# --------------------------------------------------------------------------- #


class TestAgainstCarvedFuncs:
    def _carved(self) -> list[tuple[str, int, str]]:
        cfg_path = _ROOT / "compile_config.json"
        if not cfg_path.exists():
            pytest.skip("compile_config.json not present")
        cfg = json.loads(cfg_path.read_text())
        units = {u["path"]: u.get("compiler", "cygnus-2.96") for u in cfg.get("compile_units", []) if "path" in u}
        carved: list[tuple[str, int, str]] = []
        for c in cfg.get("carved_funcs", []):
            name = c.get("name", "")
            tu = c.get("tu", "")
            if not name.startswith("func_") or not tu:
                continue
            try:
                addr = int(name.split("_")[1], 16)
            except (IndexError, ValueError):
                continue
            pin = units.get(tu, "cygnus-2.96")
            carved.append((name, addr, pin))
        return carved

    def test_sn_pinned_funcs_all_land_in_sn_bands(self) -> None:
        """Every function in an SN-pinned TU should map to an SN band."""
        carved = self._carved()
        sn_pinned = [(n, a) for n, a, pin in carved if pin == cff._COMPILER_SN]
        if not sn_pinned:
            pytest.skip("no SN-pinned carved functions in compile_config.json")
        misses = [
            (n, f"0x{a:08X}", cff.lookup_compiler(a))
            for n, a in sn_pinned
            if cff.lookup_compiler(a) != cff._COMPILER_SN
        ]
        assert not misses, (
            f"SN-pinned funcs landed in non-SN bands: {misses}"
        )

    def test_cygnus_pinned_band_assignment_is_mostly_consistent(self) -> None:
        """Cygnus-pinned funcs in non-band-1 ranges should *predominantly*
        land in Cygnus bands.  We allow a small number of band-1-style
        lucky-neutral exceptions — functions whose body is simple enough
        to compile byte-identically under either SN or Cygnus.

        The load-bearing invariant is the OTHER direction (SN-pinned
        funcs MUST land in SN bands, asserted by
        :meth:`test_sn_pinned_funcs_all_land_in_sn_bands`).  This test
        is a softer sanity check on the band table boundaries.
        """
        carved = self._carved()
        cygnus_pinned = [
            (n, a) for n, a, pin in carved if pin == cff._COMPILER_CYGNUS
        ]
        if not cygnus_pinned:
            pytest.skip("no Cygnus-pinned carved functions in compile_config.json")
        misses = [
            (n, f"0x{a:08X}", cff.lookup_compiler(a))
            for n, a in cygnus_pinned
            if (
                cff.lookup_band(a) is not None
                and cff.lookup_band(a).index != 1  # type: ignore[union-attr]
                and cff.lookup_compiler(a) != cff._COMPILER_CYGNUS
            )
        ]
        # Allow up to ~5 lucky-neutral exceptions across the entire
        # carved corpus; if this number grows we want to know (band
        # boundaries may need refinement).
        max_neutrals = 5
        assert len(misses) <= max_neutrals, (
            f"Too many Cygnus-pinned funcs landing in SN bands "
            f"({len(misses)} > {max_neutrals}); band table may need "
            f"refinement. Misses: {misses}"
        )
