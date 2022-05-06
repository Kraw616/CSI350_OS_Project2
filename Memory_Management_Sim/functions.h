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

vector<Process> seed_and_create_processes(int seed);

vector<Processor> create_processors();

vector<Slot> create_memory_12();

vector<Slot> create_memory_3();

vector<Slot> create_memory_4();

void test(vector<Slot> memory);

bool has_room(vector<Processor> processor_list);

bool has_processes(vector<Processor> processor_list);

int size_memory(vector<int*> pointers);

int size_memory_mine(vector<Slot> memory);

int free_processor(vector<Processor> processor_list);

int size_hole(vector<Slot> memory);

vector<Process> create_copy_vector(vector<Process> process_queue);

void scenario_1(vector<Process> process_queue, vector<Processor> processor_list);

void scenario_2_FF(vector<Process> process_queue, vector<Processor> processor_list, vector<Slot> memory);

void scenario_2_BF(vector<Process> process_queue, vector<Processor> processor_list, vector<Slot> memory);

void scenario_3_FF(vector<Process> process_queue, vector<Processor> processor_list, vector<Slot> memory);

void scenario_3_BF(vector<Process> process_queue, vector<Processor> processor_list, vector<Slot> memory);

void scenario_4_FF(vector<Process> process_queue, vector<Processor> processor_list, vector<Slot> memory);

void scenario_4_BF(vector<Process> process_queue, vector<Processor> processor_list, vector<Slot> memory);

bool my_alloc_FF(vector<Slot>& memory, Process to_alloc);

bool my_alloc_BF(vector<Slot>& memory, Process to_alloc);

bool my_free(vector<Slot>& memory, Process to_dealloc);
