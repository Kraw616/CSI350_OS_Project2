/* Author: Jacob Krawitz (jkrawitz@muhlenberg.edu) 
   Date: 4/19/22
   Description: Main file for Project 1. Prompts user for the scenario and algorithm they would like to perform, then
   runs the appropriate combination and outputs the correct output. Assigns processes with randomly assigned service times and memory requirements
   to one of four processors. Simulates scheduling algorithms!

    ALGORITHMS:
    FIFO (First-in First-out)
    SRT (Shortest remaining time)


    SCENARIOS:
    1 = All four processors are identical with a speed of 3GHz and a memory capacity of 8GB 
    2 = All four processors have identical speeds, 3GHz, but varying memory availability. P1 and P2 have 2GB, P3 has 
        4GB, and P4 has 8GB 
    3 = All four processors have identical memory availability, 8GB, but varying speeds. P1 and P2 are 2GHz, P3 is 3GHz, 
        and P4 is 4GHz 
    4 = All four processors are identical with a speed of 3GHz and a memory capacity of 8GB. Your system must handle 
        the processes based on their arrival times, i.e. you cannot inspect the entire set of processes, but must schedule 
        them as they arrive in the system 
*/

// INCLUDE STATEMENTS
#include <stdlib.h>
#include <iostream>
#include <random>
#include <queue>
#include <list>
#include <vector>

#include "functions.h"

using namespace std;


/*Method main()
Driver method.

*/
int main()
{
    int scenario_choice;
    int algorithm_choice;

    vector<Process> process_queue;
    vector<Processor> processor_list;

    scenario_choice = scenario_menu();

    algorithm_choice = algorithm_menu();

    process_queue = seed_and_create_processes(algorithm_choice, scenario_choice);

    processor_list = create_processors(scenario_choice);

    if(algorithm_choice == 1)   // Depending on algorithm choice, run corresponding scheduling simulation.
    {
        schedule_fifo(process_queue, processor_list, algorithm_choice, scenario_choice);

    }
    else if(algorithm_choice == 2)
    {
        schedule_SRT(process_queue, processor_list, algorithm_choice, scenario_choice);
    }

}