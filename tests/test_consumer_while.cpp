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

    init(buf, 1);

    pthread_t producer, consumer;
    data_t data;

    pthread_create(&consumer, NULL, consumer_thread, buf);

    usleep(100000);

    pthread_mutex_lock(&(buf->mutex));
    pthread_cond_signal(&(buf->full));
    pthread_cond_signal(&(buf->empty));
    pthread_mutex_unlock(&(buf->mutex));

    usleep(100000);

    data.buf = buf;
    data.val = 1;
    pthread_create(&producer, NULL, producer_thread, &data);

    pthread_join(producer, NULL);

    int* return_val;
    pthread_join(consumer, (void**)&return_val);
    ASSERT_EQ(*return_val, data.val);

    destroy(buf);
    free(buf);
}
