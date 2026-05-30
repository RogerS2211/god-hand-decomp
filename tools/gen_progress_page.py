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
        out.append({
            "n": u.get("name", "?"),
            "c": round(float(m.get("fuzzy_match_percent", 0.0)), 2),
            "mf": int(m.get("matched_functions", 0) or 0),
            "tf": int(m.get("total_functions", 0) or 0),
            "cat": meta.get("progress_category") or meta.get("category") or "",
            "auto": bool(meta.get("auto_generated", False)),
        })
    # most-complete first, then by size
    out.sort(key=lambda x: (-x["c"], -x["tf"]))
    return out


def render_html(measures: dict, units: list[dict]) -> str:
    fuzzy = float(measures.get("fuzzy_match_percent", 0.0))
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
        card(f"{mfunc:,} / {tfunc:,}", f"functions ({fpct:.2f}%)", fpct),
        card(f"{dpct:.2f}%", "data matched", dpct),
        card(f"{tunits:,}", "translation units", 100.0),
    ])

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
  .grid {{ display:grid; grid-template-columns:repeat(auto-fill,minmax(13px,1fr)); gap:3px; }}
  .cell {{ aspect-ratio:1/1; border-radius:2px; cursor:pointer; }}
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
    Live tracker: <a href="https://decomp.dev">decomp.dev</a>.</div>
</header>
<div class="cards">{cards}</div>
<div class="section">
  <div class="controls">
    <input id="q" type="search" placeholder="filter units by name…" autocomplete="off">
    <span id="count" class="sub"></span>
    <span class="legend">0%
      <i style="background:#e05d44"></i><i style="background:#fe7d37"></i>
      <i style="background:#dfb317"></i><i style="background:#a4a61d"></i>
      <i style="background:#97ca00"></i><i style="background:#4c1"></i>100%</span>
  </div>
  <div id="grid" class="grid"></div>
  <table id="tbl">
    <thead><tr>
      <th data-k="n">Unit</th><th data-k="c">Match&nbsp;%</th>
      <th data-k="mf">Funcs&nbsp;matched</th><th data-k="tf">Funcs&nbsp;total</th>
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
let sortK='c', sortDir=-1;
function rows(){{
  const f=q.value.trim().toLowerCase();
  return UNITS.filter(u=>!f||u.n.toLowerCase().includes(f))
    .sort((a,b)=>{{const x=a[sortK],y=b[sortK];
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
    d.title=u.n+'  —  '+u.c.toFixed(2)+'%  ('+u.mf+'/'+u.tf+' funcs)';
    gf.appendChild(d);
  }}
  grid.appendChild(gf);
  tb.innerHTML='';
  const tf=document.createDocumentFragment();
  for(const u of r){{
    const tr=document.createElement('tr');
    tr.innerHTML='<td class="name">'+u.n+'</td>'+
      '<td class="pct"><span class="mini"><span style="width:'+Math.min(u.c,100)+'%;background:'+color(u.c)+'"></span></span> '+u.c.toFixed(2)+'%</td>'+
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
    units = compact_units(report.get("units", []))

    DOCS.mkdir(exist_ok=True)
    (DOCS / "progress.html").write_text(render_html(measures, units))

    fuzzy = float(measures.get("fuzzy_match_percent", 0.0))
    fpct = float(measures.get("matched_functions_percent", 0.0))
    (DOCS / "badge_code.svg").write_text(
        make_badge("code matched", f"{fuzzy:.2f}%", color_for(fuzzy)))
    (DOCS / "badge_functions.svg").write_text(
        make_badge("functions", f"{fpct:.2f}%", color_for(fpct)))

    print(f"wrote {DOCS/'progress.html'}")
    print(f"wrote {DOCS/'badge_code.svg'}  (code {fuzzy:.2f}%)")
    print(f"wrote {DOCS/'badge_functions.svg'}  (functions {fpct:.2f}%)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv))
