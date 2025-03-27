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
    lock_t my_lock;

    init(&my_lock);
    ASSERT_EQ(my_lock.queue.initialized, 1234);
    ASSERT_EQ(my_lock.flag, 0);
    ASSERT_EQ(my_lock.guard, 0);
    ASSERT_EQ(queue_empty(my_lock.queue), 1);

    lock(&my_lock);
    ASSERT_EQ(my_lock.flag, 1);
    ASSERT_EQ(my_lock.guard, 0);
    
    unlock(&my_lock);
    ASSERT_EQ(my_lock.flag, 0);
    ASSERT_EQ(my_lock.guard, 0);
}
