/* Author: Jacob Krawitz (jkrawitz@muhlenberg.edu) 
   Date: 4/29/22
   Description: Defines function to setup simulation.
*/

#include "functions.h"

using namespace std;

vector<Process> seed_and_create_processes(int seed)
{
    // Available memory to allocate
    int to_allocate = 9950;

    // Vector of processes to hold processes that we will return
    vector<Process> process_queue;

    // Create and seed generator object
    default_random_engine gen;
    gen.seed(seed);

    // Normal distribution of mean 200 and standard deviation 75
    normal_distribution<float> distribution(200, 75);

    // Generate 50 processes with random service time between 200 and 2000, appropriate ids, and put those onto the process queue
    for(int i=0; i<50; i++)
    {
        Process current_process;
        current_process.id = i;
        current_process.service_time = 200 + (rand() % 2000);
        current_process.cycles_worked = current_process.service_time;
        process_queue.push_back(current_process);
    }

    // Iterate through process queue and if subtracting the random requirement would lead to
    // 0, allocate that process all that's left to allocate (the rest has 1)
    for(int i=0; i<process_queue.size(); i++)
    {
        int random_req = int(distribution(gen));

        if(i==49)
        {
            process_queue[i].memory_req += to_allocate;
            break;          
        }
        else if(to_allocate - random_req >= 0)
        {
            process_queue[i].memory_req += random_req;  // Give 50 whatever is left (regardless of how much it is)
            to_allocate -= random_req;
        }
    }

    // Check memory req total
    int total = 0;
    for(int i=0; i<process_queue.size(); i++)
    {
        total += process_queue[i].memory_req;
    }
    return process_queue;   // Return vector of processes
}

vector<Processor> create_processors()
{
    Processor P1;
    Processor P2;
    Processor P3;
    Processor P4;
    vector<Processor> processor_list;

    P1.speed = 150; // GHz (3 billion clocks per second)
    P1.id = 1;

    P2.speed = 150; // GHz (3 billion clocks per second)
    P2.id = 2;

    P3.speed = 150; // Hz
    P3.id = 3;

    P4.speed = 150; // GHz (3 billion clocks per second, 1,000,000,000)
    P4.id = 4;

    processor_list.push_back(P1);   // Push onto vector of processors
    processor_list.push_back(P2);
    processor_list.push_back(P3);
    processor_list.push_back(P4);

    return processor_list;
    
}

vector<Slot> create_memory_12()
{  
    vector<Slot> memory(10000);

    for(int i=0; i<memory.size(); i++)
    {
        memory[i].has_process = false;
    }
    return memory;
}

vector<Slot> create_memory_3()
{  
    vector<Slot> memory(5000);

    for(int i=0; i<memory.size(); i++)
    {
        memory[i].has_process = false;
    }
    return memory;
}

vector<Slot> create_memory_4()
{  
    vector<Slot> memory(1000);

    for(int i=0; i<memory.size(); i++)
    {
        memory[i].has_process = false;
    }
    return memory;
}

void test(vector<Slot> memory)
{
    Process test_process;
    test_process.memory_req = 10;
    test_process.id = 1;

    my_alloc_BF(memory, test_process);

    for(int i=0; i<memory.size(); i++)
    {        
        cout << memory[i].current_process_id << endl;
    }

    cout << endl;
}