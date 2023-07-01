#!/bin/bash

pushd vcpkg
./bootstrap-vcpkg.sh
./vcpkg integrate install
./vcpkg install zlib
./vcpkg install gtest
./vcpkg install benchmark
popd
