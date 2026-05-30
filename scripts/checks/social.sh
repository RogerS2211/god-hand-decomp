#!/usr/bin/env bash
# Workflow advisories.  ALWAYS exit 0 or 78 — never fails the
# session.  Warnings here flag the session-retro convention without
# blocking the commit when they're intentionally false (e.g. a
# recon-only session that didn't touch source).
#
# Checks:
#   - Today has a session retro in sessions/YYYY-MM-DD-NN-*.md, OR
#     git status shows no edits to tracked source files (recon-only).
#   - No untracked files under asm/ (those should come from splat,
#     not from hand-edits).
#
# Exit codes:
#   0   no warnings
#   78  pass-with-warnings (dispatcher renders them inline)
set -uo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "$ROOT"

warns=()

# --- 1. session retro presence ---------------------------------------
# Local time --- session retros are dated in the operator's wall-clock
# timezone (sessions/YYYY-MM-DD-NN-*.md follows the local date); using
# UTC here produces spurious "no retro yet" warnings near timezone-
# crossing hours (e.g. PDT evening crossing into next-day UTC) even
# when the session is perfectly on time in local.
today="$(date +%Y-%m-%d)"
if ! ls "$ROOT/sessions" 2>/dev/null | grep -q "^${today}-[0-9][0-9]-.*\.md$"; then
    # Tolerate recon-only sessions: only warn if tracked source has
    # changed.  `git diff --quiet` returns 0 when no changes.
    if git -C "$ROOT" rev-parse --git-dir >/dev/null 2>&1; then
        if ! git -C "$ROOT" diff --quiet -- ':!sessions' \
                                                 ':!progress/report.json' \
            || ! git -C "$ROOT" diff --quiet --cached -- ':!sessions' \
                                                          ':!progress/report.json'
        then
            warns+=("no sessions/${today}-NN-*.md retro yet — write one before commit.")
        fi
    fi
fi

# --- 2. no untracked files under asm/ --------------------------------
if git -C "$ROOT" rev-parse --git-dir >/dev/null 2>&1; then
    untracked=$(git -C "$ROOT" ls-files --others --exclude-standard -- 'asm/' 2>/dev/null || true)
    if [[ -n "$untracked" ]]; then
        warns+=("untracked files under asm/ (asm/ should come from splat only):")
        while IFS= read -r f; do
            warns+=("    $f")
        done <<<"$untracked"
    fi
fi

if (( ${#warns[@]} > 0 )); then
    for w in "${warns[@]}"; do
        echo "WARN: $w"
    done
    exit 78
fi
exit 0
