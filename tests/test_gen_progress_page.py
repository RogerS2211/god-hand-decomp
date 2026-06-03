"""Unit tests for tools/gen_progress_page.py size + module-rollup logic.

The tracker's value is "what's still missing", so it must surface per-unit
*code sizes* and a per-module rollup. report.json carries a ``size`` on every
function (it reconciles exactly to the headline ``total_code`` / ``matched_code``),
so these are computed offline from the committed report — no toolchain needed.
"""
from __future__ import annotations

import importlib.util
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parent.parent


@pytest.fixture(scope="module")
def gen():
    name = "gen_progress_page"
    spec = importlib.util.spec_from_file_location(
        name, ROOT / "tools" / "gen_progress_page.py"
    )
    mod = importlib.util.module_from_spec(spec)
    sys.modules[name] = mod
    spec.loader.exec_module(mod)
    return mod


def _unit(name, funcs, cat=""):
    return {
        "name": name,
        "measures": {"fuzzy_match_percent": 0.0},
        "metadata": {"category": cat} if cat else {},
        "functions": funcs,
    }


def _fn(size, pct):
    return {"name": "f", "size": str(size), "fuzzy_match_percent": pct}


def test_human_bytes(gen):
    assert gen.human_bytes(88) == "88 B"
    assert gen.human_bytes(2_844_416) == "2.71 MB"
    assert gen.human_bytes(239_108) == "233.5 KB"


def test_unit_code_bytes_sums_function_sizes(gen):
    # 100B matched (100%), 50B unmatched (0%), 30B null (unmatched) -> (100, 180)
    u = _unit("u", [_fn(100, 100.0), _fn(50, 0.0), {"name": "f", "size": "30", "fuzzy_match_percent": None}])
    assert gen.unit_code_bytes(u) == (100, 180)


def test_compact_units_carries_sizes_and_sorts_by_unmatched(gen):
    units = [
        _unit("small_done", [_fn(40, 100.0)]),           # 0 unmatched
        _unit("big_gap", [_fn(10, 100.0), _fn(990, 0.0)]),  # 990 unmatched
        _unit("mid_gap", [_fn(100, 0.0)]),               # 100 unmatched
    ]
    out = gen.compact_units(units)
    # biggest unmatched-bytes first
    assert [u["n"] for u in out] == ["big_gap", "mid_gap", "small_done"]
    big = next(u for u in out if u["n"] == "big_gap")
    assert big["mc"] == 10 and big["tc"] == 1000


def test_module_rollup_aggregates_by_category(gen):
    units = [
        _unit("a", [_fn(100, 100.0), _fn(100, 0.0)], cat="engine"),
        _unit("b", [_fn(50, 100.0)], cat="engine"),
        _unit("c", [_fn(80, 0.0)], cat=""),  # unclassified
    ]
    cats = [{"id": "engine", "name": "Game engine"}]
    roll = gen.module_rollup(units, cats)
    by = {m["id"]: m for m in roll}
    assert by["engine"]["tc"] == 250 and by["engine"]["mc"] == 150
    assert by["engine"]["name"] == "Game engine"
    # units with no category fall into an explicit bucket, not dropped
    assert "unclassified" in by
    assert by["unclassified"]["tc"] == 80 and by["unclassified"]["mc"] == 0
    # total code is conserved across modules
    assert sum(m["tc"] for m in roll) == 330


def test_committed_report_rollup_conserves_total_code(gen):
    import json
    rep = json.loads((ROOT / "progress" / "report.json").read_text())
    units = rep["units"]
    roll = gen.module_rollup(units, rep.get("categories", []))
    assert sum(m["tc"] for m in roll) == int(rep["measures"]["total_code"])
    assert sum(m["mc"] for m in roll) == int(rep["measures"]["matched_code"])
