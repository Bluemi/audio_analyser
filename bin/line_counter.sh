#!/bin/bash
echo "src:"
wc -l `find -wholename "./src/*.cpp" -o -wholename "./src/*.hpp"` | sort -g
echo
echo "tests:"
wc -l `find -wholename "./tests/*.cpp" -o -wholename "./tests/*.hpp"` | sort -g
