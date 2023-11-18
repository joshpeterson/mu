#!/bin/sh
set -e
cmake -S . -B build -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build build
UBSAN_OPTIONS=print_stacktrace=1 ./build/mu --test
