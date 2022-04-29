/* Author: Jacob Krawitz (jkrawitz@muhlenberg.edu) 
   Date: 4/19/22
   Description: Header file including all #include statements and function declarations to be used in .cpp files.
    Header comments found here!
*/

// INCLUDE STATEMENTS
#include <stdlib.h>
#include <iostream>
#include <random>
#include <queue>
#include <vector>
#include <algorithm>

#include "processes.h"

/*
Method: scenario_menu()
Prompts the user for their choice of scenario, and returns their choice. Performed in a loop until a valid answer is given.

@returns an integer of the user's choice of scenario

DEFINED IN: setup.cpp
*/
int scenario_menu();

/*
Method: algorithm_menu()
Prompts the user for their choice of algorithm (FIFO, SJR, RR, or ML), and returns their choice. Performed in a loop until a valid answer is given.

@returns an integer of the user's choice of algorithm, converted from their string answer

DEFINED IN: setup.cpp
*/
int algorithm_menu();

/*
Method: seed_and_create_processes()
Depending on the algorithm, creates processes and puts them into the proper data structure for the algorithm.
Also prompts the user for and seeds the random number generator, which uses a 64-bit Mersenne Twister generator along with a uniform integer distribution.

@params an integer that represents the algorithm of choice
@returns a queue (for now) containing all of the process objects of the class Process

DEFINED IN: setup.cpp
*/
vector<Process> seed_and_create_processes(int algorithm, int scenario);

/*
Method: create_processors()
Depending on the scenario chosen, creates processors with corresponding memory capabilities and speeds. Creates 4 processes
and pushes them onto a processor list.

@params an integer representing the chosen scenario, which determines how the processes are intiialized
@returns a list of Processor objects containing the four processors in the simulation

DEFINED IN: setup.cpp
*/
vector<Processor> create_processors(int scenario);

/*
Method: compare_arrival_times
Given two process objects, returns the process with the lower (sooner) arrival time. DEFINED as the third
parameter in the sort() method to sort the process vector by lowest/quickest arrival time. Used in scenario 4.

@params Two processes to compare, p1 and p2
@returns true or false boolean value if p1's arrival time is less than p2's arrival time

USED IN: setup.cpp
*/
bool compare_arrival_times(Process p1, Process p2);


/*
Method: compare_service_times
Given two process objects, returns the process with the lower service time. Used as the third
parameter in the sort() method to sort the process vector by lowest/quickest service time. Used in SRT algorithm.

@params Two processes to compare, p1 and p2
@returns true or false boolean value if p1's service time is less than p2's service time

DEFINED IN: setup.cpp
*/
bool compare_service_times(Process p1, Process p2);

/*
Method: fifo
Depending on scenario, returns the next process to be loaded onto a processor. In the FIFO
scheduling method, this is typically the front/next value in the queue.

@params The process queue pointer, and the current scenario
@returns The next process to be scheduled; front of the queue (FIFO)

DEFINED IN: fifo_and_srt.cpp
*/
Process fifo(vector<Process>& process_queue, int scenario);

/*
Method: fifo (overloaded)
Overloaded version of fifo function. In scenario 4, the processors can only schedule processes that are present in
the system (AKA that have arrived), so this functions returns the next process out of the arrived_process queue.

@params The arrived_queue vector that stores all the processes that have arrived.
@returns The next process to be scheduled; front of the arrived_process queue (FIFO)

DEFINED IN: fifo_and_srt.cpp
*/
Process fifo(vector<Process>& arrived_list);

/*
Method: SRT
Determines and returns the next process to be sceduled in an SRT strategy, depending on the scenario. Since the 
processes are pre-sorted by service times, the shortest process (which goes next) is at the front of the queue. Therefore,
this function returns the front of the process queue once again.

@params The process queue and the scenario chosen
@returns The next process to be scheduled; the shortest remaining time (front of sorted process vector)

DEFINED IN: fifo_and_srt.cpp
*/
Process SRT(vector<Process>& process_queue, int scenario);

/*
Method: SRT (overloaded)

@params The process queue and the scenario chosen
@returns The next process to be scheduled; the shortest remaining time (front of sorted process vector)

DEFINED IN: fifo_and_srt.cpp
*/
Process SRT(vector<Process>& arrived_queue);


/*
Method: schedule_fifo
Main scheduling method for FIFO in this simulation.
Taking into account the scenario chosen (processor/processor conditions), loads initial processes onto the processors and performs a simulated FIFO schedule.
At the end, outputs each process in the order they were finished along with their service time, arrival time, memory requirement, wait time, and total time in the system.


@params The process queue vector, processor list vector, the user's choice of algorithm, and the user's choice of scenario

DEFINED IN: scheduling_fifo.cpp
*/
void schedule_fifo(vector<Process>& process_queue, vector<Processor>& processor_list, int algorithm, int scenario);


/*
Method: schedule_SRT
Main scheduling method for SRT in this simulation.
Taking into account the scenario chosen, loads initial processes onto the processors and performs a simulated SRT schedule (details below). 
At the end, outputs each process in the order they were finished along with their service time, arrival time, memory requirement, wait time, and total time in the system. 
Similar to FIFO, although the process queue is sorted by service time at the beginning to simulate the shortest job being first (and reduce iterations through the process queue).

@params The process queue vector, processor list vector, the user's choice of algorithm, and the user's choice of scenario

DEFINED IN: scheduling_srt.cpp
*/
void schedule_SRT(vector<Process>& process_queue, vector<Processor>& processor_list, int algorithm, int scenario);















