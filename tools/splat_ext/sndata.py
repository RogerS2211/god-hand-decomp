"""splat extension: SN-Systems-linker .sndata segment.

The SCE PS2 ee-gcc toolchain emits a separate `.sndata` section for the
SN Systems linker small-data convention (distinct from gcc's `.sdata`).
splat ships an `sdata` segment type but no `sndata`; this extension is a
one-liner subclass that just changes the output linker section name.
"""

from splat.segtypes.common.data import CommonSegData


class PS2SegSndata(CommonSegData):
    def get_linker_section(self) -> str:
        return ".sndata"
