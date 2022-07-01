#!/bin/sh
ag -l | entr -s '/usr/bin/time -f "Elapsed time for build and tests: %E" ./build.sh'