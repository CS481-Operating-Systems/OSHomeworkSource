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

TEST(VPNTest, TestsIntests)
{
    int count;
    int idx = 0;
    FrameList* head = new FrameList(idx++);
    FrameList* tail = head;
    FrameList* remove_frame;
    for (int i = 0; i < 10; i++)
    {
        FrameList* next = new FrameList(idx++);
        tail->next = next;
        tail = next;
    }


    count = clock_lru(head, &remove_frame);
    ASSERT_EQ(count, 12);
    ASSERT_EQ(remove_frame->idx, 0);

    count = clock_lru(head, &remove_frame);
    ASSERT_EQ(count, 1);
    ASSERT_EQ(remove_frame->idx, 0);


    tail = head;
    for (int i = 0; i < 5; i++)
    {
        tail->access(idx++);
        tail = tail->next;
    }
    count = clock_lru(head, &remove_frame);
    ASSERT_EQ(count, 6);
    ASSERT_EQ(remove_frame->idx, 5);

}

