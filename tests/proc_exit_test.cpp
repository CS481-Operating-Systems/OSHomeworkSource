// EXPECT_EQ and ASSERT_EQ are macros
// EXPECT_EQ test execution and continues even if there is a failure
// ASSERT_EQ test execution and aborts if there is a failure
// The ASSERT_* variants abort the program execution if an assertion fails 
// while EXPECT_* variants continue with the run.

#include "gtest/gtest.h"
#include "src.hpp"

int counter = 0;

void grandchild()
{
}

void child()
{
    counter++;
}

void parent()
{
}

TEST(ProcessOrderTest, TestsInTests)
{
    for (int i = 0; i < 100; i++)
    {
        int pid = getpid();
        run_processes();

        ASSERT_EQ(getpid(), pid);
        ASSERT_LT(0, counter);
        printf("%d\n", counter);
    }
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    int ierr = 0;
    ierr += RUN_ALL_TESTS();

    return ierr;

}



