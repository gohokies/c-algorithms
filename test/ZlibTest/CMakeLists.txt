find_package(ZLIB REQUIRED)

add_executable(ZlibTest main.cpp)

target_link_libraries(ZlibTest ZLIB::ZLIB)
target_link_libraries(ZlibTest GTest::gtest GTest::gtest_main)

add_test(NAME ZlibTest COMMAND ZlibTest)
