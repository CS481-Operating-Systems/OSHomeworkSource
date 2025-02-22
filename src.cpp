#include "src.hpp"

#define TLB_MISS "tlb_miss"
#define PROTECT_FAULT "protect_fault"
#define SEG_FAULT "seg_fault"
#define PAGE_FAULT "page_fault"


void protection_fault()
{
    throw PROTECT_FAULT;
}

void segmentation_fault()
{
    throw SEG_FAULT;
}

void page_fault()
{
    throw PAGE_FAULT;
}

void tlb_miss()
{
    throw TLB_MISS;
}


