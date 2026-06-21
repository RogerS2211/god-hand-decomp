# GodHandNameAfterAnalysis.py -- Ghidra Jython, run AFTER auto-analysis.
# Fix shells, create missing functions, apply decomp names. Error-tolerant:
# a duplicate-name or bad-address on one function never aborts the rest.
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
created = named = shells = errs = 0
for a, n in syms:
    try:
        addr = toAddr(a)
        if getInstructionAt(addr) is None:
            disassemble(addr)
        f = getFunctionAt(addr)
        if f is not None and f.getBody().getNumAddresses() <= 1:
            removeFunction(f)
            f = None
            if getInstructionAt(addr) is None:
                disassemble(addr)
        if f is None:
            f = createFunction(addr, n)
            if f is not None:
                created += 1
        if f is not None:
            if f.getName() != n:
                try:
                    f.setName(n, SourceType.USER_DEFINED)
                    named += 1
                except:
                    # name collision -> uniquify with address suffix
                    try:
                        f.setName("%s_%06X" % (n, a & 0xFFFFFF), SourceType.USER_DEFINED)
                        named += 1
                    except:
                        errs += 1
            if f.getBody().getNumAddresses() <= 1:
                shells += 1
        else:
            shells += 1
    except:
        errs += 1
print("NameAfterAnalysis: created %d, named %d, %d shells, %d errs" % (created, named, shells, errs))
