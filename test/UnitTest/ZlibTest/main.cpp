#include <iostream>

#include "zlib.h"
#include "gtest/gtest.h"

TEST(ZLibTest, ZLibVersionTest)
{ 
    std::cout << zlibVersion() << std::endl;
}