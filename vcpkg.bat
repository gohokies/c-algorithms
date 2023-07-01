pushd vcpkg

call bootstrap-vcpkg.bat
vcpkg integrate install

vcpkg install zlib
vcpkg install gtest
vcpkg install benchmark

popd
