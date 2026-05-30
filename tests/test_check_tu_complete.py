"""Offline unit tests for ``scripts/check_tu_complete.py``.

Pure-Python — no real compile.py, objdiff, or repo-tree dependency;
covers the script's helpers + the top-level driver (``check_one``) +
the marker-mode wrapper (``check_marker``) against tmpdir-staged
minimal project trees.  Small focused tests that pin the contract.
"""
from __future__ import annotations

import json
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "scripts"))
import check_tu_complete as ctc  # noqa: E402


# --------------------------------------------------------------------------- #
# Helpers
# --------------------------------------------------------------------------- #


def _write_project(
    tmp: Path,
    *,
    tu_text: str,
    carved: list[dict],
    report_units: list[dict] | None = None,
) -> tuple[Path, Path, Path]:
    """Stage a minimal project tree and return (root, config, report)."""
    (tmp / "src" / "cod").mkdir(parents=True)
    tu_path = tmp / "src" / "cod" / "demo.c"
    tu_path.write_text(tu_text)
    cfg = tmp / "compile_config.json"
    cfg.write_text(json.dumps({"carved_funcs": carved}))
    rep = tmp / "progress" / "report.json"
    rep.parent.mkdir(parents=True)
    if report_units is not None:
        rep.write_text(json.dumps({"units": report_units}))
    return tmp, cfg, rep


def _matched(name: str, *, pct: float = 100.0) -> dict:
    return {"name": name, "fuzzy_match_percent": pct}


def _unmatched(name: str) -> dict:
    return {"name": name}  # no fuzzy_match_percent key


def _unit(name: str, fns: list[dict]) -> dict:
    return {"name": name, "functions": fns}


# --------------------------------------------------------------------------- #
# Pure helpers
# --------------------------------------------------------------------------- #


class TestPureHelpers:
    def test_tu_unit_name_strips_c_suffix(self) -> None:
        assert ctc.tu_unit_name("src/cod/000000.c") == "src/cod/000000"

    def test_tu_unit_name_strips_cpp_suffix(self) -> None:
        assert ctc.tu_unit_name("src/foo.cpp") == "src/foo"

    def test_find_includes_matches_three_folder_styles(self) -> None:
        src = (
            'INCLUDE_ASM("nonmatching", func_a);\n'
            'INCLUDE_ASM("matching", func_b)\n'
            '  INCLUDE_ASM("permanent", func_c);\n'
            '// not a real one: INCLUDE_ASM("nonmatching", foo);\n'  # commented
        )
        # All four lines actually match the regex (the // prefix line
        # has leading whitespace... wait, no; `//` is not whitespace).
        # That comment line is *not* matched because the regex
        # requires only whitespace before INCLUDE_ASM.
        out = ctc.find_includes(src)
        assert out == [
            ("nonmatching", "func_a"),
            ("matching", "func_b"),
            ("permanent", "func_c"),
        ]

    def test_nonmatching_includes_only_returns_nonmatching(self) -> None:
        src = (
            'INCLUDE_ASM("nonmatching", func_a);\n'
            'INCLUDE_ASM("permanent", func_b);\n'
            'INCLUDE_ASM("matching", func_c);\n'
        )
        assert ctc.nonmatching_includes(src) == ["func_a"]

    def test_unit_unmatched_functions_handles_missing_pct(self) -> None:
        unit = _unit("u", [
            _matched("func_a"),
            _unmatched("func_b"),
            {"name": "func_c", "fuzzy_match_percent": 99.5},  # partial
        ])
        assert ctc.unit_unmatched_functions(unit) == ["func_b", "func_c"]

    def test_unit_unmatched_functions_empty_when_all_matched(self) -> None:
        unit = _unit("u", [_matched("func_a"), _matched("func_b")])
        assert ctc.unit_unmatched_functions(unit) == []


# --------------------------------------------------------------------------- #
# check_one top-level driver
# --------------------------------------------------------------------------- #


class TestCheckOne:
    def test_empty_marker_no_op_via_check_marker(self, tmp_path: Path) -> None:
        marker = tmp_path / "marker.txt"
        # marker missing → no-op
        out = ctc.check_marker(
            root=tmp_path,
            config_path=tmp_path / "compile_config.json",
            report_path=tmp_path / "progress" / "report.json",
            marker_path=marker,
        )
        assert out == []

    def test_marker_with_comments_and_blanks_is_filtered(
        self, tmp_path: Path,
    ) -> None:
        marker = tmp_path / "marker.txt"
        marker.write_text("# a comment\n\n  \n")
        out = ctc.read_marker(marker)
        assert out == []

    def test_tu_with_no_carves_is_trivial_pass(self, tmp_path: Path) -> None:
        root, cfg, _ = _write_project(
            tmp_path,
            tu_text="// empty TU, no carves\n",
            carved=[],
        )
        rep_path = tmp_path / "progress" / "report.json"
        result = ctc.check_one(
            "src/cod/demo.c",
            root=root, config_path=cfg, report_path=rep_path,
        )
        assert result.ok
        assert result.unit_name is None  # no work to do
        assert result.nonmatching_includes == []

    def test_tu_with_one_nonmatching_include_fails(
        self, tmp_path: Path,
    ) -> None:
        root, cfg, _ = _write_project(
            tmp_path,
            tu_text=(
                '#include "include_asm.h"\n'
                'INCLUDE_ASM("nonmatching", func_a);\n'
            ),
            carved=[
                {"name": "func_a", "tu": "src/cod/demo.c", "unit": "asm/x",
                 "vaddr": "0x100000", "size": 8},
            ],
            report_units=[_unit("src/cod/demo", [_matched("func_a")])],
        )
        rep_path = tmp_path / "progress" / "report.json"
        result = ctc.check_one(
            "src/cod/demo.c",
            root=root, config_path=cfg, report_path=rep_path,
        )
        assert not result.ok
        assert result.nonmatching_includes == ["func_a"]
        # diagnostic names the function
        assert "func_a" in result.pretty()

    def test_tu_with_permanent_include_is_allowed(
        self, tmp_path: Path,
    ) -> None:
        # The 'permanent' marker convention — counts as
        # TU-matched provided the function actually shows matched
        # in report.json (which it will, because compile.py emits
        # the bytes verbatim from the asm carve).
        root, cfg, _ = _write_project(
            tmp_path,
            tu_text=(
                '#include "include_asm.h"\n'
                'INCLUDE_ASM("permanent", func_mmi);\n'
            ),
            carved=[
                {"name": "func_mmi", "tu": "src/cod/demo.c", "unit": "asm/x",
                 "vaddr": "0x100000", "size": 8},
            ],
            report_units=[_unit("src/cod/demo", [_matched("func_mmi")])],
        )
        rep_path = tmp_path / "progress" / "report.json"
        result = ctc.check_one(
            "src/cod/demo.c",
            root=root, config_path=cfg, report_path=rep_path,
        )
        assert result.ok
        assert result.nonmatching_includes == []
        assert result.unmatched_functions == []

    def test_tu_with_unmatched_function_fails_and_names_it(
        self, tmp_path: Path,
    ) -> None:
        root, cfg, _ = _write_project(
            tmp_path,
            tu_text="void func_a(void) {}\n",  # no INCLUDE_ASM
            carved=[
                {"name": "func_a", "tu": "src/cod/demo.c", "unit": "asm/x",
                 "vaddr": "0x100000", "size": 8},
            ],
            report_units=[_unit("src/cod/demo", [_unmatched("func_a")])],
        )
        rep_path = tmp_path / "progress" / "report.json"
        result = ctc.check_one(
            "src/cod/demo.c",
            root=root, config_path=cfg, report_path=rep_path,
        )
        assert not result.ok
        assert result.unmatched_functions == [("src/cod/demo", "func_a")]
        pretty = result.pretty()
        assert "func_a" in pretty
        assert "src/cod/demo" in pretty

    def test_tu_fully_matched_passes(self, tmp_path: Path) -> None:
        root, cfg, _ = _write_project(
            tmp_path,
            tu_text="int func_a(void) { return 1; }\n",
            carved=[
                {"name": "func_a", "tu": "src/cod/demo.c", "unit": "asm/x",
                 "vaddr": "0x100000", "size": 4},
            ],
            report_units=[_unit("src/cod/demo", [_matched("func_a")])],
        )
        rep_path = tmp_path / "progress" / "report.json"
        result = ctc.check_one(
            "src/cod/demo.c",
            root=root, config_path=cfg, report_path=rep_path,
        )
        assert result.ok
        assert result.unmatched_functions == []
        assert "COMPLETE" in result.pretty()

    def test_missing_unit_in_report_is_a_note_not_failure(
        self, tmp_path: Path,
    ) -> None:
        # report.json exists but has no entry for this unit (TU declared
        # in carved_funcs but compile.py --setup hasn't been re-run).
        root, cfg, _ = _write_project(
            tmp_path,
            tu_text="int func_a(void) { return 1; }\n",
            carved=[
                {"name": "func_a", "tu": "src/cod/demo.c", "unit": "asm/x",
                 "vaddr": "0x100000", "size": 4},
            ],
            report_units=[],  # empty units list
        )
        rep_path = tmp_path / "progress" / "report.json"
        result = ctc.check_one(
            "src/cod/demo.c",
            root=root, config_path=cfg, report_path=rep_path,
        )
        # The TU has no nonmatching includes; sub-criterion 2 can't
        # decide, so we pass-with-note rather than fail.
        assert result.ok
        assert result.notes  # has a note
        assert "not in progress/report.json" in result.notes[0]

    def test_missing_report_when_tu_has_carves_raises(
        self, tmp_path: Path,
    ) -> None:
        root, cfg, _ = _write_project(
            tmp_path,
            tu_text="int func_a(void) { return 1; }\n",
            carved=[
                {"name": "func_a", "tu": "src/cod/demo.c", "unit": "asm/x",
                 "vaddr": "0x100000", "size": 4},
            ],
            report_units=None,  # no file created
        )
        rep_path = tmp_path / "progress" / "report.json"
        with pytest.raises(ctc.CheckError, match="progress/report.json"):
            ctc.check_one(
                "src/cod/demo.c",
                root=root, config_path=cfg, report_path=rep_path,
            )

    def test_missing_tu_source_raises(self, tmp_path: Path) -> None:
        cfg = tmp_path / "compile_config.json"
        cfg.write_text(json.dumps({"carved_funcs": []}))
        with pytest.raises(ctc.CheckError, match="TU source not found"):
            ctc.check_one(
                "src/cod/no_such.c",
                root=tmp_path, config_path=cfg,
                report_path=tmp_path / "progress" / "report.json",
            )


# --------------------------------------------------------------------------- #
# CLI smoke
# --------------------------------------------------------------------------- #


class TestCli:
    def test_no_marker_no_arg_exits_0(
        self, tmp_path: Path, capsys: pytest.CaptureFixture[str],
    ) -> None:
        (tmp_path / "compile_config.json").write_text(
            json.dumps({"carved_funcs": []}),
        )
        rc = ctc._cli([
            "--config", str(tmp_path / "compile_config.json"),
            "--report", str(tmp_path / "progress" / "report.json"),
            "--marker", str(tmp_path / "marker.txt"),
            "--root", str(tmp_path),
        ])
        assert rc == 0
        out = capsys.readouterr().out
        assert "no TU in marker" in out

    def test_json_mode_emits_parseable_payload(
        self, tmp_path: Path, capsys: pytest.CaptureFixture[str],
    ) -> None:
        root, cfg, _ = _write_project(
            tmp_path,
            tu_text='INCLUDE_ASM("nonmatching", func_a);\n',
            carved=[
                {"name": "func_a", "tu": "src/cod/demo.c", "unit": "asm/x",
                 "vaddr": "0x100000", "size": 8},
            ],
            report_units=[_unit("src/cod/demo", [_unmatched("func_a")])],
        )
        rep_path = tmp_path / "progress" / "report.json"
        rc = ctc._cli([
            "--config", str(cfg),
            "--report", str(rep_path),
            "--root", str(root),
            "--json",
            "src/cod/demo.c",
        ])
        assert rc == 1  # incomplete
        payload = json.loads(capsys.readouterr().out)
        assert payload["marker_used"] is False
        assert len(payload["tus"]) == 1
        rep = payload["tus"][0]
        assert rep["ok"] is False
        assert rep["nonmatching_includes"] == ["func_a"]
        assert rep["unmatched_functions"] == [
            {"unit": "src/cod/demo", "function": "func_a"},
        ]

    def test_marker_mode_with_one_failing_tu_exits_1(
        self, tmp_path: Path,
    ) -> None:
        root, cfg, _ = _write_project(
            tmp_path,
            tu_text='INCLUDE_ASM("nonmatching", func_a);\n',
            carved=[
                {"name": "func_a", "tu": "src/cod/demo.c", "unit": "asm/x",
                 "vaddr": "0x100000", "size": 8},
            ],
            report_units=[_unit("src/cod/demo", [_unmatched("func_a")])],
        )
        marker = tmp_path / "marker.txt"
        marker.write_text("src/cod/demo.c\n")
        rc = ctc._cli([
            "--config", str(cfg),
            "--report", str(tmp_path / "progress" / "report.json"),
            "--marker", str(marker),
            "--root", str(root),
        ])
        assert rc == 1
