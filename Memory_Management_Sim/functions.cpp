/* Author: Jacob Krawitz (jkrawitz@muhlenberg.edu) 
   Date: 4/29/22
   Description: Defines functions used in simulator. *Notably my_alloc and my_free*
*/

#include "functions.h"

using namespace std;


bool my_alloc(vector<Slot>& memory, Process to_alloc)
{
    bool found = false;

    bool go = false;

    int recent = 0;

    LOOP: while(!found)
    {
        for(int i=recent; i<memory.size(); i++)
        {
            if(!memory[i].has_process)
            {
                for(int r=i; r<(recent+to_alloc.memory_req); r++)
                {
                    if(memory[r].has_process)
                    {
                        recent = r;
                        //cout << "RECENT: " << r << endl;
                        goto LOOP;
                    }
                }
                // fits
                for(int j=i; j<(i+to_alloc.memory_req); j++)
                {
                    Slot new_slot;
                    new_slot.current_process_id = to_alloc.id;
                    new_slot.has_process = true;

                    memory[j] = new_slot;
                }   
                return true;
            } 
        }
    }
    return false;
}

bool my_free(vector<Slot>& memory, Process to_dealloc)
{
    for(int i=0; i<memory.size(); i++)
    {
        if(memory[i].current_process_id == to_dealloc.id)
        {
            memory[i].current_process_id = 0;
            memory[i].has_process = 0;
        }
    }
}

// Function that returns if there is space on any of the four processors
bool has_room(vector<Processor> processor_list)
{
    for(int i=0; i<processor_list.size(); i++)
    {
        if(!processor_list[i].has_process)
        {
            return true;
        }
    }
    return false;
}

// Function that returns if there are processors on any of the processors (similar to prev)
bool has_processes(vector<Processor> processor_list)
{
    for(int i=0; i<processor_list.size(); i++)
    {
        if(processor_list[i].has_process)
        {
            return true;
        }
    }
    return false;
}

// Returns which processor has a free spot
int free_processor(vector<Processor> processor_list)
{
    for(int i=0; i<processor_list.size(); i++)
    {
        if(!processor_list[i].has_process)
        {
            return i;
        }
    }
    return -1;
}

void print_processors(vector<Processor> processor_list, int cycles)
{
    cout << "CYCLES: " << cycles << endl;
    for(int i=0; i<processor_list.size();i++)
    {
        cout << "Processor ID: " << i << ", " << processor_list[i].current_process.id << endl;
    }
}

int size_memory(vector<int*> pointers)
{
    int count = 0;

    for(int i=0; i<pointers.size(); i++)
    {
        if(pointers[i] != 0)
        {
            count+=1;
        }
    }
    return count;
}

int size_memory_mine(vector<Slot> memory)
{
    int count = 0;

    for(int i=0; i<memory.size(); i++)
    {
        if(memory[i].current_process_id != 0)
        {
            count += 1;
        }
    }
}