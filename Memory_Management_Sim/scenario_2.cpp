/* Author: Jacob Krawitz (jkrawitz@muhlenberg.edu) 
   Date: 4/29/22
   Description: Defines function for scenario 2 (I handle allocation).

   ** NOTE **
   Outputs are possible to see, but are commented out.
*/

#include "functions.h"


// Scenario 2, FF
void scenario_2_FF(vector<Process> process_queue, vector<Processor> processor_list, vector<Slot> memory)
{
    // Keep track of cycles taken in the system
    int cycle = 0;

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

    // Preload processes
    for(int i=0; i<processor_list.size();i++)
    {
        // Load into memory
        my_alloc_FF(memory, process_queue[i]);

        // Load onto processor
        processor_list[i].current_process = process_queue[i];
        processor_list[i].has_process = true;
        process_queue.erase(process_queue.begin() + i);
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
            
                    // If the pointer is loaded into memory...
                    
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
                        Process next_process;
                        next_process = process_queue.front();


                        if(my_alloc_FF(memory, next_process))
                        {                        
                            processor_list[i].current_process = next_process;
                            processor_list[i].has_process = true;

                            process_queue.erase(process_queue.begin());

                        }
                    }
                }
            }
        }

        // Every 100 cycles...
        if(cycle % 100 == 0)
        {
            
            Process next_process;

            if(!process_queue.empty())
            {
                // Next process from process queue gets loaded into memory
                next_process = process_queue.front();

                if((size_memory_mine(memory) < 10000))
                {
                    my_alloc_FF(memory, next_process);
                }
            }
            
            int free_processor_id;

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
                else
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

            /* Output
            print_processors(processor_list, cycle);

            int count = memory.size();
            cout << "MEM: " << count << endl;

            cout << "SIZE OF P QUEUE: " << process_queue.size() << endl;
            cout << "SIZE OF W QUEUE: " << wait_queue.size() << endl;*/
        } 
    }

    // While te wait queue is not empty (after process queue is empty)
    while(!wait_queue.empty())
    {
        int *ptr;

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
                }
            }
        }
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
    }
    // Output process info

    cout << "SCENARIO 2 FF: " << endl;
    cout << "--------------------" << endl;
    cout << endl;

    for(int i=0; i<finished.size(); i++)
    {
        cout << "PROCESS ID: " << finished[i].id << endl; 
        cout << "PROCESS ST: " << finished[i].service_time << endl; 
        cout << "PROCESS MR: " << finished[i].memory_req << endl; 
        
        cout << endl;
    }
}

// Scenario 2, BF
void scenario_2_BF(vector<Process> process_queue, vector<Processor> processor_list, vector<Slot> memory)
{
    // Keep track of cycles taken in the system
    int cycle = 0;

    // Holder process for once all processes except ones on processors done
    Process holder_process;
    holder_process.id = -1;

    // Vectors to hold finished processes, processes that are waiting for processors to free up,
    // and a processor to hold processes waiting due to no memory availability
    vector<Process> finished;
    vector<Process> wait_queue;
    vector<Process> mem_wait_queue;

    // Preload processes
    for(int i=0; i<processor_list.size();i++)
    {
        // Load into memory
        my_alloc_BF(memory, process_queue[i]);

        // Load onto processor
        processor_list[i].current_process = process_queue[i];
        processor_list[i].has_process = true;
        process_queue.erase(process_queue.begin() + i);
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
            
                    // If the pointer is loaded into memory...
                    
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
                        Process next_process;
                        next_process = process_queue.front();


                        if(my_alloc_BF(memory, next_process))
                        {                        
                            processor_list[i].current_process = next_process;
                            processor_list[i].has_process = true;

                            process_queue.erase(process_queue.begin());

                        }
                    }
                }
            }
        }

        // Every 100 cycles...
        if(cycle % 100 == 0)
        {
            
            Process next_process;

            if(!process_queue.empty())
            {
                // Next process from process queue gets loaded into memory
                next_process = process_queue.front();

                if(!(size_memory_mine(memory) >= 10000))
                {
                    my_alloc_BF(memory, next_process);
                }
            }
            
            int free_processor_id;

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
                else
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

            /* Output
            print_processors(processor_list, cycle);

            int count = memory.size();
            cout << "MEM: " << count << endl;

            cout << "SIZE OF P QUEUE: " << process_queue.size() << endl;
            cout << "SIZE OF W QUEUE: " << wait_queue.size() << endl;*/
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
                }
            }
        }
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
    }
    // Output process info

    cout << "SCENARIO 2 BF: " << endl;
    cout << "--------------------" << endl;
    cout << endl;

    for(int i=0; i<finished.size(); i++)
    {
        cout << "PROCESS ID: " << finished[i].id << endl; 
        cout << "PROCESS ST: " << finished[i].service_time << endl; 
        cout << "PROCESS MR: " << finished[i].memory_req << endl; 
        
        cout << endl;
    }
}
