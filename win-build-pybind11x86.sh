cd pybind11
rm -r build

cmake -H. -B./build -G"Visual Studio 15 2017"
cmake --build ./build --config Release --target check
