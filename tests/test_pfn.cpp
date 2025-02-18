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

TEST(VPNTest, TestsIntests)
{
    int PFN, page_size, offset;
    int physical_address;

    page_size = 4096;
    offset = 256;
    PFN = 4096;
    physical_address = get_physical_address(PFN, offset, page_size);
    ASSERT_EQ(physical_address, 16777472);


    offset += 17;
    physical_address = get_physical_address(PFN, offset, page_size);
    ASSERT_EQ(physical_address, 16777489);

    PFN = 1024;
    offset = 4096;
    physical_address = get_physical_address(PFN, offset, page_size);
    ASSERT_EQ(physical_address, 4198400);


    page_size = 1024;
    offset = 256;
    PFN = 4096;
    physical_address = get_physical_address(PFN, offset, page_size);
    ASSERT_EQ(physical_address, 4194560);
}
