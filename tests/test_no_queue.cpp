// EXPECT_EQ and ASSERT_EQ are macros
// EXPECT_EQ test execution and continues even if there is a failure
// ASSERT_EQ test execution and aborts if there is a failure
// The ASSERT_* variants abort the program execution if an assertion fails 
// while EXPECT_* variants continue with the run.

#include "gtest/gtest.h"
#include "src.hpp"

lock_t my_lock;
int val;
int finished0, finished1;

int flag0, flag1, flag2, flag3;

void* thread0(void* arg)
{
    lock(&my_lock);
    flag0 = my_lock.flag;

    flag1 = my_lock.flag;
    unlock(&my_lock);

    finished0 = 1;

    return NULL;
}

void* thread1(void* arg)
{
    lock(&my_lock);
    flag2 = my_lock.flag;
    unlock(&my_lock);

    flag3 = my_lock.flag;

    finished1 = 1;

    return NULL;
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(TLBTest, TestsIntests)
{
    init(&my_lock);
    ASSERT_EQ(my_lock.queue.initialized, 1234);

    finished0 = 0;
    finished1 = 0;

    pthread_t pthread0;
    pthread_t pthread1;

    // Create thread 0, wait for it to finish
    pthread_create(&pthread0, NULL, thread0, NULL);
    while (!finished0)
        ASSERT_LT(my_lock.guard, 2);
    pthread_join(pthread0, NULL);
    ASSERT_EQ(my_lock.flag, 0);
    ASSERT_EQ(my_lock.guard, 0);

    // Create thread 1, wait for it to finish
    pthread_create(&pthread1, NULL, thread1, NULL);
    while (!finished1)
        ASSERT_LT(my_lock.guard, 2);
    pthread_join(pthread1, NULL);
    ASSERT_EQ(my_lock.flag, 0);
    ASSERT_EQ(my_lock.guard, 0);

    ASSERT_EQ(flag0, 1);
    ASSERT_EQ(flag1, 1);
    ASSERT_EQ(flag2, 1);
    ASSERT_EQ(flag3, 0);

    destroy(&my_lock);
}
