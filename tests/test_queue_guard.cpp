// EXPECT_EQ and ASSERT_EQ are macros
// EXPECT_EQ test execution and continues even if there is a failure
// ASSERT_EQ test execution and aborts if there is a failure
// The ASSERT_* variants abort the program execution if an assertion fails 
// while EXPECT_* variants continue with the run.

#include "gtest/gtest.h"
#include "src.hpp"

lock_t my_lock;
int val;
bool first;
bool finished0, finished1;
bool thread0bool, thread1bool;

void* thread0(void* arg)
{
    lock(&my_lock);
    unlock(&my_lock);
    finished0 = true;

    return NULL;
}

void* thread1(void* arg)
{
    while (!finished0);

    lock(&my_lock);
    unlock(&my_lock);
    finished1 = true;

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
    first = false;
    finished0 = finished1 = false;
    ASSERT_EQ(my_lock.queue.initialized, 1234);

    pthread_t pthread0;
    pthread_t pthread1;

    pthread_create(&pthread0, NULL, thread0, NULL);
    pthread_create(&pthread1, NULL, thread1, NULL);
    while (!finished0)
    {
        ASSERT_LT(my_lock.guard, 2);
    }
    while (!finished1)
    {
        pthread_kill(pthread1, SIGCONT);
        sched_yield();
    }
    pthread_join(pthread0, NULL);
    pthread_join(pthread1, NULL);

    destroy(&my_lock);
}

