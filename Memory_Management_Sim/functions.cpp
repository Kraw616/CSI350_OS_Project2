/* Author: Jacob Krawitz (jkrawitz@muhlenberg.edu) 
   Date: 5/06/22
   Description: Defines functions used in simulator, notably my_alloc and my_free.

   * NOTE * See functions.h for header comments.
*/

// INCLUDE STATEMENT
#include "functions.h"

using namespace std;

int size_hole(vector<Slot> memory, int start)
{
    for(int i=start; i<memory.size();i++)
    {
        if(memory[i].has_process)   // From a starting point, see how long it takes until you reach an occupied slot (size of hole)
        {
            return i-start;
        }
    }
    return -1;
}

bool my_alloc_FF(vector<Slot>& memory, Process to_alloc)
{
    int recent = 0;

    // For each slot in memory...
    for(int i=recent; i<memory.size(); i++)
    {
        if(!memory[i].has_process)  // If you reach a slot with a process...
        {
            bool fits = true;   // Set bool to true
            
            for(int r=i; r<(i+to_alloc.memory_req); r++)
            {
                if(memory[r].has_process)   // If at any slot between the free slot + the memory requirement has a process, does not fit
                {
                    fits = false;
                }
            }
            if(fits)    // If this hole can accomodate the process...
            {
                for(int j=i; j<(i+to_alloc.memory_req); j++)    // Set all slots in range of the requirement to the process's id
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

bool my_alloc_BF(vector<Slot>& memory, Process to_alloc)
{
    int recent = 0;

    int min_hole = memory.size()+1; // Set variables to hold minimum and maximum hole sizes
    int min_hole_index = -1;

    for(int i=recent; i<memory.size(); i++) // For each slot in memory...
    {
        if(!memory[i].has_process)  // If that slot doe not have a processs...
        {
            bool fits = true;  

            for(int r=i; r<(i+to_alloc.memory_req); r++)
            {
                if(memory[r].has_process)
                {
                    fits = false;
                }
            }
            if(fits)
            {
                int hole = size_hole(memory, i);    // If our process fits in the hole, see if the size of the hold is less than minimum
                if(hole < min_hole)
                {
                    min_hole = hole;
                    min_hole_index = i;
                }
            }  
        } 
    }
    if(min_hole_index > -1) // If an index was found...
    {
        for(int j=min_hole_index; j<(min_hole_index+to_alloc.memory_req); j++)
        {
            Slot new_slot;  // Fill up that minimum sized hold with the process
            new_slot.current_process_id = to_alloc.id;
            new_slot.has_process = true;
            memory[j] = new_slot;
        }   
        return true;
    }
    return false;   // If not, return false
}

void my_free(vector<Slot>& memory, Process to_dealloc)
{
    for(int i=0; i<memory.size(); i++)
    {
        if(memory[i].current_process_id == to_dealloc.id)   // Free up any slots that have the id of the process we want to deallocate
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
        if(!processor_list[i].has_process)  // If there is space on any of the four processes, return true
        {
            return true;
        }
    }
    return false;
}

// Function that returns if there are processes on any of the processors (similar to prev)
bool has_processes(vector<Processor> processor_list)
{
    for(int i=0; i<processor_list.size(); i++)
    {
        if(processor_list[i].has_process)
        {
            return true;    // If there are processes on any of the processors, return true
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
            return i;   // If a processor does not have a process, return which one
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
            count+=1;   // How many slots of memory are filled? With scenario 1
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
            count += 1; // How many slots of memory are filled? With scenario 2-4
        }
    }
    return count;
}
