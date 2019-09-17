mkdir build && cd build
cmake -DCMAKE_CXX_FLAGS="${CMAKE_CXX_FLAGS} -Wno-deprecated -Wno-overloaded-virtual" -DCMAKE_BUILD_TYPE=RelWithDebInfo -DHAVE_SSL=ON -DCMAKE_INSTALL_PREFIX:PATH="${PREFIX}" -DCMAKE_PREFIX_PATH="${PREFIX}" ..
make install
