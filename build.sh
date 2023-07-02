#!/bin/bash

mkdir -p linuxbuild
pushd linuxbuild
cmake -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
popd
