// EXPECT_EQ and ASSERT_EQ are macros
// EXPECT_EQ test execution and continues even if there is a failure
// ASSERT_EQ test execution and aborts if there is a failure
// The ASSERT_* variants abort the program execution if an assertion fails 
// while EXPECT_* variants continue with the run.

#include "gtest/gtest.h"
#include "src.hpp"

FILE* fn;

void grandchild()
{
    fn = fopen("./procs.output", "w");
    fprintf(fn, "Here\n");
    fclose(fn);
}

void child()
{
    fn = fopen("./procs.output", "a");
    fprintf(fn, "Here\n");
    fclose(fn);
}

void parent()
{
    fn = fopen("./procs.output", "a");
    fprintf(fn, "Here\n");
    fclose(fn);
}

TEST(ProcessOrderTest, TestsInTests)
{
    int rc = fork();
    int pid = getpid();

    if (rc == 0)
    {
        run_processes();
        exit(1);
    }
    else
    {
        wait(NULL);

        const char* comparison = "Here";

        fn = fopen("./procs.output", "r");

        char buff[255];
        for (int i = 0; i < 3; i++)
        {
            fscanf(fn, "%s\n", buff);
            ASSERT_STREQ(buff, comparison);
        }

        fclose(fn);
    }
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    int ierr = 0;
    ierr += RUN_ALL_TESTS();

    return ierr;

}



