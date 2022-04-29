/* Author: Jacob Krawitz (jkrawitz@muhlenberg.edu) 
   Date: 4/19/22
   Description: Performs setup before the scheduling simulation. Contains methods to prompt user for their
   choice of algorithm and scenario, and depending on those choices, initializes 4 processors of varying characteristics
   and 50 processes of varying characteristics.
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

// NOTE: Please see functions.h for header/block comments.
int scenario_menu()
{
    int scenario;

    cout << "What scenario would you like?: " << endl;
    cin >> scenario;

    return scenario;
}

int algorithm_menu()
{
    bool not_valid = true;
    string algorithm;
    int algorithm_choice;

    while(not_valid)
    {
        cout << "What scheduling algorithm would you like? (FIFO, SRT): " << endl;
        cin >> algorithm;

        if(algorithm == "FIFO")
        {
            algorithm_choice = 1;
            not_valid = false;
        }
        else if(algorithm == "SRT")
        {
            algorithm_choice = 2;
            not_valid = false;
        }
        else
        {
            not_valid = true;
        }

        return algorithm_choice;
    }
}

vector<Process> seed_and_create_processes(int algorithm, int scenario)
{
    int seed_value;

    vector<Process> process_queue;

    cout << "Seed value?: " << endl;
    cin >> seed_value;


    long long ten_to_sixth = 10000000; // Store large numbers/scientific notation numbers 
    long long ten_to_twelth = 10000000000000;
    long long one = 1;
    long long ten_to_tenth = 100000000000;

    Process process;
    mt19937_64 gen64;

    gen64.seed(seed_value); // Seed generator

    if(algorithm == 1 && scenario != 4) // FIFO Scenario 1-3 = same arrival time of 0
    {
        uniform_int_distribution<> service_time(ten_to_sixth, ten_to_twelth); // 10x10^6 - 10x10^12
        uniform_int_distribution<> arrival_time(one, ten_to_tenth);   // 1 - 10x10^10
        uniform_int_distribution<> memory_requirement(1, 8);    // Initialize randomizers 


        for(int i=0; i<50; i++) // Create 50 processes with corresponding ID numbers, random service times,
        {                           // and memory requirements
            Process current_process;
            current_process.id = i+1;
            current_process.service_time = service_time(gen64);
            current_process.arrival_time = 0;
            current_process.memory_req = memory_requirement(gen64);
            current_process.wait_time = 0;  // Wait time & turnaround time is calculated later, so is initially 0
            current_process.turnaround_time = 0;
            current_process.cycles_worked = current_process.service_time;

            process_queue.push_back(current_process);    // Push process onto the queue
        }
        return process_queue;
    }
    else if(algorithm == 1 && scenario == 4)    // FIFO Scenario 4 = Random arrival times
    {
        uniform_int_distribution<> service_time(ten_to_sixth, ten_to_twelth); // 10x10^6 - 10x10^12
        uniform_int_distribution<> arrival_time(one, ten_to_tenth);   // 1 - 10x10^10
        uniform_int_distribution<> memory_requirement(1, 8);    // Initialize randomizers 


        for(int i=0; i<50; i++) // Create 50 processes with corresponding ID numbers, and random service times, arrival times,
        {                           // and memory requirements
            Process current_process;
            current_process.id = i+1;
            current_process.service_time = service_time(gen64);
            current_process.arrival_time = arrival_time(gen64);
            current_process.memory_req = memory_requirement(gen64);
            current_process.wait_time = 0;  // Wait time & turnaround time is calculated later, so is initially 0
            current_process.turnaround_time = 0;
            current_process.cycles_worked = current_process.service_time;

            process_queue.push_back(current_process);    // Push process onto the queue
        }
        return process_queue;
    }



    else if(algorithm == 2 && scenario != 4) // SRT Scenario 1-3 = Same arrival time of 0
    {
         
        uniform_int_distribution<> service_time(ten_to_sixth, ten_to_twelth); // 10x10^6 - 10x10^12
        uniform_int_distribution<> arrival_time(one, ten_to_tenth);   // 1 - 10x10^10
        uniform_int_distribution<> memory_requirement(1, 8);    // Initialize randomizers 


        for(int i=0; i<50; i++) // Create 50 processes with corresponding ID numbers, and random service times, arrival times,
        {                           // and memory requirements
            Process current_process;
            current_process.id = i+1;
            current_process.service_time = service_time(gen64);
            current_process.arrival_time = 0;
            current_process.memory_req = memory_requirement(gen64);
            current_process.wait_time = 0;  // Wait time & turnaround time is calculated later, so is initially 0
            current_process.turnaround_time = 0;
            current_process.cycles_worked = current_process.service_time;

            process_queue.push_back(current_process);    // Push process onto the queue
        }
        return process_queue;
    }

    else if(algorithm == 2 && scenario == 4) // SRT Scenario 4 = Random arrival time
    {
         
        uniform_int_distribution<> service_time(ten_to_sixth, ten_to_twelth); // 10x10^6 - 10x10^12
        uniform_int_distribution<> arrival_time(one, ten_to_tenth);   // 1 - 10x10^10
        uniform_int_distribution<> memory_requirement(1, 8);    // Initialize randomizers 


        for(int i=0; i<50; i++) // Create 50 processes with corresponding ID numbers, and random service times, arrival times,
        {                           // and memory requirements
            Process current_process;
            current_process.id = i+1;
            current_process.service_time = service_time(gen64);
            current_process.arrival_time = arrival_time(gen64);
            current_process.memory_req = memory_requirement(gen64);
            current_process.wait_time = 0;  // Wait time & turnaround time is calculated later, so is initially 0
            current_process.turnaround_time = 0;
            current_process.cycles_worked = current_process.service_time;

            process_queue.push_back(current_process);    // Push process onto the queue
        }
        return process_queue;
    }
}

vector<Processor> create_processors(int scenario)
{
    if(scenario == 1) // Scenario 1: All processors are identical (8 gb storage, 3GHz speed)
    {
        Processor P1;
        Processor P2;
        Processor P3;
        Processor P4;
        vector<Processor> processor_list;

        P1.memory_capability = 8;
        P1.speed = 3; // GHz (3 billion clocks per second)
        P1.id = 1;

        P2.memory_capability = 8;
        P2.speed = 3; // GHz (3 billion clocks per second)
        P2.id = 2;


        P3.memory_capability = 8;
        P3.speed = 3; // GHz (3 billion clocks per second)
        P3.id = 3;

        P4.memory_capability = 8;
        P4.speed = 3; // GHz (3 billion clocks per second, 1,000,000,000)
        P4.id = 4;

        processor_list.push_back(P1);   // Push onto lisvectort of processors
        processor_list.push_back(P2);
        processor_list.push_back(P3);
        processor_list.push_back(P4);

        return processor_list;
    }

    else if(scenario == 2) // Scenario 1: All processors have identical speeds, but different memory capabilities
    {
        Processor P1;
        Processor P2;
        Processor P3;
        Processor P4;
        vector<Processor> processor_list;

        P1.memory_capability = 2;
        P1.speed = 3; // GHz (3 billion clocks per second)
        P1.id = 1;

        P2.memory_capability = 2;
        P2.speed = 3; // GHz (3 billion clocks per second)
        P2.id = 2;


        P3.memory_capability = 4;
        P3.speed = 3; // GHz (3 billion clocks per second)
        P3.id = 3;

        P4.memory_capability = 8;
        P4.speed = 3; // GHz (3 billion clocks per second, 1,000,000,000)
        P4.id = 4;

        processor_list.push_back(P1);
        processor_list.push_back(P2);
        processor_list.push_back(P3);
        processor_list.push_back(P4);

        return processor_list;
    }

    else if(scenario == 3) // Scenario 3: All processors have identicale memory capabilities, but varying speeds
    {
        Processor P1;
        Processor P2;
        Processor P3;
        Processor P4;
        vector<Processor> processor_list;

        P1.memory_capability = 8;
        P1.speed = 2; // GHz (2 billion clocks per second)
        P1.id = 1;

        P2.memory_capability = 8;
        P2.speed = 2; // GHz (2 billion clocks per second)
        P2.id = 2;


        P3.memory_capability = 8;
        P3.speed = 3; // GHz (3 billion clocks per second)
        P3.id = 3;

        P4.memory_capability = 8;
        P4.speed = 4; // GHz (4 billion clocks per second, 1,000,000,000)
        P4.id = 4;

        processor_list.push_back(P1);
        processor_list.push_back(P2);
        processor_list.push_back(P3);
        processor_list.push_back(P4);

        return processor_list;
    }

    else if(scenario == 4)  // Scenario 4: All processors are identical
    {
        Processor P1;
        Processor P2;
        Processor P3;
        Processor P4;
        vector<Processor> processor_list;

        P1.memory_capability = 8;
        P1.speed = 3; // GHz (3 billion clocks per second)
        P1.id = 1;

        P2.memory_capability = 8;
        P2.speed = 3; // GHz (3 billion clocks per second)
        P2.id = 2;


        P3.memory_capability = 8;
        P3.speed = 3; // GHz (3 billion clocks per second)
        P3.id = 3;

        P4.memory_capability = 8;
        P4.speed = 3; // GHz (3 billion clocks per second, 1,000,000,000)
        P4.id = 4;

        processor_list.push_back(P1);
        processor_list.push_back(P2);
        processor_list.push_back(P3);
        processor_list.push_back(P4);

        return processor_list;
    }
}

bool compare_arrival_times(Process p1, Process p2)
{
    return (p1.arrival_time < p2.arrival_time);
}

bool compare_service_times(Process p1, Process p2)
{
    return (p1.service_time < p2.service_time);
}