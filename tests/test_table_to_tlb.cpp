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
    int PFN;
    PageTable* table = new PageTable(16);
    TLB* tlb = new TLB(4,2);
    table->add_page(4, 16, 0, 1);
    table->add_page(6, 25, 0, 1);
    table->add_page(8, 0, 0, 1);
    table->add_page(15, 2, 0, 1);

    PFN = table_lookup(table, tlb, 4);
    PFN = TLB_lookup(tlb, 4);
    ASSERT_EQ(PFN, 16);

    PFN = table_lookup(table, tlb, 6);
    PFN = TLB_lookup(tlb, 6);    
    ASSERT_EQ(PFN, 25);

    PFN = table_lookup(table, tlb, 8);
    PFN = TLB_lookup(tlb, 8);    
    ASSERT_EQ(PFN, 0);

    PFN = table_lookup(table, tlb, 15);
    PFN = TLB_lookup(tlb, 15);    
    ASSERT_EQ(PFN, 2);


    delete tlb;
    delete table; 
}
