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

TEST(TLBTest, TestsIntests)
{
    remove("journal.txt");
    char txb[] = "txe12";
    char ib[] = "ib";
    char bb[] = "bb";
    char str[] = "hello world";
    char txe[] = "";
    write_to_journal(sizeof(txb)-1, txb, sizeof(ib)-1, ib, sizeof(bb)-1, bb, sizeof(str)-1, str, sizeof(txe), txe);

    sleep(1);

    char txe_err[] = "txe21";
    int err = checkpoint(sizeof(txe_err), txe_err);
    ASSERT_EQ(err, -1);

}
