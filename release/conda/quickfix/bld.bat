mkdir build & cd build
cmake -DHAVE_SSL=ON -G "Visual Studio 15 2017 Win64" -DCMAKE_INSTALL_PREFIX:PATH="${PREFIX}" ..
