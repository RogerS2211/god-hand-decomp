# GodHandFixDisasm.py -- Ghidra Jython. Fixes a project whose functions are
# 1-byte shells (created over un-disassembled bytes by an earlier bootstrap):
# remove the shells, disassemble at each entry, then recreate + name. Run
# headless on the existing program (preserves parsed data types):
#   analyzeHeadless <proj> GodHand -process SLUS_215.03 -noanalysis \
#     -scriptPath scripts/recon/ghidra -postScript GodHandFixDisasm.py
#@category GodHand
import os
from ghidra.program.model.symbol import SourceType
csv = os.path.join(os.path.dirname(getSourceFile().getAbsolutePath()), "gh_symbols.csv")
syms = []
for line in open(csv):
    line = line.strip()
    if line:
        h, n = line.split(",", 1)
        syms.append((long(h, 16), n))
# pass 1: remove shell functions so they don't block disassembly
for a, n in syms:
    f = getFunctionAt(toAddr(a))
    if f is not None:
        removeFunction(f)
# pass 2: disassemble at each entry (follows flow -> fills bodies)
dis = 0
for a, n in syms:
    addr = toAddr(a)
    if getInstructionAt(addr) is None:
        disassemble(addr)
        dis += 1
# pass 3: (re)create functions + apply names
created = shells = 0
for a, n in syms:
    addr = toAddr(a)
    f = getFunctionAt(addr)
    if f is None:
        f = createFunction(addr, n)
        if f is not None:
            created += 1
    if f is not None:
        if f.getName() != n:
            f.setName(n, SourceType.USER_DEFINED)
        if f.getBody().getNumAddresses() <= 1:
            shells += 1
    else:
        shells += 1
print("FixDisasm: disassembled %d, created %d functions, %d still-shell (undecodable entry)" % (dis, created, shells))
