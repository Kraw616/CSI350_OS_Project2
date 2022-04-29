/* Author: Jacob Krawitz (jkrawitz@muhlenberg.edu) 
   Date: 4/19/22
   Description: Contains the definition for the fifo() and SRT() methods, which return the process next to be scheduled.
   In FIFO, the next process to be scheduled is the next one in the queue; in SRT, the next process to be scheduled is the process
   with the lowest remaining service time (or the front of a sorted-by-service-time queue). For scenario 4, these methods are 
   overloaded.
*/

// INCLUDE STATEMENTS
#include "functions.h"

// NOTE: Please see functions.h for header/block comments.
Process fifo(vector<Process>& process_queue, int scenario)
{
    if(scenario == 1 || scenario == 3)
    {
        Process to_return = process_queue.front();
        //process_queue.erase(process_queue.begin());
        return to_return;
    }
    else if(scenario == 2)
    {
        Process to_return = process_queue.back();   // Return back in scenario 2, because we push back
        //process_queue.erase(process_queue.begin());
        return to_return;
    }
}

// Overloaded for scenario 4
Process fifo(vector<Process>& arrived_queue)
{
    return arrived_queue.back();
}

Process SRT(vector<Process>& process_queue, int scenario)
{
    if(scenario == 1 || scenario == 3)
    {
        Process to_return = process_queue.front();
        //process_queue.erase(process_queue.begin());
        return to_return;
    }
    else if(scenario == 2)
    {
        Process to_return = process_queue.back();   // Return back in scenario 2, because we push back
        //process_queue.erase(process_queue.begin());
        return to_return;
    }
    /*if(scenario == 1)
    {
        long long minimum = 100000000000;
        int minimum_id;
        Process to_return;
        for(int i=0; i < process_queue.size(); i++)
        {
            if(process_queue[i].service_time < minimum)
            {
                minimum = process_queue[i].service_time;
                minimum_id = i;
            }
        }
        to_return = process_queue[minimum_id];
        process_queue.erase(process_queue.begin() + minimum_id);
        return to_return;  
    }*/
}

Process SRT(vector<Process>& arrived_queue)
    {
        Process to_return;
        Process minimum_process;
        long long minimum = 1000000000000;
        int minimum_id;

        for(int i=0; i<arrived_queue.size(); i++)
        {
            if(arrived_queue[i].cycles_worked < minimum)
            {
                minimum = arrived_queue[i].cycles_worked;
                minimum_process = arrived_queue[i];
                minimum_id = i;
            }
        }
        arrived_queue.erase(arrived_queue.begin() + minimum_id);
        return minimum_process;
    }
