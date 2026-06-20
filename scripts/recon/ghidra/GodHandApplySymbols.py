# GodHandApplySymbols.py -- Ghidra Jython. Applies god-hand-decomp function
# symbols (names + boundaries) from gh_symbols.csv (sibling file).
#@category GodHand
import os
from ghidra.program.model.symbol import SourceType
csv = os.path.join(os.path.dirname(getSourceFile().getAbsolutePath()), "gh_symbols.csv")
created = renamed = labeled = 0
f = open(csv)
for line in f:
    line = line.strip()
    if not line:
        continue
    hexa, name = line.split(",", 1)
    addr = toAddr(long(hexa, 16))
    fn = getFunctionAt(addr)
    if fn is None:
        try:
            fn = createFunction(addr, name)
        except:
            fn = None
        if fn is not None:
            created += 1
    if fn is not None:
        if fn.getName() != name:
            fn.setName(name, SourceType.USER_DEFINED)
            renamed += 1
    else:
        createLabel(addr, name, True)
        labeled += 1
f.close()
print("GodHand symbols: created %d, named %d, labeled %d" % (created, renamed, labeled))
