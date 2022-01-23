#!/bin/sh
set -e
# Change to -D PRODUCTION=ON to build without tests
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -D PRODUCTION=OFF
cmake --build build
./build/mu
