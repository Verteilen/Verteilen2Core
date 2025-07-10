#/bin/bash
echo Start Building...
mkdir cmake-build-debug
cd cmake-build-debug
cmake -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" -S .. -B .
cd ..
cmake --build cmake-build-debug --target all -- -j 8
cmake --build cmake-build-debug --target all -- -j 8
