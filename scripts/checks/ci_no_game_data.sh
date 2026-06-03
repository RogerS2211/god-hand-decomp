#!/usr/bin/env bash
# ci_no_game_data.sh — fail a PR that adds copyrighted game data, SDK
# binaries, or other derived/binary blobs.
#
# The #1 project rule is "never commit game assets, ripped data, ROMs/ISOs,
# SDK binaries, or any copyrighted material" (CONTRIBUTING.md).  This guard
# enforces it mechanically on every PR.  Two layers:
#
#   1. A precise denylist of game-data / SDK / boot-ELF / derived-artifact
#      paths (anchored so it never trips on the legitimately-tracked
#      config/SLUS_215.03.{lcf,yaml} text files).
#   2. A binary-file backstop: this repo is intentionally 100% text, so any
#      newly-added *binary* file (git treats it as binary) is rejected even
#      if the denylist missed it — catches a renamed ISO, a stray .o, etc.
#
# The single allowed payload under disc_extract/ is rel/manifest.json.
#
# Usage:
#   scripts/checks/ci_no_game_data.sh [FILE ...]   # check exactly these paths
#   scripts/checks/ci_no_game_data.sh              # check files changed vs
#                                                  #   $DIFF_BASE (default
#                                                  #   origin/main)
#
# Exit codes: 0 = clean, 1 = leak found, 77 = skip (cannot determine the
# changed set and no paths were given).
set -uo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "$ROOT"

ALLOWED_LEAF="disc_extract/rel/manifest.json"

# Game data, SDK toolchain, the carved boot ELF, and derived binaries.
# Matched case-insensitively against each repo-relative path.
DENY_RE='\.(iso|afs|img|irx|fst|elf|o|map|lst|bin)$|^SLUS_[0-9]|(^|/)GODHAND\.|^disc_extract/|^compiler/|^tools/wibo$|^tools/objdiff-cli$|^tools/(m2c|asm-differ|decomp-permuter)/'

# Collect the candidate paths.
declare -a FILES=()
if [[ $# -gt 0 ]]; then
    FILES=("$@")
else
    BASE="${DIFF_BASE:-origin/main}"
    if ! git rev-parse --git-dir >/dev/null 2>&1; then
        echo "ci_no_game_data: not a git repo and no paths given — skip."
        exit 77
    fi
    if ! git rev-parse --verify -q "$BASE" >/dev/null; then
        echo "ci_no_game_data: base ref '$BASE' not found — skip."
        echo "  (set DIFF_BASE, or pass paths explicitly)"
        exit 77
    fi
    mapfile -t FILES < <(git diff --name-only --diff-filter=ACMR "$BASE"...HEAD)
fi

if [[ ${#FILES[@]} -eq 0 ]]; then
    echo "ci_no_game_data: no changed files to check."
    exit 0
fi

# Is a path a binary file on disk?  Uses git's own binary heuristic:
# `git diff --numstat` prints "-\t-\t..." for binary content, real counts
# for text.  (git diff --no-index exits non-zero whenever the files differ,
# so we read its stdout rather than its exit status, which pipefail would
# otherwise turn into a false negative.)
is_binary() {
    local f="$1" stat
    [[ -f "$f" ]] || return 1
    stat=$(git diff --numstat --no-index /dev/null "$f" 2>/dev/null)
    [[ "$stat" == "-"$'\t'"-"* ]]
}

declare -a VIOLATIONS=()
for f in "${FILES[@]}"; do
    [[ "$f" == "$ALLOWED_LEAF" ]] && continue
    if printf '%s\n' "$f" | grep -iqE "$DENY_RE"; then
        VIOLATIONS+=("$f  (game data / SDK / derived artifact)")
        continue
    fi
    if is_binary "$f"; then
        VIOLATIONS+=("$f  (binary file — this repo is text-only)")
    fi
done

if [[ ${#VIOLATIONS[@]} -gt 0 ]]; then
    echo "ci_no_game_data: ${#VIOLATIONS[@]} disallowed file(s) in this change:"
    for v in "${VIOLATIONS[@]}"; do
        echo "   - $v"
    done
    echo
    echo "Never commit game assets, ripped data, ROMs/ISOs, SDK binaries, or"
    echo "any copyrighted material.  Supply your own dumped disc locally."
    exit 1
fi

echo "ci_no_game_data: ${#FILES[@]} changed file(s) checked; no game data."
exit 0
