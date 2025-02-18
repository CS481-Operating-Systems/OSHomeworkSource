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
    PageTable* table = new PageTable(16);
    TLB* tlb = new TLB(4,2);
    table->add_page(4, 16, 0, 1);
    table->add_page(6, 25, 1, 1);
    table->add_page(8, 0, 1, 0);
    table->add_page(15, 2, 0, 0);

    int addr;
    int page_size = 4;
    int virtual_address;

    tlb->add_entry(2, 1, 20);
    virtual_address = 24;
    addr = virtual_to_physical(virtual_address, page_size, tlb, table);
    ASSERT_EQ(addr, 80);

    virtual_address = 26;
    addr = virtual_to_physical(virtual_address, page_size, tlb, table);
    ASSERT_EQ(addr, 82);



    delete tlb;
    delete table; 
}
