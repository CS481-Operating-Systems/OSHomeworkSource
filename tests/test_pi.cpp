// EXPECT_EQ and ASSERT_EQ are macros
// EXPECT_EQ test execution and continues even if there is a failure
// ASSERT_EQ test execution and aborts if there is a failure
// The ASSERT_* variants abort the program execution if an assertion fails 
// while EXPECT_* variants continue with the run.

#include "gtest/gtest.h"
#include "src.hpp"
#include <math.h>

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(TLBTest, TestsIntests)
{
    double global_sum, serial_global_sum;
    
    int global_n = 1000;
    int n_threads;
    for (int iter = 0; iter < 3; iter++)
    {
        serial_global_sum = serial_compute_pi(global_n, 0);
        for (int i = 0; i < 4; i++)
        {
            n_threads = pow(2, i);
            global_sum = pthread_compute_pi(n_threads, global_n);
            ASSERT_NEAR(serial_global_sum, global_sum, 0.2);
        }
        
        global_n *= 10;
    }
}
