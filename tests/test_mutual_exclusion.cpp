// EXPECT_EQ and ASSERT_EQ are macros
// EXPECT_EQ test execution and continues even if there is a failure
// ASSERT_EQ test execution and aborts if there is a failure
// The ASSERT_* variants abort the program execution if an assertion fails 
// while EXPECT_* variants continue with the run.

#include "gtest/gtest.h"
#include "src.hpp"

lock_t my_lock;
volatile int value = 0;
int n_loops = 10000;
int* finished;

void queue_sig_handler(int signum)
{
}

void* thread(void* arg)
{
    int* id = (int*)arg;

    lock(&my_lock);
    for (int i = 0; i < n_loops; i++) 
        value++;
    unlock(&my_lock);

    finished[*id] = 1;
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

    int n_threads = 10;
    pthread_t* threads = new pthread_t[n_threads];
    int* thread_ids = new int[n_threads];
    finished = new int[n_threads];

    for (int i = 0; i < n_threads; i++)
    {
        finished[i] = 0;
        thread_ids[i] = i;
        pthread_create(&(threads[i]), NULL, thread, &(thread_ids[i]));
    }

    for (int i = 0; i < n_threads; i++)
    {
        while (!finished[i])
        {
            pthread_kill(threads[i], SIGCONT);
            sched_yield();
        }
        pthread_join(threads[i], NULL);
    }

    ASSERT_EQ(value, n_threads*n_loops);

    destroy(&my_lock);
}
