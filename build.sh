#!/bin/sh
set -e
cmake -S . -B build -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build build
./build/mu --test
