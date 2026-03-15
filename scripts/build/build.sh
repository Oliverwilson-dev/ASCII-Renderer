#!/usr/bin/env bash
set -e
cd "$(dirname "$0")/../.."
mkdir -p build
cmake -S . -B build
cmake --build build
./bin/ascii_tests
