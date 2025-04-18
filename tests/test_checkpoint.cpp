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
    char journal_name[] = "journal.txt";
    char data_name[] = "data.txt";

    remove(journal_name);

    char txb[] = "txe12";
    char ib[] = "ib";
    char bb[] = "bb";
    char str[] = "hello world";
    char txe[] = "txe21";
    write_to_journal(sizeof(txb)-1, txb, sizeof(ib)-1, ib, sizeof(bb)-1, bb, sizeof(str)-1, str, sizeof(txe), txe);

    sleep(1);

    int err = checkpoint(sizeof(txe), txe);
    ASSERT_EQ(err, 0);

    sleep(1);

    char sol[] = "txe12ibbbhello worldtxe21";

    int fd = open(journal_name, O_RDONLY);
    int fd2 = open(data_name, O_RDONLY);

    struct stat st;
    stat(journal_name, &st);
    int size = st.st_size + 1;
    ASSERT_GT(size, 0);

    char* journal_bytes = (char*)malloc(size);
    char* data_bytes = (char*)malloc(size);
    read(fd, journal_bytes, size);
    read(fd2, data_bytes, size);
    journal_bytes[size-1] = '\0';
    data_bytes[size-1] = '\0';
    ASSERT_STREQ(data_bytes, journal_bytes);
    ASSERT_STREQ(sol, data_bytes);

    free(journal_bytes);
    free(data_bytes);
    close(fd);
    close(fd2);
}

