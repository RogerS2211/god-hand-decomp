#!/usr/bin/env python3
"""doc_figures.py — reconcile the README "Progress" table with report.json.

The committed ``progress/report.json`` is the ground truth decomp.dev ingests.
The README "Progress" table is a hand-updated copy of those numbers, and nothing
stopped it silently drifting — it was a full publish (1,843 vs 1,912 functions)
stale once. This lint re-derives the headline figures from ``report.json`` and
fails if the README table disagrees, so a stale doc can't be committed. (Badges
are hosted by decomp.dev, which renders them from the same report, so they can't
drift.)

Toolchain-free (reads only committed files), so it runs in PR CI alongside
``report_lint.py``. When it fails: update the README "Progress" table to match
``progress/report.json``.

Exit codes: 0 pass, 1 mismatch, 77 skip (no report.json).
"""
from __future__ import annotations

import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
TOL = 0.02   # percent rounding tolerance (figures display at 2 decimals)


def _pct(n: float, d: float) -> float:
    return 0.0 if not d else 100.0 * n / d


def _num(s: str) -> float:
    return float(s.replace(",", ""))


def expected_figures(measures: dict) -> dict:
    mf = int(measures.get("matched_functions", 0))
    tf = int(measures.get("total_functions", 0))
    return {
        "functions_matched": mf,
        "functions_total": tf,
        "functions_pct": _pct(mf, tf),
        "fuzzy_pct": float(measures.get("fuzzy_match_percent", 0.0)),
        "linked_pct": float(measures.get("complete_code_percent", 0.0)),
        "data_pct": float(measures.get("matched_data_percent", 0.0)),
        "units": int(measures.get("total_units", 0)),
    }


def check_readme(text: str, exp: dict) -> list[str]:
    errs: list[str] = []
    m = re.search(
        r"Functions matched\s*\|\s*\*\*\s*([\d,]+)\s*/\s*([\d,]+)\s*\*\*"
        r"\s*\(\s*([\d.]+)\s*%\)", text)
    if not m:
        errs.append("README: 'Functions matched' row not found / unparseable")
    else:
        if int(_num(m.group(1))) != exp["functions_matched"]:
            errs.append(f"README functions matched {m.group(1)} "
                        f"!= {exp['functions_matched']:,}")
        if int(_num(m.group(2))) != exp["functions_total"]:
            errs.append(f"README functions total {m.group(2)} "
                        f"!= {exp['functions_total']:,}")
        if abs(_num(m.group(3)) - exp["functions_pct"]) > TOL:
            errs.append(f"README functions % {m.group(3)} "
                        f"!= {exp['functions_pct']:.2f}")
    for label, key in (("Code matched \\(fuzzy\\)", "fuzzy_pct"),
                       ("Code fully linked", "linked_pct"),
                       ("Data matched", "data_pct")):
        m = re.search(rf"{label}\s*\|\s*\*\*\s*([\d.]+)\s*%", text)
        if not m:
            errs.append(f"README: '{label}' row not found")
        elif abs(_num(m.group(1)) - exp[key]) > TOL:
            errs.append(f"README {label} {m.group(1)}% != {exp[key]:.2f}%")
    m = re.search(r"Translation units\s*\|\s*([\d,]+)", text)
    if not m:
        errs.append("README: 'Translation units' row not found")
    elif int(_num(m.group(1))) != exp["units"]:
        errs.append(f"README units {m.group(1)} != {exp['units']:,}")
    return errs


def reconcile(root: Path) -> list[str]:
    measures = json.loads((root / "progress" / "report.json").read_text()
                          ).get("measures", {})
    exp = expected_figures(measures)
    errs: list[str] = []
    readme = root / "README.md"
    if readme.exists():
        errs += check_readme(readme.read_text(), exp)
    else:
        errs.append("README.md missing")
    return errs


def main() -> int:
    report = ROOT / "progress" / "report.json"
    if not report.exists():
        print("progress/report.json missing — skipping doc reconciliation.")
        return 77
    errs = reconcile(ROOT)
    if errs:
        print("doc figures OUT OF SYNC with progress/report.json:")
        for e in errs:
            print("  -", e)
        print("Fix: update the README 'Progress' table to match progress/report.json.")
        return 1
    measures = json.loads(report.read_text()).get("measures", {})
    exp = expected_figures(measures)
    print(f"docs in sync: {exp['functions_matched']:,}/{exp['functions_total']:,} "
          f"functions ({exp['functions_pct']:.2f}%), fuzzy {exp['fuzzy_pct']:.2f}%, "
          f"linked {exp['linked_pct']:.2f}%, {exp['units']:,} units.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
