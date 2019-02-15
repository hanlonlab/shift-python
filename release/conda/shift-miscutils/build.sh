cd LibMiscUtils
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX:PATH="${PREFIX}" -DCMAKE_PREFIX_PATH="${PREFIX}" ..
make install
