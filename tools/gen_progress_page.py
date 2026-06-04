#!/usr/bin/env python3
"""gen_progress_page.py — render the visual function tracker + badges.

Reads the objdiff progress report (``progress/report.json``, the same file
decomp.dev consumes) and emits three self-contained artifacts under ``docs/``:

    docs/progress.html        a single-file, offline-openable function tracker
    docs/badge_code.svg       shields-style badge: matched code %
    docs/badge_functions.svg  shields-style badge: matched functions %

The HTML embeds a *compact* per-unit summary (name, match %, function
counts, category) — not the full 3 MB report — so it stays small enough to
commit and opens directly from ``file://`` with no server or network.

Usage:
    python tools/gen_progress_page.py                  # uses progress/report.json
    python tools/gen_progress_page.py path/to/report.json

Re-run whenever ``progress/report.json`` changes (the CI workflow regenerates
nothing — it just uploads the report; the committed HTML/SVG are refreshed by
hand or by a pre-commit hook).
"""
from __future__ import annotations

import html
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
DOCS = ROOT / "docs"

# shields.io flat palette, low → high completion
_SCALE = [
    (0, "#e05d44"),    # red
    (25, "#fe7d37"),   # orange
    (50, "#dfb317"),   # yellow
    (75, "#a4a61d"),   # yellowgreen
    (90, "#97ca00"),   # green
    (100, "#4c1"),     # brightgreen
]


def color_for(pct: float) -> str:
    chosen = _SCALE[0][1]
    for threshold, col in _SCALE:
        if pct >= threshold:
            chosen = col
    return chosen


def human_bytes(n: int) -> str:
    """Compact human-readable byte size: '88 B', '233.5 KB', '2.71 MB'."""
    n = int(n)
    if n < 1024:
        return f"{n} B"
    if n < 1024 * 1024:
        return f"{n / 1024:.1f} KB"
    return f"{n / 1024 / 1024:.2f} MB"


def unit_code_bytes(unit: dict) -> tuple[int, int]:
    """Return (matched_bytes, total_bytes) for a unit, summed from its
    per-function ``size`` fields.  A function counts as matched only at
    100% fuzzy.  These sums reconcile exactly to the report's headline
    ``matched_code`` / ``total_code`` (see tests), so the tracker gets real
    byte sizes with no toolchain or build."""
    matched = total = 0
    for fn in unit.get("functions") or []:
        try:
            size = int(fn.get("size") or 0)
        except (TypeError, ValueError):
            size = 0
        total += size
        if fn.get("fuzzy_match_percent") == 100.0:
            matched += size
    return matched, total


def module_rollup(units: list[dict], categories: list[dict]) -> list[dict]:
    """Aggregate units into modules by their assigned progress category.

    Units with no category fall into an explicit ``unclassified`` bucket
    rather than being dropped, so module code totals always conserve the
    project total.  Once units are tagged (metadata.progress_categories /
    category) and the report is regenerated, real modules appear here."""
    names = {c.get("id"): c.get("name", c.get("id")) for c in (categories or [])}
    agg: dict[str, dict] = {}
    for u in units:
        meta = u.get("metadata", {}) or {}
        cat = meta.get("progress_category") or meta.get("category") or "unclassified"
        m = u.get("measures", {}) or {}
        mc, tc = unit_code_bytes(u)
        bucket = agg.setdefault(cat, {
            "id": cat,
            "name": names.get(cat, "Unclassified" if cat == "unclassified" else cat),
            "mc": 0, "tc": 0, "mf": 0, "tf": 0,
        })
        bucket["mc"] += mc
        bucket["tc"] += tc
        bucket["mf"] += int(m.get("matched_functions", 0) or 0)
        bucket["tf"] += int(m.get("total_functions", 0) or 0)
    return sorted(agg.values(), key=lambda d: d["tc"], reverse=True)


def _text_width(s: str) -> int:
    # crude monospace-ish estimate; good enough for badge layout
    return int(len(s) * 6.5) + 10


def make_badge(label: str, message: str, color: str) -> str:
    """Return a flat shields-style SVG badge (self-contained, no fonts)."""
    lw = _text_width(label)
    mw = _text_width(message)
    total = lw + mw
    lx = lw / 2 * 10
    mx = (lw + mw / 2) * 10
    return f"""<svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" width="{total}" height="20" role="img" aria-label="{html.escape(label)}: {html.escape(message)}">
  <title>{html.escape(label)}: {html.escape(message)}</title>
  <linearGradient id="s" x2="0" y2="100%">
    <stop offset="0" stop-color="#bbb" stop-opacity=".1"/>
    <stop offset="1" stop-opacity=".1"/>
  </linearGradient>
  <clipPath id="r"><rect width="{total}" height="20" rx="3" fill="#fff"/></clipPath>
  <g clip-path="url(#r)">
    <rect width="{lw}" height="20" fill="#555"/>
    <rect x="{lw}" width="{mw}" height="20" fill="{color}"/>
    <rect width="{total}" height="20" fill="url(#s)"/>
  </g>
  <g fill="#fff" text-anchor="middle" font-family="Verdana,Geneva,DejaVu Sans,sans-serif" font-size="110" text-rendering="geometricPrecision">
    <text aria-hidden="true" x="{lx:.0f}" y="150" fill="#010101" fill-opacity=".3" transform="scale(.1)" textLength="{(lw-10)*10:.0f}">{html.escape(label)}</text>
    <text x="{lx:.0f}" y="140" transform="scale(.1)" textLength="{(lw-10)*10:.0f}">{html.escape(label)}</text>
    <text aria-hidden="true" x="{mx:.0f}" y="150" fill="#010101" fill-opacity=".3" transform="scale(.1)" textLength="{(mw-10)*10:.0f}">{html.escape(message)}</text>
    <text x="{mx:.0f}" y="140" transform="scale(.1)" textLength="{(mw-10)*10:.0f}">{html.escape(message)}</text>
  </g>
</svg>
"""


def compact_units(units: list[dict]) -> list[dict]:
    out = []
    for u in units:
        m = u.get("measures", {}) or {}
        meta = u.get("metadata", {}) or {}
        mc, tc = unit_code_bytes(u)
        out.append({
            "n": u.get("name", "?"),
            "c": round(float(m.get("fuzzy_match_percent", 0.0)), 2),
            "mf": int(m.get("matched_functions", 0) or 0),
            "tf": int(m.get("total_functions", 0) or 0),
            "mc": mc,
            "tc": tc,
            "cat": meta.get("progress_category") or meta.get("category") or "",
            "auto": bool(meta.get("auto_generated", False)),
        })
    # biggest remaining gap first — surfaces the high-impact unmatched units
    out.sort(key=lambda x: (x["tc"] - x["mc"], x["tc"]), reverse=True)
    return out


_CAT_NAMES = {
    "cri-middleware": "CRI middleware",
    "sce-runtime": "SCE runtime",
    "crt": "C runtime (libc / libm / libstdc++ / libgcc)",
}


def library_panel(summary: dict | None) -> str:
    """Render the function-categories breakdown from progress/function_categories.json.

    These are functions in the game's own ``.text`` identified (by relocation-
    masked instruction-signature analysis, byte-identical modulo relocation) as
    standard-library / middleware / C-runtime code — i.e. *not* the engine code
    the decomp targets.  The axis is orthogonal to matched/INCLUDE_ASM: it says
    what subsystem a function belongs to, not whether it is decompiled yet."""
    if not summary:
        return ""
    order = ["cri-middleware", "sce-runtime", "crt"]
    rows = []
    for cid in order:
        s = summary.get(cid)
        if not s:
            continue
        pct = float(s.get("pct_of_text", 0.0))
        rows.append(
            f'<tr><td class="name">{html.escape(_CAT_NAMES.get(cid, cid))}</td>'
            f'<td>{int(s.get("count", 0)):,}</td>'
            f'<td class="pct"><span class="mini"><span style="width:{min(pct*4,100):.2f}%;'
            f'background:#8957e5"></span></span> {pct:.2f}%</td>'
            f'<td>{human_bytes(s.get("code_bytes", 0))}</td></tr>'
        )
    if not rows:
        return ""
    tot = summary.get("library_total", {})
    tpct = float(tot.get("pct_of_text", 0.0))
    rows.append(
        f'<tr style="font-weight:600;border-top:2px solid #30363d">'
        f'<td class="name">total identified</td><td>{int(tot.get("count", 0)):,}</td>'
        f'<td class="pct">{tpct:.2f}% of .text</td>'
        f'<td>{human_bytes(tot.get("code_bytes", 0))}</td></tr>'
    )
    return f"""<div class="section">
  <div class="h2">Library / middleware (identified)</div>
  <div class="hint">Functions in the game's <code>.text</code> identified as standard-library /
    middleware / C-runtime code (not the engine code the decomp targets), from
    <code>progress/function_categories.json</code>. Independent of the matched/INCLUDE_ASM axis.</div>
  <table class="modtbl">
    <thead><tr><th>Category</th><th>Functions</th><th>Share&nbsp;of&nbsp;.text</th><th>Code&nbsp;size</th></tr></thead>
    <tbody>{''.join(rows)}</tbody>
  </table>
</div>"""


def render_html(measures: dict, units: list[dict], modules: list[dict],
                lib_summary: dict | None = None) -> str:
    fuzzy = float(measures.get("fuzzy_match_percent", 0.0))
    linked = float(measures.get("complete_code_percent", 0.0))
    mfunc = int(measures.get("matched_functions", 0) or 0)
    tfunc = int(measures.get("total_functions", 0) or 0)
    fpct = float(measures.get("matched_functions_percent", 0.0))
    dpct = float(measures.get("matched_data_percent", 0.0))
    tunits = int(measures.get("total_units", len(units)) or len(units))
    data = json.dumps(units, separators=(",", ":"))

    def card(value, label, pct):
        return (
            f'<div class="card"><div class="bar"><span style="width:{min(pct,100):.2f}%;'
            f'background:{color_for(pct)}"></span></div>'
            f'<div class="v">{value}</div><div class="l">{label}</div></div>'
        )

    cards = "".join([
        card(f"{fuzzy:.2f}%", "code matched (fuzzy)", fuzzy),
        card(f"{linked:.2f}%", "code fully linked", linked),
        card(f"{mfunc:,} / {tfunc:,}", f"functions ({fpct:.2f}%)", fpct),
        card(f"{dpct:.2f}%", "data matched", dpct),
        card(f"{tunits:,}", "translation units", 100.0),
    ])

    def mod_row(mod):
        pct = 0.0 if mod["tc"] == 0 else 100.0 * mod["mc"] / mod["tc"]
        return (
            f'<tr><td class="name">{html.escape(mod["name"])}</td>'
            f'<td class="pct"><span class="mini"><span style="width:{min(pct,100):.2f}%;'
            f'background:{color_for(pct)}"></span></span> {pct:.2f}%</td>'
            f'<td>{human_bytes(mod["mc"])} / {human_bytes(mod["tc"])}</td>'
            f'<td>{mod["mf"]:,} / {mod["tf"]:,}</td></tr>'
        )

    modules_html = "".join(mod_row(m) for m in modules)
    n_modules = len([m for m in modules if m["id"] != "unclassified"])
    lib_html = library_panel(lib_summary)

    return f"""<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>God Hand decomp — progress</title>
<style>
  :root {{ color-scheme: dark; }}
  * {{ box-sizing: border-box; }}
  body {{ margin:0; font-family: ui-sans-serif,system-ui,-apple-system,Segoe UI,Roboto,sans-serif;
         background:#0d1117; color:#e6edf3; }}
  header {{ padding:28px 24px 8px; }}
  h1 {{ margin:0 0 4px; font-size:22px; letter-spacing:.2px; }}
  .sub {{ color:#8b949e; font-size:13px; }}
  .cards {{ display:grid; grid-template-columns:repeat(auto-fit,minmax(190px,1fr)); gap:12px; padding:16px 24px; }}
  .card {{ background:#161b22; border:1px solid #30363d; border-radius:10px; padding:14px 16px; }}
  .card .v {{ font-size:24px; font-weight:600; }}
  .card .l {{ color:#8b949e; font-size:12px; margin-top:2px; }}
  .bar {{ height:6px; background:#21262d; border-radius:4px; overflow:hidden; margin-bottom:10px; }}
  .bar span {{ display:block; height:100%; }}
  .section {{ padding:8px 24px 32px; }}
  .controls {{ display:flex; gap:10px; align-items:center; margin:6px 0 14px; flex-wrap:wrap; }}
  input[type=search] {{ background:#0d1117; border:1px solid #30363d; color:#e6edf3; border-radius:6px;
         padding:7px 10px; font-size:13px; min-width:240px; }}
  .legend {{ display:flex; gap:6px; align-items:center; color:#8b949e; font-size:12px; margin-left:auto; }}
  .legend i {{ width:14px; height:14px; border-radius:3px; display:inline-block; }}
  .grid {{ display:flex; flex-wrap:wrap; gap:3px; align-content:flex-start; }}
  .cell {{ height:16px; border-radius:2px; cursor:pointer; flex:0 0 auto; }}
  .h2 {{ font-size:14px; color:#e6edf3; margin:6px 0 2px; font-weight:600; }}
  .hint {{ color:#6e7681; font-size:12px; margin:2px 0 14px; }}
  .modtbl {{ margin:0 0 8px; }}
  table {{ width:100%; border-collapse:collapse; margin-top:22px; font-size:13px; }}
  th,td {{ text-align:left; padding:6px 10px; border-bottom:1px solid #21262d; }}
  th {{ color:#8b949e; font-weight:500; cursor:pointer; user-select:none; position:sticky; top:0; background:#0d1117; }}
  td.pct {{ font-variant-numeric:tabular-nums; }}
  .mini {{ display:inline-block; width:90px; height:8px; background:#21262d; border-radius:4px; vertical-align:middle; overflow:hidden; }}
  .mini span {{ display:block; height:100%; }}
  .name {{ font-family:ui-monospace,SFMono-Regular,Menlo,monospace; }}
  a {{ color:#58a6ff; }}
  footer {{ color:#6e7681; font-size:12px; padding:0 24px 28px; }}
</style>
</head>
<body>
<header>
  <h1>God Hand (SLUS-21503) — matching decompilation</h1>
  <div class="sub">Per–translation-unit progress, generated from
    <code>progress/report.json</code> by <code>tools/gen_progress_page.py</code>.
    Units are sorted by largest remaining gap.</div>
</header>
<div class="cards">{cards}</div>
<div class="section">
  <div class="h2">Modules</div>
  <div class="hint">{n_modules} classified module(s) · code matched / total. Assign
    units to categories in <code>objdiff.json</code> and regenerate to break the
    boot ELF out by subsystem.</div>
  <table class="modtbl">
    <thead><tr><th>Module</th><th>Match&nbsp;%</th><th>Code (matched&nbsp;/&nbsp;total)</th><th>Funcs</th></tr></thead>
    <tbody>{modules_html}</tbody>
  </table>
</div>
{lib_html}
<div class="section">
  <div class="h2">Translation units</div>
  <div class="controls">
    <input id="q" type="search" placeholder="filter units by name…" autocomplete="off">
    <span id="count" class="sub"></span>
    <span class="legend">0%
      <i style="background:#e05d44"></i><i style="background:#fe7d37"></i>
      <i style="background:#dfb317"></i><i style="background:#a4a61d"></i>
      <i style="background:#97ca00"></i><i style="background:#4c1"></i>100%</span>
  </div>
  <div class="hint">Heat-map cells are sized by code bytes — the big red blocks are the high-impact gaps.</div>
  <div id="grid" class="grid"></div>
  <table id="tbl">
    <thead><tr>
      <th data-k="n">Unit</th><th data-k="c">Match&nbsp;%</th>
      <th data-k="u">Remaining</th><th data-k="tc">Code&nbsp;size</th>
      <th data-k="mf">Funcs&nbsp;✓</th><th data-k="tf">Funcs</th>
      <th data-k="cat">Category</th>
    </tr></thead>
    <tbody></tbody>
  </table>
</div>
<footer>God Hand decomp · preservation &amp; research project · not affiliated with Capcom or Sony.</footer>
<script>
const UNITS = {data};
const SCALE = [[0,"#e05d44"],[25,"#fe7d37"],[50,"#dfb317"],[75,"#a4a61d"],[90,"#97ca00"],[100,"#4c1"]];
function color(p){{let c=SCALE[0][1];for(const[t,col]of SCALE)if(p>=t)c=col;return c;}}
const grid=document.getElementById('grid'), tb=document.querySelector('#tbl tbody'),
      q=document.getElementById('q'), count=document.getElementById('count');
function hb(n){{n=+n;if(n<1024)return n+' B';if(n<1048576)return (n/1024).toFixed(1)+' KB';return (n/1048576).toFixed(2)+' MB';}}
const keyval=(u,k)=> k==='u' ? (u.tc-u.mc) : u[k];
let sortK='u', sortDir=-1;
function rows(){{
  const f=q.value.trim().toLowerCase();
  return UNITS.filter(u=>!f||u.n.toLowerCase().includes(f))
    .sort((a,b)=>{{const x=keyval(a,sortK),y=keyval(b,sortK);
      if(typeof x==='number')return (x-y)*sortDir;
      return String(x).localeCompare(String(y))*sortDir;}});
}}
function render(){{
  const r=rows();
  count.textContent=r.length+' / '+UNITS.length+' units';
  grid.innerHTML='';
  const gf=document.createDocumentFragment();
  for(const u of r){{
    const d=document.createElement('div');
    d.className='cell'; d.style.background=color(u.c);
    d.style.width=Math.max(6,Math.min(64,Math.sqrt(u.tc)/3.5)).toFixed(0)+'px';
    d.title=u.n+'  —  '+u.c.toFixed(2)+'%  ('+hb(u.mc)+' / '+hb(u.tc)+', '+u.mf+'/'+u.tf+' funcs)';
    gf.appendChild(d);
  }}
  grid.appendChild(gf);
  tb.innerHTML='';
  const tf=document.createDocumentFragment();
  for(const u of r){{
    const tr=document.createElement('tr');
    tr.innerHTML='<td class="name">'+u.n+'</td>'+
      '<td class="pct"><span class="mini"><span style="width:'+Math.min(u.c,100)+'%;background:'+color(u.c)+'"></span></span> '+u.c.toFixed(2)+'%</td>'+
      '<td>'+hb(u.tc-u.mc)+'</td><td>'+hb(u.tc)+'</td>'+
      '<td>'+u.mf+'</td><td>'+u.tf+'</td><td>'+(u.cat||'')+'</td>';
    tf.appendChild(tr);
  }}
  tb.appendChild(tf);
}}
q.addEventListener('input',render);
document.querySelectorAll('#tbl th').forEach(th=>th.addEventListener('click',()=>{{
  const k=th.dataset.k; if(k===sortK)sortDir*=-1; else {{sortK=k; sortDir=(k==='n'||k==='cat')?1:-1;}}
  render();
}}));
render();
</script>
</body>
</html>
"""


def main(argv: list[str]) -> int:
    report_path = Path(argv[1]) if len(argv) > 1 else ROOT / "progress" / "report.json"
    if not report_path.exists():
        print(f"error: report not found: {report_path}", file=sys.stderr)
        return 1
    report = json.loads(report_path.read_text())
    measures = report.get("measures", {})
    raw_units = report.get("units", [])
    modules = module_rollup(raw_units, report.get("categories", []))
    units = compact_units(raw_units)

    cats_path = ROOT / "progress" / "function_categories.json"
    lib_summary = None
    if cats_path.exists():
        lib_summary = json.loads(cats_path.read_text()).get("summary")

    DOCS.mkdir(exist_ok=True)
    (DOCS / "progress.html").write_text(
        render_html(measures, units, modules, lib_summary))

    fuzzy = float(measures.get("fuzzy_match_percent", 0.0))
    linked = float(measures.get("complete_code_percent", 0.0))
    fpct = float(measures.get("matched_functions_percent", 0.0))
    (DOCS / "badge_code.svg").write_text(
        make_badge("code matched", f"{fuzzy:.2f}%", color_for(fuzzy)))
    (DOCS / "badge_linked.svg").write_text(
        make_badge("fully linked", f"{linked:.2f}%", color_for(linked)))
    (DOCS / "badge_functions.svg").write_text(
        make_badge("functions", f"{fpct:.2f}%", color_for(fpct)))

    print(f"wrote {DOCS/'progress.html'}")
    print(f"wrote {DOCS/'badge_code.svg'}  (code {fuzzy:.2f}%)")
    print(f"wrote {DOCS/'badge_linked.svg'}  (linked {linked:.2f}%)")
    print(f"wrote {DOCS/'badge_functions.svg'}  (functions {fpct:.2f}%)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv))
