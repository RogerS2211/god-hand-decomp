"""Make the repo root importable so `import compile` works under pytest.

The build entry point lives at the repo root as ``compile.py``; pytest's
default rootdir is ``tests/``, so we prepend the repo root explicitly here
rather than relying on per-test ``sys.path`` munging.
"""
from __future__ import annotations

import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))
