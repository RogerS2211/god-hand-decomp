"""Unit tests for scripts/verify_rel_splat_roundtrip.py.

These pin the line-format contract that `rebuild_asm()` enforces against
splat 0.40 / spimdisasm 1.40.3 output. If a future splat or spimdisasm
release changes the comment format, these tests will catch the drift
before the on-disc REL round-trip breaks.

The end-to-end round-trip against `disc_extract/rel/r207.rel` is
exercised by `scripts/checks/rel-splat.sh` (a session_check sub-check);
these unit tests focus on the byte-re-encoding edge cases that are
hard to provoke from the real-input path alone.
"""

from __future__ import annotations

import importlib.util
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parent.parent


def _load_module():
    spec = importlib.util.spec_from_file_location(
        "verify_rel_splat_roundtrip",
        ROOT / "scripts" / "verify_rel_splat_roundtrip.py",
    )
    mod = importlib.util.module_from_spec(spec)
    assert spec.loader is not None
    spec.loader.exec_module(mod)
    return mod


VR = _load_module()


def _write(tmp_path: Path, body: str) -> Path:
    p = tmp_path / "snippet.s"
    p.write_text(body)
    return p


def test_rebuild_asm_empty_file(tmp_path):
    p = _write(tmp_path, "")
    assert VR.rebuild_asm(p) == b""


def test_rebuild_asm_skips_directives_and_labels(tmp_path):
    body = """\
.include "macro.inc"
.set noat
.set noreorder
.section .text, "ax"

glabel func_00000100
endlabel func_00000100
nonmatching func_00000100, 0x4
"""
    p = _write(tmp_path, body)
    assert VR.rebuild_asm(p) == b""


def test_rebuild_asm_trailing_hex_form(tmp_path):
    # Two MIPS instructions in the splat trailing-HEX form:
    #   lui $v0, 0
    #   addiu $sp, $sp, -0x10
    body = """\
glabel func_00000100
    /* 100 00000100 0000023C */  lui        $v0, (0x0 >> 16)
    /* 104 00000104 F0FFBD27 */  addiu      $sp, $sp, -0x10
endlabel func_00000100
"""
    p = _write(tmp_path, body)
    # Little-endian bytes for the two instructions (taken from the
    # hex comment field):
    assert VR.rebuild_asm(p) == bytes.fromhex("0000023CF0FFBD27")


def test_rebuild_asm_bare_hex_line(tmp_path):
    # A bare /* HEX */ line on its own contributes its bytes (used
    # by spimdisasm for asciz body + alignment pad in data segments;
    # asm rarely uses it but the helper supports it for symmetry
    # with scripts/verify_splat_roundtrip.py).
    body = """\
    /* DEADBEEF */
"""
    p = _write(tmp_path, body)
    assert VR.rebuild_asm(p) == bytes.fromhex("DEADBEEF")


def test_rebuild_asm_align_pads_when_misaligned(tmp_path):
    # One byte, then .align 2 (= 4-byte boundary). Expect 3 zero pad
    # bytes to bring the cursor to offset 4.  This is a synthetic
    # case — real MIPS .text is always 4-byte aligned so .align 2 is
    # a no-op in practice — but we keep the safety net.
    body = """\
    /* AB */
.align 2
    /* CD */
"""
    p = _write(tmp_path, body)
    assert VR.rebuild_asm(p) == bytes.fromhex("AB000000CD")


def test_rebuild_asm_align_noop_when_already_aligned(tmp_path):
    # 4 bytes (already 4-byte aligned), then .align 2 — no padding.
    body = """\
    /* 100 00000100 0000023C */  lui $v0, (0x0 >> 16)
.align 2
    /* 104 00000104 F0FFBD27 */  addiu $sp, $sp, -0x10
"""
    p = _write(tmp_path, body)
    assert VR.rebuild_asm(p) == bytes.fromhex("0000023CF0FFBD27")


def test_check_one_passes_for_r207(tmp_path):
    """End-to-end smoke: the registry entry for r207 round-trips."""
    # This re-uses the on-disc REL via the script's RELS registry.
    # If splat has not yet been run, the check returns 77 (skip);
    # we accept either 0 or 77 here so the test passes on a fresh
    # clone before the REL splat outputs land.
    rc = VR.check_one(VR.RELS[0])
    assert rc in (0, 77)
