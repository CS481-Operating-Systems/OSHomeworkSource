#include "src.hpp"

#define TLB_MISS "TLB Miss!"
#define PROTECT_FAULT "Protection Fault!"
#define SEG_FAULT "Segmentation Fault!"
#define PAGE_FAULT "Page Fault!"


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


