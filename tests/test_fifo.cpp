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
    FrameList* remove_frame;
    int count;
    int idx = 0;
    FrameList* head = new FrameList(idx++);
    FrameList* tail = head;
    for (int i = 0; i < 10; i++)
    {
        FrameList* next = new FrameList(idx++);
        tail->next = next;
        tail = next;
    }

    count = fifo(head, &remove_frame);
    ASSERT_EQ(remove_frame->idx, 0);
    tail = remove_frame->next;
    delete remove_frame;
    head = tail;

    count = fifo(head, &remove_frame);
    ASSERT_EQ(remove_frame->idx, 1);
    tail = remove_frame->next;
    delete remove_frame;
    head = tail;

    count = fifo(head, &remove_frame);
    ASSERT_EQ(remove_frame->idx, 2);
    tail = remove_frame->next;
    delete remove_frame;
    head = tail;

    for (int i = 3; i < 10; i++)
    {
        FrameList* next = new FrameList(idx++);
        tail->next = next;
        tail = next;
    }
    count = fifo(head, &remove_frame);
    ASSERT_EQ(remove_frame->idx, 3);


}

