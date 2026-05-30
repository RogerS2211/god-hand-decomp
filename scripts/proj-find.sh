#!/usr/bin/env bash
# proj-find.sh — safe `find` wrapper for the god-hand-decomp repo.
#
# Why: the repo root holds a 1.5 GB ISO, ~744 MB of vendored tools, and
# ~120 MB of splat/compile output. A bare `find .` is slow and noisy;
# `find /` or `find ~` will hang for many minutes and is the foot-gun
# this wrapper exists to neutralise.
#
# Usage:
#   scripts/proj-find.sh                       # all files, default prunes
#   scripts/proj-find.sh -name '*.c'           # forwards predicates
#   scripts/proj-find.sh src -name 'cod*.c'    # first arg may be a path
#   scripts/proj-find.sh -type f -size +1M     # any find args
#
# The wrapper always operates relative to the repo root (cwd-independent)
# and ignores: God Hand (USA).iso, compiler/, tools/, .venv/, build/,
# asm/, bin/, ghidra/, disc_extract/, expected/, .git/, .pytest_cache/,
# __pycache__/. Override prunes by passing -no-prune-defaults as the
# first argument (rarely correct; use rg first).

set -uo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

NO_PRUNE=0
if [[ "${1:-}" == "-no-prune-defaults" ]]; then
    NO_PRUNE=1
    shift
fi

# Resolve an optional leading path arg; if absent, default to ROOT.
SEARCH_PATH="$ROOT"
if [[ $# -gt 0 && "$1" != -* ]]; then
    case "$1" in
        /*) SEARCH_PATH="$1" ;;
        *)  SEARCH_PATH="$ROOT/$1" ;;
    esac
    shift
fi

# Refuse to operate above the repo root.
case "$SEARCH_PATH" in
    "$ROOT"|"$ROOT"/*) : ;;
    *)
        printf 'proj-find: refusing to search above repo root: %s\n' "$SEARCH_PATH" >&2
        printf 'proj-find: ROOT=%s\n' "$ROOT" >&2
        exit 2
        ;;
esac

PRUNE_PATHS=(
    "$ROOT/God Hand (USA).iso"
    "$ROOT/compiler"
    "$ROOT/tools"
    "$ROOT/.venv"
    "$ROOT/build"
    "$ROOT/asm"
    "$ROOT/bin"
    "$ROOT/ghidra"
    "$ROOT/disc_extract"
    "$ROOT/expected"
    "$ROOT/.git"
    "$ROOT/.pytest_cache"
    "$ROOT/__pycache__"
)

PRUNE_EXPR=()
if [[ $NO_PRUNE -eq 0 ]]; then
    first=1
    PRUNE_EXPR=( '(' )
    for p in "${PRUNE_PATHS[@]}"; do
        if [[ $first -eq 1 ]]; then
            PRUNE_EXPR+=( -path "$p" )
            first=0
        else
            PRUNE_EXPR+=( -o -path "$p" )
        fi
    done
    PRUNE_EXPR+=( ')' -prune -o )
fi

# Default predicate when caller passes no expression: -print
USER_ARGS=( "$@" )
if [[ ${#USER_ARGS[@]} -eq 0 ]]; then
    USER_ARGS=( -print )
fi

# Glue: ( <prunes> ) -prune -o ( <user args> ) -print? — but only append
# -print if user didn't already supply an action (-print/-print0/-exec/-delete).
has_action=0
for a in "${USER_ARGS[@]}"; do
    case "$a" in
        -print|-print0|-exec|-execdir|-delete|-fprint|-fprint0|-ls|-fls|-printf|-fprintf|-quit)
            has_action=1; break ;;
    esac
done

if [[ $has_action -eq 0 ]]; then
    exec find "$SEARCH_PATH" "${PRUNE_EXPR[@]}" '(' "${USER_ARGS[@]}" ')' -print
else
    exec find "$SEARCH_PATH" "${PRUNE_EXPR[@]}" '(' "${USER_ARGS[@]}" ')'
fi
