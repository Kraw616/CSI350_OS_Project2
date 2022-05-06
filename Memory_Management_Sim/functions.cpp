/* Author: Jacob Krawitz (jkrawitz@muhlenberg.edu) 
   Date: 4/29/22
   Description: Defines functions used in simulator. *Notably my_alloc and my_free*
*/

#include "functions.h"

using namespace std;

int size_hole(vector<Slot> memory, int start)
{
    for(int i=start; i<memory.size();i++)
    {
        if(memory[i].has_process)
        {
            return i-start;
        }
    }
    return -1;
}

bool my_alloc_FF(vector<Slot>& memory, Process to_alloc)
{
    bool found = false;

    bool go = false;

    int recent = 0;

    while(!found)
    {
        for(int i=recent; i<memory.size(); i++)
        {
            if(!memory[i].has_process)
            {
                bool fits = true;
                
                for(int r=i; r<(i+to_alloc.memory_req); r++)
                {
                    if(memory[r].has_process)
                    {
                        fits = false;
                    }
                }
                // fits
                if(fits)
                {
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
}

bool my_alloc_BF(vector<Slot>& memory, Process to_alloc)
{
    bool found = false;

    int recent = 0;

    int min_hole = memory.size()+1;
    int min_hole_index = -1;

    for(int i=recent; i<memory.size(); i++)
    {
        if(!memory[i].has_process)
        {
            bool fits = true;

            for(int r=i; r<(i+to_alloc.memory_req); r++)
            {
                if(memory[r].has_process)
                {
                    fits = false;
                }
            }
            // fits
            if(fits)
            {
                int hole = size_hole(memory, i);
                if(hole < min_hole)
                {
                    min_hole = hole;
                    min_hole_index = i;
                }
            }  
        } 
    }
    if(min_hole_index > -1)
    {
        for(int j=min_hole_index; j<(min_hole_index+to_alloc.memory_req); j++)
        {
            Slot new_slot;
            new_slot.current_process_id = to_alloc.id;
            new_slot.has_process = true;
            memory[j] = new_slot;
        }   
        return true;
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
    return count;
}

vector<Process> create_copy_vector(vector<Process> process_queue)
{
    vector<Process> new_vector(process_queue.size());

    copy(process_queue.begin(), process_queue.end(), new_vector.begin());

    return new_vector;
}
