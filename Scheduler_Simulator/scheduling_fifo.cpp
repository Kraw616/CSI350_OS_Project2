/* Author: Jacob Krawitz (jkrawitz@muhlenberg.edu) 
   Date: 4/19/22
   Description: Runs scheduling simulation for the FIFO algorithm. Loads initial processes onto 4 processors, runs the simulation, and then finishes the last
   4 processes on the processor (more details on this in the GitHub wiki).For each process, records its turnaround, wait, and arrival time in the system. 
   In the end, outputs total turnaround time for the system and average wait time. 
*/

//INCLUDE STATEMENTS
#include "functions.h"

// NOTE: Please see functions.h for header/block comments.
void schedule_fifo(vector<Process>& process_queue, vector<Processor>& processor_list, int algorithm, int scenario)
{
    // INITIALIZE VARIABLES/OBJECTS
    vector<Process> finished_vector;    // Hold finished processes

    long long total_turnaround_time = 0;

    long long avg_turnaround_time = 0; 
    long long avg_wait_time = 0;

    int context_switches = 0;

    Process minimum_process;
    int minimum_id = 0;

    // LOAD INITIAL 4 PROCESSES ONTO PROCESSORS BEFORE SIMULATION BEGINS   
    if(scenario == 1 || scenario == 3)    // Arriving all at one time, so preloading same 
    {
        for(int i=0; i < processor_list.size(); i++)    // For each processor...
        {   
            while(!processor_list[i].has_process)   // While a processor does not have a process (for scenario 2)
            {
                if(process_queue.front().memory_req <= processor_list[i].memory_capability) // If the first process in the queue fits...
                {
                    processor_list[i].current_process = process_queue.front();  // load that process onto the processor and set has_process to true
                    processor_list[i].has_process = true;

                    context_switches += 1;  // initial context switches
                    process_queue.erase(process_queue.begin()); // remove just added process from the queue; akin to pop()
                    break; 
                }

                else    // Otherwise, if the process does not fit,
                {
                    process_queue.insert(process_queue.begin()+1, process_queue.front());   // Place the not fitting process (front) second to beginning
                    process_queue.erase(process_queue.begin()); // pop front                    
                }
            }            
        }
    }

    else if(scenario == 2)    // Arriving all at one time, so preloading same 
    {
        for(int i=0; i < processor_list.size(); i++)    // For each processor...
        {   
            while(!processor_list[i].has_process)   // While a processor does not have a process (for scenario 2)
            {
                for(int j=0; j < process_queue.size(); j++)
                {
                    if(process_queue[j].memory_req <= processor_list[i].memory_capability)
                    {
                        processor_list[i].current_process = process_queue[j];
                        processor_list[i].has_process = true;

                        context_switches += 1;
                        process_queue.erase(process_queue.begin() + j);
                        break;
                    }
                }
            }
        }
    }

    else if(scenario == 4) // Arrival times vary, need to sort queue
    {   
        // Sort process queue

        sort(process_queue.begin(), process_queue.end(), compare_arrival_times);    // Sort queue by arrival times (faster processes first)
        
        for(int i=0; i < processor_list.size(); i++)    // See above
        {   
            while(!processor_list[i].has_process)
            {
                if(process_queue.front().memory_req <= processor_list[i].memory_capability)
                {
                    processor_list[i].current_process = process_queue.front();
                    processor_list[i].has_process = true;

                    context_switches += 1;
                    process_queue.erase(process_queue.begin()); // pop front
                    break;
                }

                else
                {
                    process_queue.insert(process_queue.begin()+2, process_queue.front());
                    process_queue.erase(process_queue.begin()); // pop front
                }
            }            
        }
    }

   // SCENARIO 1

    if(scenario == 1)
    {
        Process holder_process; // Process to "load" once there are none left
        holder_process.cycles_worked = 1000000000000000;
    
        while(process_queue.empty() != true)    // While there are processes left in the queue...
        {
            long long minimum = 10000000000000;

            // Find the minimum of all the processes currently on the processors
            for(int i=0; i < processor_list.size(); i++)
            {
                if(processor_list[i].current_process.cycles_worked < minimum)
                {
                    minimum = processor_list[i].current_process.cycles_worked;
                    minimum_process = processor_list[i].current_process;
                    minimum_id = i;
                }

            }
            
            total_turnaround_time += processor_list[minimum_id].current_process.cycles_worked;  // Increment total system time by however long that minimum was

            processor_list[minimum_id].current_process.turnaround_time = total_turnaround_time - processor_list[minimum_id].current_process.arrival_time; // Calculate turnaround time, 
            // end - arrival for the process that just finished

            processor_list[minimum_id].current_process.wait_time = processor_list[minimum_id].current_process.turnaround_time - processor_list[minimum_id].current_process.service_time;
            // Calculate wait time for finished process (turnaround - service time)

            avg_wait_time += processor_list[minimum_id].current_process.wait_time;  // Increment average wait time (to be divided later)

            finished_vector.push_back(processor_list[minimum_id].current_process); // Add done process to finished vector for later output

            for(int i=0; i < processor_list.size(); i++)    // For every other process on the processors, decrement their time remaining by however long the finished process took
            {
                processor_list[i].current_process.cycles_worked -= minimum;
            }

            processor_list[minimum_id].current_process = fifo(process_queue, scenario); // Replace process with next process on the queue
            processor_list[minimum_id].has_process = true;

            process_queue.erase(process_queue.begin()); // Remove that process from the queue
            context_switches += 1;  // Increment a context switch

            /*// OUTPUT each process and it's cycles left
            for(int j=0; j < processor_list.size(); j++)
            {
                cout << processor_list[j].id << ": " << processor_list[j].current_process.id << ", " << processor_list[j].current_process.cycles_worked << endl;
            }*/
        }


        // LEFTOVER IN PROCESSORS ONCE PROCESS QUEUE RUNS OUT 
        for(int i=0; i < processor_list.size(); i++)
        {
            long long minimum = 10000000000000;

            // Find minimum
            for(int i=0; i < processor_list.size(); i++)
            {
                if(processor_list[i].current_process.cycles_worked < minimum)
                {
                    minimum = processor_list[i].current_process.cycles_worked;
                    minimum_process = processor_list[i].current_process;
                    minimum_id = i;
                }

            }

            total_turnaround_time += processor_list[minimum_id].current_process.cycles_worked;

            processor_list[minimum_id].current_process.turnaround_time = total_turnaround_time - processor_list[minimum_id].current_process.arrival_time; // Calculate turnaround time, 
            // end - arrival
            processor_list[minimum_id].current_process.wait_time = processor_list[minimum_id].current_process.turnaround_time - processor_list[minimum_id].current_process.service_time;
            // Calculate wait time for finished process (turnaround - service time)

            avg_wait_time += processor_list[minimum_id].current_process.wait_time;

            finished_vector.push_back(processor_list[minimum_id].current_process); // Add first done process to finished
            processor_list[minimum_id].has_process = false;

            for(int i=0; i < processor_list.size(); i++)
            {
                processor_list[i].current_process.cycles_worked -= minimum;
            }

            processor_list[minimum_id].current_process = holder_process; // Replace process with a holder instead of next in process queue, so it doesn't get picked as minimum again
            processor_list[minimum_id].has_process = true;

            context_switches += 1; 

            /*// OUTPUT each process and it's cycles left
            for(int j=0; j < processor_list.size(); j++)
            {
                cout << processor_list[j].id << ": " << processor_list[j].current_process.id << ", " << processor_list[j].current_process.cycles_worked << endl;
            }*/
        }
    }

    // SCENARIO 2 (Different memory capabiltiies)

    else if(scenario == 2)
    {
        Process holder_process;
        holder_process.cycles_worked = 10000000000000;
        holder_process.id = 0;
    
        // Cycle while processes can be replaced 
        while(process_queue.empty() != true)
        {
            long long minimum = 10000000000000;

            // Find minimum
            for(int i=0; i < processor_list.size(); i++)
            {
                if(processor_list[i].current_process.cycles_worked < minimum)
                {
                    minimum = processor_list[i].current_process.cycles_worked;
                    minimum_process = processor_list[i].current_process;
                    minimum_id = i;
                }

            }
            
            // Add to total turnaround time
            total_turnaround_time += processor_list[minimum_id].current_process.cycles_worked;

            //Calculate turnaround time end-arrival
            processor_list[minimum_id].current_process.turnaround_time = total_turnaround_time - processor_list[minimum_id].current_process.arrival_time; // Calculate turnaround time, 

            // Calculate wait time for finished process (turnaround - service time)
            processor_list[minimum_id].current_process.wait_time = processor_list[minimum_id].current_process.turnaround_time - processor_list[minimum_id].current_process.service_time;

            // Add to avg_wait_time to be divided by 50 later 
            avg_wait_time += processor_list[minimum_id].current_process.wait_time;

            // First process to be done is pushed onto finished list
            finished_vector.push_back(processor_list[minimum_id].current_process); 
            processor_list[minimum_id].has_process = false;

            // Subtract other process's service time by finished process's time on processor
            for(int i=0; i < processor_list.size(); i++)
            {
                processor_list[i].current_process.cycles_worked -= minimum;
            }

            // While the processor needs to be filled...
            while(!processor_list[minimum_id].has_process)
            {
                for(int i=0; i < process_queue.size(); i++) // For each process
                {
                    if(process_queue[i].memory_req <= processor_list[minimum_id].memory_capability) // If that process fits on the processor
                    {
                        processor_list[minimum_id].current_process = process_queue[i];  // Set that process on the processor
                        processor_list[minimum_id].has_process = true;

                        context_switches += 1;
                        process_queue.erase(process_queue.begin() + i); // Erase the process from the process queue

                        //cout << process_queue[i].id << endl;

                        break;  // Break out of loop b/c we are done
                    }
                }
                if(processor_list[minimum_id].has_process == false) // If by the end we still don't have a process,
                // no processes will fit in that processor anymore. Thus, we render it inactive (holder_process)
                {
                    processor_list[minimum_id].current_process = holder_process;
                    break;
                }
                
            }
        }
        
        // Leftover in processors 
        for(int i=0; i < processor_list.size(); i++)
        {
            if(processor_list[i].has_process)   // We only want to run as long as a processor still has a process
            {
                long long minimum = 10000000000000;

                // Find minimum
                for(int i=0; i < processor_list.size(); i++)
                {
                    if(processor_list[i].current_process.cycles_worked < minimum)
                    {
                        minimum = processor_list[i].current_process.cycles_worked;
                        minimum_process = processor_list[i].current_process;
                        minimum_id = i;
                    }

                }

                total_turnaround_time += processor_list[minimum_id].current_process.cycles_worked;

                processor_list[minimum_id].current_process.turnaround_time = total_turnaround_time - processor_list[minimum_id].current_process.arrival_time; // Calculate turnaround time, 
                // end - arrival
                processor_list[minimum_id].current_process.wait_time = processor_list[minimum_id].current_process.turnaround_time - processor_list[minimum_id].current_process.service_time;
                // Calculate wait time for finished process (turnaround - service time)

                avg_wait_time += processor_list[minimum_id].current_process.wait_time;

                finished_vector.push_back(processor_list[minimum_id].current_process); // Add first done process to finished
                processor_list[minimum_id].has_process = false;


                for(int i=0; i < processor_list.size(); i++)
                {
                    processor_list[i].current_process.cycles_worked -= minimum;
                }

                processor_list[minimum_id].current_process = holder_process; // Replace process
                processor_list[minimum_id].has_process = true;

                context_switches += 1; 
            }
            
        }

    }

    // SCENARIO 3 (Different speeds)

    else if(scenario == 3)
    {
        for(int i=0; i < processor_list.size(); i++)
            {
                processor_list[i].current_process.cycles_worked /= (processor_list[i].speed / 4);   // Cycles remaining take into account the speed of the processors
                // A processor at 3 GHz runs 3/4 as fast as a processor at 4 GHz, which runs 1x as fast
                processor_list[i].current_process.service_time = processor_list[i].current_process.cycles_worked; // Service time + speeds
            }

        Process holder_process;
        holder_process.cycles_worked = 10000000000000;
    
        // Cycle while processes can be replaced 
        while(process_queue.empty() != true)
        {
            long long minimum = 10000000000000;

           // Find minimum
            for(int i=0; i < processor_list.size(); i++)
            {
                if(processor_list[i].current_process.cycles_worked < minimum)
                {
                    minimum = processor_list[i].current_process.cycles_worked;
                    minimum_process = processor_list[i].current_process;
                    minimum_id = i;

                }
            }

            total_turnaround_time += minimum;

            processor_list[minimum_id].current_process.turnaround_time = total_turnaround_time - processor_list[minimum_id].current_process.arrival_time; // Calculate turnaround time, 
            // end - arrival
            processor_list[minimum_id].current_process.wait_time = processor_list[minimum_id].current_process.turnaround_time - minimum;
            // Calculate wait time for finished process (turnaround - service time)

            avg_wait_time += processor_list[minimum_id].current_process.wait_time;

            finished_vector.push_back(processor_list[minimum_id].current_process); // Add first done process to finished 

            for(int i=0; i < processor_list.size(); i++)
            {
                processor_list[i].current_process.cycles_worked -= minimum;
            }

            processor_list[minimum_id].current_process = fifo(process_queue, scenario); // Replace process
            process_queue.erase(process_queue.begin()); // pop front
            context_switches += 1;
        }

        // Leftover in processors

        for(int i=0; i < processor_list.size(); i++)
        {
            for(int i=0; i < processor_list.size(); i++)
            {
                processor_list[i].current_process.cycles_worked /= (processor_list[i].speed / 4);   // Cycles remaining take into account the speed of the processors
                // A processor at 3 GHz runs 3/4 as fast as a processor at 4 GHz, which runs 1x as fast
                processor_list[i].current_process.service_time = processor_list[i].current_process.cycles_worked; // Service time + speeds
            }
            
            long minimum = 10000000000000;

            // Find minimum
            for(int i=0; i < processor_list.size(); i++)
            {
                if(processor_list[i].current_process.cycles_worked < minimum)
                {
                    minimum = processor_list[i].current_process.cycles_worked;
                    minimum_process = processor_list[i].current_process;
                    minimum_id = i;

                }
            }

            total_turnaround_time += minimum;

            processor_list[minimum_id].current_process.turnaround_time = total_turnaround_time - processor_list[minimum_id].current_process.arrival_time; // Calculate turnaround time, 
            // end - arrival
            processor_list[minimum_id].current_process.wait_time = processor_list[minimum_id].current_process.turnaround_time - processor_list[minimum_id].current_process.service_time;
            // Calculate wait time for finished process (turnaround - service time)

            avg_wait_time += processor_list[minimum_id].current_process.wait_time;

            finished_vector.push_back(processor_list[minimum_id].current_process); // Add done process to finished 

            for(int i=0; i < processor_list.size(); i++)
            {
                processor_list[i].current_process.cycles_worked -= minimum;
            }

            processor_list[minimum_id].current_process = holder_process; // Replace process with holder process
            context_switches += 1;
        }
    }

    // SCENARIO 4 (Different arrival times)
    else if(scenario == 4)
    {
        Process holder_process;
        holder_process.cycles_worked = 1000000000000000;

        vector<Process> arrived_queue;  // Vector to hold processes that have arrived (processes load processes from here instead of process_queue)
    
        // Cycle while processes can be replaced 
        while(process_queue.empty() != true || arrived_queue.empty() != true)
        {
            // Check if processes have arrived, and if so, add them to the arrived queue
            for(int i=0; i < process_queue.size(); i++)
            {
                if(process_queue[i].arrival_time <= total_turnaround_time)
                {
                    arrived_queue.push_back(process_queue[i]);  // Process arrived
                    process_queue.erase(process_queue.begin() + i); // Remove from process queue
                }
            }

            // Fill empty processors
            if(arrived_queue.empty() != true)
            {
                for(int i=0; i < processor_list.size(); i++)
                {
                    if(!processor_list[i].has_process)  // For each process, if they don't have a process, assign them a process from arrived queue
                    {
                        processor_list[i].current_process = fifo(arrived_queue);
                        arrived_queue.pop_back();

                        processor_list[i].has_process = true;
                        context_switches += 1;
                    }
                }
            }
           
            long long minimum = 10000000000000;

            // Find minimum
            for(int i=0; i < processor_list.size(); i++)
            {
                if(processor_list[i].current_process.cycles_worked < minimum && processor_list[i].has_process)
                {
                    minimum = processor_list[i].current_process.cycles_worked;
                    minimum_process = processor_list[i].current_process;
                    minimum_id = i;
                }

            }

            // Update total turnaround time (time the system has been running)
            total_turnaround_time += processor_list[minimum_id].current_process.cycles_worked;

            processor_list[minimum_id].current_process.turnaround_time = total_turnaround_time - processor_list[minimum_id].current_process.arrival_time; // Calculate turnaround time, 
            // end - arrival
            processor_list[minimum_id].current_process.wait_time = processor_list[minimum_id].current_process.turnaround_time - processor_list[minimum_id].current_process.service_time;
            // Calculate wait time for finished process (turnaround - service time)

            avg_wait_time += processor_list[minimum_id].current_process.wait_time;

            // Add finished process to the finished list, and indicate it no longer has a process
            finished_vector.push_back(processor_list[minimum_id].current_process); // Add first done process to finished 
            processor_list[minimum_id].has_process = false;

            // Update other processes's time left on other processors
            for(int i=0; i < processor_list.size(); i++)
            {
                processor_list[i].current_process.cycles_worked -= minimum;
            }

            // If there are available processes, replace just finished process
            if(arrived_queue.empty() != true) 
            {
                processor_list[minimum_id].current_process = fifo(arrived_queue);
                arrived_queue.pop_back(); // Get rid of process

                context_switches += 1;
                processor_list[minimum_id].has_process = true;
            }
        }


       // Leftover in processors 
        for(int i=0; i < processor_list.size(); i++)
        {
            long long minimum = 10000000000000;

            // Find minimum
            for(int i=0; i < processor_list.size(); i++)
            {
                if(processor_list[i].current_process.cycles_worked < minimum)
                {
                    minimum = processor_list[i].current_process.cycles_worked;
                    minimum_process = processor_list[i].current_process;
                    minimum_id = i;
                }

            }

            total_turnaround_time += processor_list[minimum_id].current_process.cycles_worked;

            processor_list[minimum_id].current_process.turnaround_time = total_turnaround_time - processor_list[minimum_id].current_process.arrival_time; // Calculate turnaround time, 
            // end - arrival
            processor_list[minimum_id].current_process.wait_time = processor_list[minimum_id].current_process.turnaround_time - processor_list[minimum_id].current_process.service_time;
            // Calculate wait time for finished process (turnaround - service time)

            avg_wait_time += processor_list[minimum_id].current_process.wait_time;

            finished_vector.push_back(processor_list[minimum_id].current_process); // Add first done process to finished

            for(int i=0; i < processor_list.size(); i++)
            {
                processor_list[i].current_process.cycles_worked -= minimum;
            }

            processor_list[minimum_id].current_process = holder_process; // Replace process with a holder, so it doesn't get picked as minimum again
            context_switches += 1; 
        }
    }

    // OUTPUT

    unsigned long long avg_service_time = 0;
    long long avg_arrival_time = 0;
    int avg_mem_req = 0;

    // Calculate average arrival time, service time, memory requirements by iterating through finished vector
    for(int i=0; i<finished_vector.size(); i++)
    {
        avg_service_time += finished_vector[i].service_time;
        avg_arrival_time += finished_vector[i].arrival_time;
        avg_mem_req += finished_vector[i].memory_req;
    }

    avg_wait_time = avg_wait_time / 50; // Calculate average wait time (all wait times / 50)
    avg_turnaround_time = total_turnaround_time / 50;

    avg_service_time = avg_service_time / 50;   // Calculate averages
    avg_arrival_time = avg_arrival_time / 50;
    avg_mem_req = avg_mem_req / 50;
    
    // OUTPUT STATISTICS FOR EACH PROCESS THAT FINISHED
    for(int i=0; i<finished_vector.size(); i++)
    {
        cout << "PROCESS ID: " << finished_vector[i].id << endl;
        cout << "Service time: " << finished_vector[i].service_time << endl;
        cout << "Arrival time: " << finished_vector[i].arrival_time << endl;
        cout << "Memory requirement: " << finished_vector[i].memory_req << endl;
        cout << "Wait time: " << finished_vector[i].wait_time << endl;
        cout << "Total time in system: " << finished_vector[i].wait_time + finished_vector[i].service_time << endl;
        cout << endl;
    }

    // OUTPUT SUMMARY STATS
    cout << endl;
    cout << "Total turnaround time: " << total_turnaround_time << endl;
    cout << "Average turnaround time: " << avg_turnaround_time << endl;
    cout << "Average wait time: " << avg_wait_time << endl;
    cout << "Context switches: " << context_switches << endl;
    cout << "Average service time: " << avg_service_time << endl;
    cout << "Average arrival time: " << avg_arrival_time << endl;
    cout << "Average memory requirement: " << avg_mem_req << endl;
    cout << endl;

}
