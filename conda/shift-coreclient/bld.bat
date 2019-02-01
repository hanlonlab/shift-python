cd LibCoreClient
mkdir build
#cmake -G "Visual Studio 15 2017 Win64" -DCMAKE_INSTALL_PREFIX:PATH="${PREFIX}" ..

[ -d ./build/shift_coreclient.dir ] && ls ./build/shift_coreclient.dir | grep -v "Release" | sed 's/^/.\/build\/shift_coreclient.dir\//'| xargs rm -r
[ -d ./build ] && ls ./build | grep -v "Release" | grep -v "shift_coreclient.dir" | sed 's/^/.\/build\//' | xargs rm -r
cmake -H. -B./build -G"Visual Studio 15 2017" -DCMAKE_BUILD_TYPE=Debug
cmake --build ./build --target ALL_BUILD --config Debug

# Release library
[ -d ./build/shift_coreclient.dir ] && ls ./build/shift_coreclient.dir | grep -v "Debug" | sed 's/^/.\/build\/shift_coreclient.dir\//'| xargs rm -r
[ -d ./build ] && ls ./build | grep -v "Debug" | grep -v "shift_coreclient.dir" | sed 's/^/.\/build\//' | xargs rm -r
cmake -H. -B./build -G"Visual Studio 15 2017" -DCMAKE_BUILD_TYPE=Release
cmake --build ./build --target ALL_BUILD --config Release

# Delete CMake files
[ -d ./build ] && ls ./build | grep -v "Debug" | grep -v "Release" | grep -v "shift_coreclient.dir" | sed 's/^/.\/build\//' | xargs rm -r


make install
