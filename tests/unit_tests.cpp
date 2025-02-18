// EXPECT_EQ and ASSERT_EQ are macros
// EXPECT_EQ test execution and continues even if there is a failure
// ASSERT_EQ test execution and aborts if there is a failure
// The ASSERT_* variants abort the program execution if an assertion fails 
// while EXPECT_* variants continue with the run.

#include "gtest/gtest.h"
#include "src.hpp"

TEST(PageTableTest, TestsIntests)
{
    PageTable* table = new PageTable(16);
    TLB* tlb = new TLB(4,2);
    table->add_page(4, 16, 0, 1);
    table->add_page(6, 25, 1, 1);
    table->add_page(8, 0, 1, 0);
    table->add_page(15, 2, 0, 0);

    int addr;
    int page_size = 4;
    int virtual_address = 16;
    addr = virtual_to_physical(virtual_address, page_size, tlb, table);
    ASSERT_EQ(addr, 64);

    virtual_address = 19;
    addr = virtual_to_physical(virtual_address, page_size, tlb, table);
    ASSERT_EQ(addr, 67);

    delete tlb;
    delete table; 
}


TEST(FIFOTest, TestsIntests)
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

TEST(LRUTest, TestsIntests)
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


TEST(ClockLRUTest, TestsIntests)
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



int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}



