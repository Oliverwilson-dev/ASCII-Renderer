#!/usr/bin/env bash
set -e
SCRIPT_DIR="$(dirname "$0")"
"$SCRIPT_DIR/clean.sh"
"$SCRIPT_DIR/build.sh"
