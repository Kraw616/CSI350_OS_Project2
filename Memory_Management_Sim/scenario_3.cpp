/* Author: Jacob Krawitz (jkrawitz@muhlenberg.edu) 
   Date: 5/06/22
   Description: Defines function for scenario 3 (I handle allocation).

   ** NOTE **
   Outputs are possible to see, but are commented out.
*/

// INCLUDE STATEMENT
#include "functions.h"

// Scenario 3, FF
void scenario_3_FF(vector<Process> process_queue, vector<Processor> processor_list, vector<Slot> memory)
{
    // Keep track of cycles taken in the system
    int cycle = 0;

    int fails = 0;

    // Holder process for once all processes except ones on processors done
    Process holder_process;
    holder_process.id = -1;

    // Vectors to hold finished processes, processes that are waiting for processors to free up,
    // and a processor to hold processes waiting due to no memory availability
    vector<Process> finished;
    vector<Process> wait_queue;
    vector<Process> mem_wait_queue;

    bool loaded;

    // Preload processes
    for(int i=0; i<processor_list.size();i++)
    {
        loaded = false;

        Process to_load = process_queue[i];
        while(!loaded)
        {
            if(process_queue[i].memory_req > memory.size())
            {
                fails += 1;
                to_load = process_queue[i+1];
                process_queue.erase(process_queue.begin() + i);
                continue;
            }
            // Load into memory
            my_alloc_FF(memory, process_queue[i]);

            // Load onto processor
            processor_list[i].current_process = process_queue[i];
            processor_list[i].has_process = true;
            process_queue.erase(process_queue.begin() + i);

            loaded = true;
        }
    }

    // Loop while process queue is not empty (adding to wait queue)
    while(!process_queue.empty())
    {
        cycle += 50; // Cycles go by 50 cycles, at 100 cycles a new process comes in and at 150 is the speed
                    // cycle_num % 100 = 0 then we are at a new 100th cycle, new process comes in
                    // cycle_num % 150 = 0 then it is 1 second for the processor

        // Increment processes on processors
        for(int i=0; i<processor_list.size();i++)
        {
            if(processor_list[i].has_process)
            {
                processor_list[i].current_process.cycles_worked -= 50;
            }
        }

        // Check if any process is done
        for(int i=0; i<processor_list.size();i++)
        {
            if(processor_list[i].has_process)
            {
                // If a process on a processor's cycles worked is 0 or less...
                if(processor_list[i].current_process.cycles_worked <= 0)
                {  
                    // Add it to the finished queue 
                    finished.push_back(processor_list[i].current_process);
                                
                    // Deallocate the memory 
                    my_free(memory, processor_list[i].current_process);
                
                    // Replace process with waiting process if there, or new one from process
                    if(!wait_queue.empty())
                    {
                        processor_list[i].current_process = wait_queue.front();
                        processor_list[i].has_process = true;
                        wait_queue.erase(wait_queue.begin());
                    }
                    else
                    {  
                        // If processes in memory wait queue...
                        if(!mem_wait_queue.empty())
                        {
                            Process next_process = mem_wait_queue.front();

                            // If they fit, load those
                            if(my_alloc_FF(memory, next_process))
                            {
                                processor_list[i].current_process = next_process;
                                processor_list[i].has_process = true;

                                mem_wait_queue.erase(mem_wait_queue.begin());
                            }
                        }
                        // Otherwise, load another process
                        else
                        {
                            Process next_process;
                            next_process = process_queue.front();

                            if((my_alloc_FF(memory, next_process)))
                            {                            
                                processor_list[i].current_process = next_process;
                                processor_list[i].has_process = true;

                                process_queue.erase(process_queue.begin());
                            }
                            else
                            {
                                mem_wait_queue.push_back(next_process);
                            }
                        }  
                    }
                }
            }
        }

        // Every 100 cycles...
        if(cycle % 100 == 0)
        {
            if(!process_queue.empty())
            {
                // Next process from process queue gets loaded into memory
                Process next_process = process_queue.front();

                // If it has a too high memory requirement, increment fails and erase it from queue
                if(next_process.memory_req > memory.size())
                {
                    fails += 1;
                    process_queue.erase(process_queue.begin() + next_process.id);
                    break;
                }
                // Otherwise, see if we can allocate it
                else if(my_alloc_FF(memory, next_process))
                {
                    ;
                }
                // If not, add to wait queue for mem 
                else
                {
                    mem_wait_queue.push_back(next_process);
                }
            }
            
            int free_processor_id;

            Process next_process = process_queue.front();

            // If there is room on the processor...
            if(has_room(processor_list))
            {
                // If no processes are waiting...
                if(wait_queue.empty() && !process_queue.empty())
                {
                    // Get the ID of a free processor, and load random process onto it
                    free_processor_id = free_processor(processor_list);
                    processor_list[free_processor_id].current_process = next_process;
                    processor_list[free_processor_id].has_process = true;

                    //cout << processor_list[free_processor_id].id << endl;
                    process_queue.erase(process_queue.begin());  
                }
                // If processes are in wait queue, load those
                else if(!wait_queue.empty())
                {
                    free_processor_id = free_processor(processor_list);
                    processor_list[free_processor_id].current_process = wait_queue.front();
                    processor_list[free_processor_id].has_process = true;
                    wait_queue.erase(wait_queue.begin());
                }
            }
            // Otherwise, push the new process into the wait cue
            else
            {
                wait_queue.push_back(next_process);

                process_queue.erase(process_queue.begin());
            }

            /*//Output
            print_processors(processor_list, cycle);

            int count = size_memory_mine(memory);
            cout << "MEM: " << count << endl;

            cout << "SIZE OF P QUEUE: " << process_queue.size() << endl;
            cout << "SIZE OF W QUEUE: " << wait_queue.size() << endl;
            cout << "SIZE OF MEM W QUEUE:" << mem_wait_queue.size() << endl;
            */
            
        } 
    }

    // While te wait queue is not empty (after process queue is empty)
    while(!wait_queue.empty())
    {
        cycle += 50; // Cycles go by 50 cycles, at 100 cycles a new process comes in and at 150 is the speed
                    // cycle_num % 100 = 0 then we are at a new 100th cycle, new process comes in
                    // cycle_num % 150 = 0 then it is 1 second for the processor

        // Increment processes on processors
        for(int i=0; i<processor_list.size();i++)
        {
            if(processor_list[i].has_process)
            {
                processor_list[i].current_process.cycles_worked -= 50;
            }
        }

        // Check if any process is done
        for(int i=0; i<processor_list.size();i++)
        {
            if(processor_list[i].has_process)
            {
                // If a process on a processor is done, push it to finished and load waiting process
                if(processor_list[i].current_process.cycles_worked <= 0)
                {
                    finished.push_back(processor_list[i].current_process);
                    
                    // Deallocate the memory 
                    my_free(memory, processor_list[i].current_process);
                
                    // Replace process with a waiting process 
                    processor_list[i].current_process = wait_queue.front();
                    processor_list[i].has_process = true;

                    wait_queue.erase(wait_queue.begin());

                    // If there are processes waiting due to memory...
                    if(!mem_wait_queue.empty())
                    {
                        Process next_process = mem_wait_queue.front();

                        // If they fit, add them to the wait queue
                        if(my_alloc_FF(memory, next_process))
                        {
                            wait_queue.push_back(next_process);

                            mem_wait_queue.erase(mem_wait_queue.begin());
                        }
                    }
                }
            }
        }

        /*//Output
        print_processors(processor_list, cycle);

        int count = size_memory_mine(memory);
        cout << "MEM: " << count << endl;

        cout << "SIZE OF P QUEUE: " << process_queue.size() << endl;
        cout << "SIZE OF W QUEUE: " << wait_queue.size() << endl;
        cout << "SIZE OF MEM W QUEUE:" << mem_wait_queue.size() << endl;
        */
    }

    // While there are still processes on processors (after wait queue empty)
    while(has_processes(processor_list))
    {
        cycle += 50; // Cycles go by 50 cycles, at 100 cycles a new process comes in and at 150 is the speed
                    // cycle_num % 100 = 0 then we are at a new 100th cycle, new process comes in
                    // cycle_num % 150 = 0 then it is 1 second for the processor

        // Increment processes on processors
        for(int i=0; i<processor_list.size();i++)
        {
            if(processor_list[i].has_process)
            {
                processor_list[i].current_process.cycles_worked -= 50;
            }
        }

        // Check if any process is done
        for(int i=0; i<processor_list.size();i++)
        {
            if(processor_list[i].has_process)
            {
                // If a process is done, replace it with a holder process
                if(processor_list[i].current_process.cycles_worked <= 0)
                {
                    finished.push_back(processor_list[i].current_process);

                
                    // Deallocate the memory
                    my_free(memory, processor_list[i].current_process); 
                
                    // Holder process 
                    processor_list[i].current_process = holder_process;
                    processor_list[i].has_process = false;
                }
            }
        }

        /*//Output
        print_processors(processor_list, cycle);

        int count = size_memory_mine(memory);
        cout << "MEM: " << count << endl;

        cout << "SIZE OF P QUEUE: " << process_queue.size() << endl;
        cout << "SIZE OF W QUEUE: " << wait_queue.size() << endl;
        cout << "SIZE OF MEM W QUEUE:" << mem_wait_queue.size() << endl;
        */
        
    }

    // Output process info
    cout << "SCENARIO 3 FF: " << endl;
    cout << "--------------------" << endl;
    cout << endl;

    for(int i=0; i<finished.size(); i++)
    {
        cout << "PROCESS ID: " << finished[i].id << endl; 
        cout << "PROCESS ST: " << finished[i].service_time << endl; 
        cout << "PROCESS MR: " << finished[i].memory_req << endl; 
        
        cout << endl;
    }
    cout << "FAILED TO ALLOCATE: " << fails << endl;
    cout << "TOTAL CYCLES: " << cycle << endl;
}

// Scenario 3, BF
void scenario_3_BF(vector<Process> process_queue, vector<Processor> processor_list, vector<Slot> memory)
{
    // Keep track of cycles taken in the system
    int cycle = 0;

    int fails = 0;

    // Holder process for once all processes except ones on processors done
    Process holder_process;
    holder_process.id = -1;

    // Vectors to hold finished processes, processes that are waiting for processors to free up,
    // and a processor to hold processes waiting due to no memory availability
    vector<Process> finished;
    vector<Process> wait_queue;
    vector<Process> mem_wait_queue;

    // Create array to hold pointers to processes 
    //vector<int*> pointers(50);
    //int* pointers = new int[50];

    //int *ptr;

    bool loaded;

    // Preload processes
    for(int i=0; i<processor_list.size();i++)
    {
        loaded = false;

        Process to_load = process_queue[i];
        while(!loaded)
        {
            if(process_queue[i].memory_req > memory.size())
            {
                fails += 1;
                to_load = process_queue[i+1];
                process_queue.erase(process_queue.begin() + i);
                continue;
            }
            // Load into memory
            my_alloc_BF(memory, process_queue[i]);

            // Load onto processor
            processor_list[i].current_process = process_queue[i];
            processor_list[i].has_process = true;
            process_queue.erase(process_queue.begin() + i);

            loaded = true;
        }
    }

    // Loop while process queue is not empty (adding to wait queue)
    while(!process_queue.empty())
    {
        cycle += 50; // Cycles go by 50 cycles, at 100 cycles a new process comes in and at 150 is the speed
                    // cycle_num % 100 = 0 then we are at a new 100th cycle, new process comes in
                    // cycle_num % 150 = 0 then it is 1 second for the processor

        // Increment processes on processors
        for(int i=0; i<processor_list.size();i++)
        {
            if(processor_list[i].has_process)
            {
                processor_list[i].current_process.cycles_worked -= 50;
            }
        }

        // Check if any process is done
        for(int i=0; i<processor_list.size();i++)
        {
            if(processor_list[i].has_process)
            {
                // If a process on a processor's cycles worked is 0 or less...
                if(processor_list[i].current_process.cycles_worked <= 0)
                {  
                    // Add it to the finished queue 
                    finished.push_back(processor_list[i].current_process);
                                
                    // Deallocate the memory 
                    my_free(memory, processor_list[i].current_process);
                
                    // Replace process with waiting process if there, or new one from process
                    if(!wait_queue.empty())
                    {
                        processor_list[i].current_process = wait_queue.front();
                        processor_list[i].has_process = true;
                        wait_queue.erase(wait_queue.begin());
                    }
                    else
                    {  
                        // If processes in memory wait queue...
                        if(!mem_wait_queue.empty())
                        {
                            Process next_process = mem_wait_queue.front();

                            // If they fit, load those
                            if(my_alloc_BF(memory, next_process))
                            {
                                processor_list[i].current_process = next_process;
                                processor_list[i].has_process = true;

                                mem_wait_queue.erase(mem_wait_queue.begin());
                            }
                        }
                        // Otherwise, load another process
                        else
                        {
                            Process next_process;
                            next_process = process_queue.front();

                            if((my_alloc_FF(memory, next_process)))
                            {                            
                                processor_list[i].current_process = next_process;
                                processor_list[i].has_process = true;

                                process_queue.erase(process_queue.begin());
                            }
                            else
                            {
                                mem_wait_queue.push_back(next_process);
                            }
                        }  
                    }
                }
            }
        }

        // Every 100 cycles...
        if(cycle % 100 == 0)
        {
            if(!process_queue.empty())
            {
                // Next process from process queue gets loaded into memory
                Process next_process = process_queue.front();

                // If it has a too high memory requirement, increment fails and erase it from queue
                if(next_process.memory_req > memory.size())
                {
                    fails += 1;
                    process_queue.erase(process_queue.begin() + next_process.id);
                    break;
                }
                // Otherwise, see if we can allocate it
                else if(my_alloc_BF(memory, next_process))
                {
                    ;
                }
                // If not, add to wait queue for mem 
                else
                {
                    mem_wait_queue.push_back(next_process);
                }
            }
            
            int free_processor_id;

            Process next_process = process_queue.front();

            // If there is room on the processor...
            if(has_room(processor_list))
            {
                // If no processes are waiting...
                if(wait_queue.empty() && !process_queue.empty())
                {
                    // Get the ID of a free processor, and load random process onto it
                    free_processor_id = free_processor(processor_list);
                    processor_list[free_processor_id].current_process = next_process;
                    processor_list[free_processor_id].has_process = true;

                    //cout << processor_list[free_processor_id].id << endl;
                    process_queue.erase(process_queue.begin());  
                }
                // If processes are in wait queue, load those
                else if(!wait_queue.empty())
                {
                    free_processor_id = free_processor(processor_list);
                    processor_list[free_processor_id].current_process = wait_queue.front();
                    processor_list[free_processor_id].has_process = true;
                    wait_queue.erase(wait_queue.begin());
                }
            }
            // Otherwise, push the new process into the wait cue
            else
            {
                wait_queue.push_back(next_process);

                process_queue.erase(process_queue.begin());
            }

            /*//Output
            print_processors(processor_list, cycle);

            int count = size_memory_mine(memory);
            cout << "MEM: " << count << endl;

            cout << "SIZE OF P QUEUE: " << process_queue.size() << endl;
            cout << "SIZE OF W QUEUE: " << wait_queue.size() << endl;
            cout << "SIZE OF MEM W QUEUE:" << mem_wait_queue.size() << endl;
            */
        } 
    }

    // While te wait queue is not empty (after process queue is empty)
    while(!wait_queue.empty())
    {
        cycle += 50; // Cycles go by 50 cycles, at 100 cycles a new process comes in and at 150 is the speed
                    // cycle_num % 100 = 0 then we are at a new 100th cycle, new process comes in
                    // cycle_num % 150 = 0 then it is 1 second for the processor

        // Increment processes on processors
        for(int i=0; i<processor_list.size();i++)
        {
            if(processor_list[i].has_process)
            {
                processor_list[i].current_process.cycles_worked -= 50;
            }
        }

        // Check if any process is done
        for(int i=0; i<processor_list.size();i++)
        {
            if(processor_list[i].has_process)
            {
                // If a process on a processor is done, push it to finished and load waiting process
                if(processor_list[i].current_process.cycles_worked <= 0)
                {
                    finished.push_back(processor_list[i].current_process);
                    
                    // Deallocate the memory 
                    my_free(memory, processor_list[i].current_process);
                
                    // Replace process with a waiting process 
                    processor_list[i].current_process = wait_queue.front();
                    processor_list[i].has_process = true;

                    wait_queue.erase(wait_queue.begin());

                    // If there are processes waiting due to memory...
                    if(!mem_wait_queue.empty())
                    {
                        Process next_process = mem_wait_queue.front();

                        // If they fit, add them to the wait queue
                        if(my_alloc_BF(memory, next_process))
                        {
                            wait_queue.push_back(next_process);

                            mem_wait_queue.erase(mem_wait_queue.begin());
                        }
                    }
                }
            }
        }

        /*
        print_processors(processor_list, cycle);

        int count = size_memory_mine(memory);
        cout << "MEM: " << count << endl;

        cout << "SIZE OF P QUEUE: " << process_queue.size() << endl;
        cout << "SIZE OF W QUEUE: " << wait_queue.size() << endl;
        cout << "SIZE OF MEM W QUEUE:" << mem_wait_queue.size() << endl;*/
    }

    // While there are still processes on processors (after wait queue empty)
    while(has_processes(processor_list))
    {
        cycle += 50; // Cycles go by 50 cycles, at 100 cycles a new process comes in and at 150 is the speed
                    // cycle_num % 100 = 0 then we are at a new 100th cycle, new process comes in
                    // cycle_num % 150 = 0 then it is 1 second for the processor

        // Increment processes on processors
        for(int i=0; i<processor_list.size();i++)
        {
            if(processor_list[i].has_process)
            {
                processor_list[i].current_process.cycles_worked -= 50;
            }
        }

        // Check if any process is done
        for(int i=0; i<processor_list.size();i++)
        {
            if(processor_list[i].has_process)
            {
                // If a process is done, replace it with a holder process
                if(processor_list[i].current_process.cycles_worked <= 0)
                {
                    finished.push_back(processor_list[i].current_process);

    
                    // Deallocate the memory
                    my_free(memory, processor_list[i].current_process); 

                    // If there are processes waiting due to memory...
                    if(!mem_wait_queue.empty())
                    {
                        Process next_process = mem_wait_queue.front();  // Set the front as next process

                        if(my_alloc_BF(memory, next_process))   // If we can fit it, assign it to a processor
                        {
                            processor_list[i].current_process = next_process;
                            processor_list[i].has_process = true;

                            mem_wait_queue.erase(mem_wait_queue.begin());   // Erase from mem_wait_queue
                        }
                    }
                    else    // Otherwise, if the queue is empty, just put a holder process to signal that the processor is done
                    {
                        // Holder process 
                            processor_list[i].current_process = holder_process;
                            processor_list[i].has_process = false;
                    }
                }
            }
        }

        /*//Output
        print_processors(processor_list, cycle);

        int count = size_memory_mine(memory);
        cout << "MEM: " << count << endl;

        cout << "SIZE OF P QUEUE: " << process_queue.size() << endl;
        cout << "SIZE OF W QUEUE: " << wait_queue.size() << endl;
        cout << "SIZE OF MEM W QUEUE:" << mem_wait_queue.size() << endl;
        */
        
    }
    // Output process info

    cout << "SCENARIO 3 BF: " << endl;
    cout << "--------------------" << endl;
    cout << endl;

    for(int i=0; i<finished.size(); i++)
    {
        cout << "PROCESS ID: " << finished[i].id << endl; 
        cout << "PROCESS ST: " << finished[i].service_time << endl; 
        cout << "PROCESS MR: " << finished[i].memory_req << endl; 
        
        cout << endl;
    }
    cout << "FAILED TO ALLOCATE: " << fails << endl;
    cout << "TOTAL CYCLES: " << cycle << endl;
}
