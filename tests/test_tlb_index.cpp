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
    int VPN, k, index, tag;

    k = 2;
    VPN = 16;
    split_VPN(VPN, k, &index, &tag);
    ASSERT_EQ(index, 0);

    VPN = 17;
    split_VPN(VPN, k, &index, &tag);
    ASSERT_EQ(index, 1);

    VPN = 32;
    split_VPN(VPN, k, &index, &tag);
    ASSERT_EQ(index, 0);

    VPN = 33;
    split_VPN(VPN, k, &index, &tag);
    ASSERT_EQ(index, 1);

    k = 4;
    VPN = 16;
    split_VPN(VPN, k, &index, &tag);
    ASSERT_EQ(index, 0);

    VPN = 17;
    split_VPN(VPN, k, &index, &tag);
    ASSERT_EQ(index, 1);

    VPN = 18;
    split_VPN(VPN, k, &index, &tag);
    ASSERT_EQ(index, 2);

    VPN = 19;
    split_VPN(VPN, k, &index, &tag);
    ASSERT_EQ(index, 3);

}
