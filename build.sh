#!/bin/sh
set -e
# Add -D PRODUCTION=ON to build without tests
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/mu
