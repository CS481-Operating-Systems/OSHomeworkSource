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
    count = lru(head, &remove_frame);
    ASSERT_EQ(remove_frame->idx, 0);
    head = remove_frame->next;
    delete remove_frame;

    tail = head;
    for (int i = 0; i < 5; i++)
    {
        tail->access(idx++);
        tail = tail->next;
    }
    count = lru(head, &remove_frame);
    ASSERT_EQ(remove_frame->idx, 6);
    tail = head;
    while (tail->next)
    {
        if (tail->next == remove_frame)
        {
            tail->next = remove_frame->next;
            delete remove_frame;
            break;
        }
        tail = tail->next;
    }

    tail = head;
    while (tail->next)
    {
        if (tail->idx != 8)
            tail->access(idx++);
        tail = tail->next;
    }
    count = lru(head, &remove_frame);
    ASSERT_EQ(remove_frame->idx, 8);
}

