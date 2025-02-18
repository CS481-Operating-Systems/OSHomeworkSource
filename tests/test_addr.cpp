// EXPECT_EQ and ASSERT_EQ are macros
// EXPECT_EQ test execution and continues even if there is a failure
// ASSERT_EQ test execution and aborts if there is a failure
// The ASSERT_* variants abort the program execution if an assertion fails 
// while EXPECT_* variants continue with the run.

#include "gtest/gtest.h"
#include "src.hpp"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}

TEST(PageTableTest, TestsIntests)
{
    int addr;

    int page_size = 4;
    int offset = 0;
    int PFN = 2;
    addr = get_physical_address(PFN, offset, page_size);
    ASSERT_EQ(addr, 8);

    offset = 1;
    addr = get_physical_address(PFN, offset, page_size);
    ASSERT_EQ(addr, 9);

    page_size = 16;
    offset = 0;
    PFN = 8;
    addr = get_physical_address(PFN, offset, page_size);
    ASSERT_EQ(addr, 128);

    offset = 8;
    addr = get_physical_address(PFN, offset, page_size);
    ASSERT_EQ(addr, 136);

}
