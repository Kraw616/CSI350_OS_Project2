/* Author: Jacob Krawitz (jkrawitz@muhlenberg.edu) 
   Date: 5/06/22
   Description: Header file for all functions uses across .cpp files. Acts as the main linker file for the program. Includes all libraries used aswell.
*/

// INCLUDE STATEMENTS
#include <chrono> // To measure system time
#include <stdlib.h>
#include <iostream>
#include <random> // Random numbers
#include <vector>

#include "processes.h"

using namespace std;

/*
Method: print_processors()
Method that prints all the processors and what processes occupies them. Used for optional output of each processor at each step of the simulation.

@params A list of processors, an int value of how many simulated cycles the system has been through
@returns 

DEFINED IN: functions.cpp
*/
void print_processors(vector<Processor> processor_list, int cycles);

/*
Method: seed_and_created_processes()
Creates and seeds 50 processes. Service times assigned randomly between 200 and 2000 cycles, and memory requirements were assigned randomly in a normal distrubtion
with a mean of 200 and standard deviation of 75. The max of all the processes' memory requirements is 10,000. Each process is given a bit of 10,000 until the last process,
which is given however much space is left to allocate. This creates a base process queue that is copied for each scenario/implementation.

@params An integer seed that is input by the user in main.cpp
@returns A vector of processes; process queue

DEFINED IN: setup.cpp
*/
vector<Process> seed_and_create_processes(int seed);

/*
Method: create_processors()
Creates 4 processors with unique IDs and speeds, and pushes them onto a list.

@params None
@returns a vector of processors

DEFINED IN: setup.cpp
*/
vector<Processor> create_processors();

/*
Method: create_memory_2()
Creates a vector of Slot objects with a size of 10,000 for use in scenario 2.

@params None
@returns A memory vector to be used in scenario 2

DEFINED IN: setup.cpp
*/
vector<Slot> create_memory_2();

/*
Method: create_memory_3()
Creates a vector of Slot objects with a size of 5,000 for use in scenario 3.

@params None
@returns A memory vector to be used in scenario 3

DEFINED IN: setup.cpp
*/
vector<Slot> create_memory_3();

/*
Method: create_memory_4()
Creates a vector of Slot objects with a size of 1,000 for use in scenario 4.

@params None
@returns A memory vector to be used in scenario 4

DEFINED IN: setup.cpp
*/
vector<Slot> create_memory_4();

/*
Method: has_room()
Given a list of processors, gives a T/F value if there are open spaces on any of the processors.

@params A list/vector of processors
@returns A boolean T/F if there is any room on the processors

DEFINED IN: functions.cpp
*/
bool has_room(vector<Processor> processor_list);

/*
Method: has_processes()
Given a list of processors, gives a T/F value if there are currently processes on any of the processors.

@params A list/vector of processors
@returns A boolean T/F if there are any processes on the processors

DEFINED IN: functions.cpp
*/
bool has_processes(vector<Processor> processor_list);

/*
Method: size_memory
Given a vector of pointers, gives the amount of filled slots A.K.A. how much memory is used. Method used in scenario 1.

@params A vector of pointers
@returns An int that gives how many slots are filled.

DEFINED IN: functions.cpp
*/
int size_memory(vector<int*> pointers);

/*
Method: size_memory_mine()
Given a vector of slot objects (memory), determines how many slots are being taken up by a process. Used for scenarios 2-4 where I create my own representation of memory.

@params A vector of slot objects; memory vector
@returns An int that gives how many slots are filled.

DEFINED IN: functions.cpp
*/
int size_memory_mine(vector<Slot> memory);

/*
Method: free_processor()
From a list of processors, determines what processor has an availability. 

@params  A list of processors
@returns An int id of which processor is free

DEFINED IN: functions.cpp
*/
int free_processor(vector<Processor> processor_list);

/*
Method: size_hole()
Given a vector of slot objects, determines the size of a hole. Starts at a given index of the vector, and interates until an occupied slot is reached.
Outputs the size of how long it took to get to an occupied slot; how large of an open space there is.

@params A vector of slots memory, an int start for the index of where the hole begins
@returns int index of the size of a given hole

DEFINED IN: functions.cpp
*/
int size_hole(vector<Slot> memory, int start);

/*
Method: scenario_1()
Given 50 processes, schedules them in a FIFO manner. These processes are allocated and deallocated to memory using malloc() and free() before they are scheduled.
In this scenario, the OS handles memory allocation. Outputs information about each finished process (mem req, service time, etc.).

@params A process queue of processes to schedule, and a list of processor to schedule these processes onto
@returns None

DEFINED IN: scenario_1.cpp
*/
void scenario_1(vector<Process> process_queue, vector<Processor> processor_list);

/*
Method: scenario_2_FF()
Given 50 processes, schedules them in a FIFO manner. Unlike scenario 1, uses an array of slot objects to represent available memory.
These processes are allocated and deallocated to our vector memory using my_alloc() and my_free() before they are scheduled.
In this scenario, we handle memory allocation of a 10mb chunk in a First-Fit memory allocation method. Outputs information about each finished process (mem req, service time, etc.).

@params A process queue of processes to schedule, and a list of processor to schedule these processes onto, a vector of Slot objects to represent our 10mb chunk of memory 
@returns None

DEFINED IN: scenario_2.cpp
*/
void scenario_2_FF(vector<Process> process_queue, vector<Processor> processor_list, vector<Slot> memory);

/*
Method: scenario_2_BF()
Given 50 processes, schedules them in a FIFO manner. Unlike scenario 1, uses an array of slot objects to represent available memory.
These processes are allocated and deallocated to our vector memory using my_alloc() and my_free() before they are scheduled.
In this scenario, we handle memory allocation of a 10mb chunk in a Best-Fit memory allocation method. Outputs information about each finished process (mem req, service time, etc.).

@params A process queue of processes to schedule, and a list of processor to schedule these processes onto, a vector of Slot objects to represent our 10mb chunk of memory 
@returns None

DEFINED IN: scenario_2.cpp
*/
void scenario_2_BF(vector<Process> process_queue, vector<Processor> processor_list, vector<Slot> memory);

/*
Method: scenario_3_FF()
Given 50 processes, schedules them in a FIFO manner. Unlike scenario 1, uses an array of slot objects to represent available memory.
These processes are allocated and deallocated to our vector memory using my_alloc() and my_free() before they are scheduled.
In this scenario, we handle memory allocation of a 5mb chunk in a First-Fit memory allocation method. Outputs information about each finished process (mem req, service time, etc.).

@params A process queue of processes to schedule, and a list of processor to schedule these processes onto, a vector of Slot objects to represent our 5mb chunk of memory 
@returns None

DEFINED IN: scenario_3.cpp
*/
void scenario_3_FF(vector<Process> process_queue, vector<Processor> processor_list, vector<Slot> memory);

/*
Method: scenario_3_BF()
Given 50 processes, schedules them in a FIFO manner. Unlike scenario 1, uses an array of slot objects to represent available memory.
These processes are allocated and deallocated to our vector memory using my_alloc() and my_free() before they are scheduled.
In this scenario, we handle memory allocation of a 5mb chunk in a Best-Fit memory allocation method. Outputs information about each finished process (mem req, service time, etc.).

@params A process queue of processes to schedule, and a list of processor to schedule these processes onto, a vector of Slot objects to represent our 5mb chunk of memory 
@returns None

DEFINED IN: scenario_3.cpp
*/
void scenario_3_BF(vector<Process> process_queue, vector<Processor> processor_list, vector<Slot> memory);

/*
Method: scenario_4_FF()
Given 50 processes, schedules them in a FIFO manner. Unlike scenario 1, uses an array of slot objects to represent available memory.
These processes are allocated and deallocated to our vector memory using my_alloc() and my_free() before they are scheduled.
In this scenario, we handle memory allocation of a 1mb chunk in a First-Fit memory allocation method. Outputs information about each finished process (mem req, service time, etc.).

@params A process queue of processes to schedule, and a list of processor to schedule these processes onto, a vector of Slot objects to represent our 1mb chunk of memory 
@returns None

DEFINED IN: scenario_4.cpp
*/
void scenario_4_FF(vector<Process> process_queue, vector<Processor> processor_list, vector<Slot> memory);

/*
Method: scenario_4_BF()
Given 50 processes, schedules them in a FIFO manner. Unlike scenario 1, uses an array of slot objects to represent available memory.
These processes are allocated and deallocated to our vector memory using my_alloc() and my_free() before they are scheduled.
In this scenario, we handle memory allocation of a 1mb chunk in a Best-Fit memory allocation method. Outputs information about each finished process (mem req, service time, etc.).

@params A process queue of processes to schedule, and a list of processor to schedule these processes onto, a vector of Slot objects to represent our 1mb chunk of memory 
@returns None

DEFINED IN: scenario_4.cpp
*/
void scenario_4_BF(vector<Process> process_queue, vector<Processor> processor_list, vector<Slot> memory);

/*
Method: my_alloc_FF
Given a memory chunk, determines if there is a hole of memory available that can fit a desired process. Iterates through the chunk, and if it reaches a slot
that can fit the process, sets the slots to the desired process's id and returns true. If nothing can be found, returns false. First-fit method, meaning
we start scanning the chunk from the top and plop our process into the first hole that fits. 

@params A reference to a vector of Slot objects (memory chunk), a process that we want to allocate memory for
@returns A boolean value if we successful allocated the memory or not

DEFINED IN: functions.cpp
*/
bool my_alloc_FF(vector<Slot>& memory, Process to_alloc);

/*
Method: my_alloc_BF
Given a memory chunk, determines if there is a hole of memory available that can fit a desired process. If a hole that can fit is found, determines the size of that
hole, and once we are done iterating and searching the chunk, we put out process into the hole that is the smallest (but can still hold our process). This is the best-fit method,
meaning we plop our process in the smallest possible hole we can that can still fit it.

@params A reference to a vector of Slot objects (memory chunk), a process that we want to allocate memory for
@returns A boolean value if we successful allocated the memory or not

DEFINED IN: functions.cpp
*/
bool my_alloc_BF(vector<Slot>& memory, Process to_alloc);

/*
Method: my_free()
Given a chunk of memory, resets slots that have a certain process on them so they no longer hold a process/are "freed". Iterates through a given vector of Slot objects
and if a slot object's id matches the process's id that we want to deallocate, set that slot's held id to 0 and that it does not have a process on it.

@params A reference to a chunk of memory, and a process that we want to deallocate
@returns None

DEFINED IN: functions.cpp
*/
void my_free(vector<Slot>& memory, Process to_dealloc);
