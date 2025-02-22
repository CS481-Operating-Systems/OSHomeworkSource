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

TEST(PageTableTest, TestsIntests)
{
    bool exception;
    PageTable* table = new PageTable(16);
    TLB* tlb = new TLB(4,2);
    table->add_page(4, 16, 0, 1);
    table->add_page(6, 25, 1, 1);
    table->add_page(8, 0, 1, 0);
    table->add_page(15, 2, 0, 0);

    int addr;
    int page_size = 8;
    int virtual_address = 112;

    try
    {
        exception = false;
        addr = virtual_to_physical(virtual_address, page_size, tlb, table);
    }
    catch (const char* msg)
    {
        ASSERT_STREQ(msg, PAGE_FAULT);
        exception = true;
    }
    ASSERT_EQ(exception, true);

    table->add_page(14, 13, 0, 1);
    addr = virtual_to_physical(virtual_address, page_size, tlb, table);
    ASSERT_EQ(addr, 104);

    virtual_address = 119;
    addr = virtual_to_physical(virtual_address, page_size, tlb, table);
    ASSERT_EQ(addr, 111);


    delete tlb;
    delete table; 
}
