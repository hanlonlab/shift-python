#!/bin/bash
set -ex


./bootstrap

export CXXFLAGS="${CXXFLAGS}"

./configure --prefix="${PREFIX}" \
            --libdir="${PREFIX}/lib" \
            --with-ssl \
            --host="${HOST}"

make -j${CPU_COUNT}
make install