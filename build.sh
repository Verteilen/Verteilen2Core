#/bin/bash
echo Start Building...
cmake -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" -S . -B ./cmake-build-debug
cmake --build cmake-build-debug --target all -- -j 14