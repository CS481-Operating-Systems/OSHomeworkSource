#ifndef TEST_SRC_HPP
#define TEST_SRC_HPP

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>



/***********************************
 * Page Table
 ***********************************/
class PTE
{
    public:
        PTE()
        {
            PFN = 0;
            protect_bit = 0;
            valid_bit = 1;
            present_bit = 0;
            can_access = not protect_bit;
        }

        ~PTE()
        {

        }

        void update_entry(int _PFN, int _protect_bit = 0, int _valid_bit = 1)
        {
            PFN = _PFN;
            protect_bit = _protect_bit;
            valid_bit = _valid_bit;
            present_bit = 1;
            can_access = not protect_bit;
        }

        int PFN;
        int protect_bit;
        int valid_bit;
        int present_bit;
        bool can_access;
};


class PageTable
{
    public:
        PageTable(int _num_pages)
        {
            num_pages = _num_pages;
            entries = new PTE*[num_pages];
            for (int i = 0; i < num_pages; i++)
                entries[i] = new PTE();
        }

        ~PageTable()
        {
            for (int i = 0; i < num_pages; i++)
                delete entries[i];
            delete[] entries;
        }

        void add_page(int VPN, int PFN, int protect_bit = 0, int valid_bit = 1)
        {
            entries[VPN]->update_entry(PFN, protect_bit, valid_bit);
        }

        void lookup(int VPN, PTE** entry)
        {
            *entry = entries[VPN];
        }


        PTE** entries;
        int num_pages;
};


/***********************************
 * TLB 
 ***********************************/
class TLB_entry
{
    public:
        TLB_entry()
        {
            tag = 0;
            PFN = 0;
            protect_bit = 0;
            valid_bit = 0;
            idx = 0;
            can_access = not protect_bit;
        }

        ~TLB_entry()
        {

        }

        void update_entry(int _tag, int _PFN, int _protect_bit = 0, int _idx = 0)
        {
            tag = _tag;
            PFN = _PFN;
            protect_bit = _protect_bit;
            idx = _idx;
            valid_bit = 1;
            can_access = not protect_bit;
        }

        int tag;
        int PFN;
        int protect_bit;
        int valid_bit;
        bool can_access;
        int idx;
};

class TLB_set
{
    public:
        TLB_set()
        {
            entries = NULL;
            set_size = 0;
            counter = 0;
        }

        ~TLB_set()
        {
            for (int i = 0; i < set_size; i++)
                delete entries[i];
            delete[] entries;
        }

        void create_set(int _set_size)
        {
            set_size = _set_size;
            entries = new TLB_entry*[set_size];
            for (int i = 0; i < set_size; i++)
                entries[i] = new TLB_entry();
        }

        void add_entry(int tag, int PFN, int protect_bit = 0)
        {
            // If available spot in set, add TLB entry
            for (int i = 0; i < set_size; i++)
            {
                if (entries[i]->valid_bit == 0)
                {
                    entries[i]->update_entry(tag, PFN, protect_bit, counter++);
                    return;
                }
            }

            // If no available spots in set, 
            //    1. remove entry with lowest idx
            //    2. add TLB entry to this position
            int min_counter = counter;
            int min_idx = -1;
            for (int i = 0; i < set_size; i++)
            {
                if (entries[i]->idx < min_counter)
                {
                    min_idx = i;
                    min_counter = entries[i]->idx;
                }
            }
            entries[min_idx]->update_entry(tag, PFN, protect_bit, counter++);
        }

        bool lookup(int tag, TLB_entry** entry)
        {
            for (int i = 0; i < set_size; i++)
            {
                if (entries[i]->tag == tag && entries[i]->valid_bit==1)
                {
                    *entry = entries[i];
                    return true;
                }
            }
            return false;
        }

        TLB_entry** entries;
        int set_size;
        int counter;
};

class TLB
{
    public:
        TLB(int _k, int set_size)
        {
            k = _k;
            sets = new TLB_set[k];
            for (int i = 0; i < k; i++)
                sets[i].create_set(set_size);
        }

        ~TLB()
        {
            delete[] sets;

        }

        void add_entry(int idx, int tag, int PFN, int protect_bit = 0)
        {
            sets[idx].add_entry(tag, PFN, protect_bit);
        }
        
        bool lookup(int idx, int tag, TLB_entry** entry)
        {
            return sets[idx].lookup(tag, entry); 
        }

        TLB_set* sets;
        int k;
};


/***********************************
 * Frame List : 
 *    for replacment algorithm
 **********************************/
class FrameList
{
    public:
        FrameList(int _idx)
        {
            next = NULL;
            clock_bit = 1;
            idx = _idx;
        }

        ~FrameList()
        {

        }


        void access(int _idx)
        {
            clock_bit = 1;
            idx = _idx;
        }

        FrameList* next;
        int idx;
        int clock_bit;
};

/***********************************
 * To be implemented by you
 **********************************/
// translation.cpp
void split_virtual_address(int virtual_address, int page_size, int* VPN, int* offset);
void split_VPN(int VPN, int k, int* index, int* tag);
int TLB_lookup(TLB* tlb, int VPN);
int table_lookup(PageTable* table, TLB* tlb, int VPN);
int get_physical_address(int PFN, int offset, int page_size);
int virtual_to_physical(int virtual_address, int page_size, TLB* tlb, PageTable* table);

// replacement.cpp
int fifo(FrameList* active_frames, FrameList** frame_to_remove_ptr);
int lru(FrameList* active_frames, FrameList** frame_to_remove_ptr);
int clock_lru(FrameList* active_frames, FrameList** frame_to_remove_ptr);


/***********************************
 * Implemented in src.cpp 
 ***********************************/
void protection_fault();
void segmentation_fault();
void page_fault();
void tlb_miss();




#endif
