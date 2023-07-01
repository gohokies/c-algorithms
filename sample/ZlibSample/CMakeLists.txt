find_package(ZLIB REQUIRED)

add_executable(ZLibSample example.cpp)

target_link_libraries(ZLibSample ZLIB::ZLIB)