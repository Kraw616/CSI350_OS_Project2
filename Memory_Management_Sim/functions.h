/* Author: Jacob Krawitz (jkrawitz@muhlenberg.edu) 
   Date: 4/29/22
   Description: Header file for all functions uses across .cpp files. Will include header comments.
*/


#include <chrono>
#include <stdlib.h>
#include <iostream>
#include <random>
#include <vector>

#include "processes.h"

using namespace std;

void print_processors(vector<Processor> processor_list, int cycles);

vector<Process> seed_and_create_processes();

vector<Processor> create_processors();

vector<Slot> create_memory();

void test(vector<Slot> memory);

bool has_room(vector<Processor> processor_list);

bool has_processes(vector<Processor> processor_list);

int size_memory(vector<int*> pointers);

int size_memory_mine(vector<Slot> memory);

int free_processor(vector<Processor> processor_list);

void scenario_1(vector<Process> process_queue, vector<Processor> processor_list);

void scenario_2(vector<Process> process_queue, vector<Processor> processor_list, vector<Slot>& memory);

bool my_alloc(vector<Slot>& memory, Process to_alloc);

bool my_free(vector<Slot>& memory, Process to_dealloc);



