# Ghidra + MCP setup (God Hand)

A pre-bootstrapped Ghidra project + MCP bridge so Claude can query Ghidra
(decompile, xrefs, structs) over MCP. Installed under ~ (WSL).

## What's already done (headless, by Claude)
- JDK 21 → ~/jdk21 ; Ghidra 11.3.2 → ~/ghidra_11.3.2_PUBLIC
- MCP bridge venv → ~/ghidra-mcp-venv ; bridge → ~/ghidra-mcp/bridge_mcp_ghidra.py
- GhidraMCP 1.4 extension staged → ~/ghidra_11.3.2_PUBLIC/Extensions/Ghidra/GhidraMCP-1-4.zip
- Project → ~/ghidra-projects/GodHand (program SLUS_215.03), with all 8528
  decomp functions created + named (scripts/recon/ghidra/gh_symbols.csv).
- Claude Code MCP config → .mcp.json (project root; gitignored).

## Finish in the Ghidra GUI (your steps, via WSLg)
1. Launch: `JAVA_HOME=~/jdk21 ~/ghidra_11.3.2_PUBLIC/ghidraRun`
2. File > Install Extensions > check **GhidraMCP** > OK > restart Ghidra.
3. Open project ~/ghidra-projects/GodHand, open SLUS_215.03 in CodeBrowser.
   When asked "configure new plugins?" enable **GhidraMCPPlugin** (it starts an
   HTTP server on :8080). (Else: File > Configure > search GhidraMCP.)
4. (Optional, for types) File > Parse C Source > add scripts/recon/ghidra/gh_engine.h.
5. (Optional, better decompiles) Analysis > Auto Analyze (the GUI doesn't hit
   the headless timing-report bug that blocked auto-analysis).

## Connect Claude
- Reload Claude Code so it reads .mcp.json; approve the `ghidra` server.
- Verify the bridge sees Ghidra: `~/ghidra-mcp-venv/bin/python ~/ghidra-mcp/bridge_mcp_ghidra.py` should reach http://127.0.0.1:8080/ while Ghidra+plugin run.
