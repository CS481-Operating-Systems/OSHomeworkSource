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
    int pid = getpid();
    fprintf(fn, "Grandchild %d\n", pid);
    fflush(fn);
    fclose(fn);
}

void child()
{
    fn = fopen("./procs.output", "a");
    int pid = getpid();
    fprintf(fn, "Child %d\n", pid);
    fflush(fn);
    fclose(fn);
}

void parent()
{
    fn = fopen("./procs.output", "a");
    int pid = getpid();
    fprintf(fn, "Parent %d\n", pid);
    fflush(fn);
    fclose(fn);
}

TEST(ProcessOrderTest, TestsInTests)
{
    int pid = getpid();
    run_processes();

    if (getpid() != pid)
        exit(0);

    fn = fopen("./procs.output", "r");

    char buff[255];
    int pid_g, pid_c, pid_p;
    fscanf(fn, "%s\n", buff);
    ASSERT_STREQ(buff, "Grandchild");
    fscanf(fn, "%d\n", &pid_g);
    fscanf(fn, "%s\n", buff);
    ASSERT_STREQ(buff, "Child");
    fscanf(fn, "%d\n", &pid_c);
    fscanf(fn, "%s\n", buff);
    ASSERT_STREQ(buff, "Parent");
    fscanf(fn, "%d\n", &pid_p);

    fclose(fn);

    ASSERT_EQ(pid, pid_p);
    ASSERT_NE(pid_p, pid_c);
    ASSERT_NE(pid_p, pid_g);
    ASSERT_NE(pid_c, pid_g);
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    int ierr = 0;
    ierr += RUN_ALL_TESTS();

    return ierr;

}



