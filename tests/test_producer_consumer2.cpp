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
    buffer_t* buf = (buffer_t*)malloc(sizeof(buffer_t));

    init(buf, 5);

    int n_p = 10;
    int n_c = 10;
    int n = n_p + n_c;
    pthread_t* threads = (pthread_t*)malloc(n*sizeof(pthread_t));
    data_t* data = (data_t*)malloc(n_p*sizeof(data_t));
    for (int i = 0; i < n_p; i++)
    {
        data[i].buf = buf;
        data[i].val = i;
        pthread_create(&(threads[i]), NULL, producer_thread, &(data[i]));
    }
    for (int i = 0; i < n_c; i++)
    {
        pthread_create(&(threads[n_p+i]), NULL, consumer_thread, buf);
    }

    for (int i = 0; i < n_p; i++)
        pthread_join(threads[i], NULL);

    int* return_val;
    int ctr = 0;
    int val_ctr = 0;
    for (int i = 0; i < n_c; i++)
    {
        pthread_join(threads[n_p+i], (void**)&return_val);
        ctr += i;
        val_ctr += *return_val;
    }
    ASSERT_EQ(ctr, val_ctr);

    destroy(buf);

    free(threads);
    free(data);
    free(buf);
}
