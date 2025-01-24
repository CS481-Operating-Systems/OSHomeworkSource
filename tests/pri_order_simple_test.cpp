// EXPECT_EQ and ASSERT_EQ are macros
// EXPECT_EQ test execution and continues even if there is a failure
// ASSERT_EQ test execution and aborts if there is a failure
// The ASSERT_* variants abort the program execution if an assertion fails 
// while EXPECT_* variants continue with the run.

#include "gtest/gtest.h"
#include "src.hpp"

int counter;
void job0(int time)
{
    for (int t = 0; t < time; t++)
        counter += 3;
}

void job1(int time)
{
    for (int t = 0; t < time; t++)
        counter *= 2;
}

void job2(int time)
{
    for (int t = 0; t < time; t++)
        counter -= 1;
}

void create_jobs(int* n_jobs, Job** jobs)
{
    *n_jobs = 5;
    Job* example_jobs = (Job*)malloc((*n_jobs)*sizeof(Job));

    int priorities[] = {0, 1, 1, 2, 2};
    int indices[] = {1, 0, 2, 3, 4};
    int times[] = {3, 7, 6, 2, 1};
    Operation run_jobs[] = {job2, job1, job0, job0, job1};

    for (int i = 0; i < *n_jobs; i++)
    {
        example_jobs[i].priority = priorities[i];
        example_jobs[i].idx = indices[i];
        example_jobs[i].time = times[i];
        example_jobs[i].run_job = run_jobs[i];
    }

    *jobs = example_jobs;
}

TEST(PriorityTest, TestsIntests)
{
    for (int i = 0; i < 1; i++)
    {
        int n_jobs;
        Job* jobs;

        // Run Test
        create_jobs(&n_jobs, &jobs);
        counter = 0;
        priority(n_jobs, jobs);
        ASSERT_EQ(counter, -720);
        free(jobs);
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    int ierr = 0;
    ierr += RUN_ALL_TESTS();

    return ierr;

}

