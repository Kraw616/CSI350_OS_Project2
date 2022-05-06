/* Author: Jacob Krawitz (jkrawitz@muhlenberg.edu) 
   Date: 4/29/22
   Description: 

    ALGORITHMS:

    1. FIRST-FIT

    2. BEST-FIT
    
    SCENARIOS:
    1. Memory allocation of the 10MB will be handled by your operating system. You will need to use the C++ 
    malloc() and free() calls to dynamically allocate and deallocate memory for your processes. Keep in mind 
    that malloc() allocates memory in terms of bytes, so you will need to make sure you take that into 
    consideration when specifying the number of kilobytes a process requires. Measure the total real time, in 
    nanoseconds, that it takes for your simulation to complete (i.e. from the first process entering the system until 
    the last process completes). 
 
    2. Implement either First-fit or Next-fit AND either Best-fit or Worst-fit. Your implementations will need to provide 
    my_alloc() and my_free() functions that allocate and deallocate memory from the contiguous 10MB. Your 
    implementation will thus need to keep track of allocated memory and holes to allocate memory appropriately 
    and efficiently to the processes. Measure the total real time, in nanoseconds, that it takes for your simulation to 
    complete (i.e. from the first process entering the system until the last process completes). 
    
    3. Using the same memory management implementations from scenario 2, and the same processes from scenarios 
    1 and 2, assume that your system only has 5MB of total memory. If a process arrives but cannot be loaded into 
    memory it should be placed in a separate queue to wait until memory becomes available. Further, if a process 
    requires more memory than the total system memory then it is rejected and you should make a note of this. 
    Measure the total real time, in nanoseconds, that it takes for your simulation to complete (i.e. from the first 
    process entering the system until the last process completes). 
    
    4.  Repeated scenario 3, but now assume that your system only has 1MB of total memory. Measure the total real 
    time, in nanoseconds, that it takes for your simulation to complete (i.e. from the first process entering the 
    system until the last process completes).  
*/

// INCLUDE STATEMENTS
#include "functions.h"
#include <chrono>
#include <ctime>

using namespace std;

// MAIN METHOD
int main()
{

     // Value to seed random generator
    int seed_value;

    // Prompt user for seed value to seed generator of memory requiremnents
    cout << "Seed value?: " << endl;
    cin >> seed_value;

    // Create our simulated memory chunk for scenario 2
    vector<Slot> memory_10mb = create_memory_12();
    
    
    // Seed and create processors
    vector<Process> process_queue = seed_and_create_processes(seed_value);
    vector<Processor> processor_list = create_processors();

    
    vector<Process> process_queue_1 = process_queue;
    vector<Slot> memory_1 = memory_10mb;

    // Record times before and after scenario 1 and take the difference, and convert seconds to nanoseconds
    chrono::high_resolution_clock::time_point t_start_1 = chrono::high_resolution_clock::now();
    scenario_1(process_queue_1, processor_list);
    chrono::high_resolution_clock::time_point t_end_1 = chrono::high_resolution_clock::now();

    chrono::duration<double> time_elapsed_1 = chrono::duration_cast<chrono::duration<double> >(t_end_1-t_start_1);

    cout << "It took " << (time_elapsed_1.count() * 1000000000) << " nanoseconds to complete scenario 1." << endl;

    cout << endl;
    
    vector<Process> process_queue_2_FF = create_copy_vector(process_queue);
    vector<Slot> memory_2_FF = memory_10mb;

    // Record times before and after scenario 2 and take the difference, and convert seconds to nanoseconds
    chrono::high_resolution_clock::time_point t_start_2_FF = chrono::high_resolution_clock::now();
    // reseed to same number at beginning of scenario
    scenario_2_FF(process_queue_2_FF, processor_list, memory_2_FF);
    chrono::high_resolution_clock::time_point t_end_2_FF = chrono::high_resolution_clock::now();

    chrono::duration<double> time_elapsed_2_FF = chrono::duration_cast<chrono::duration<double> >(t_end_2_FF-t_start_2_FF);

    cout << "It took " << (time_elapsed_2_FF.count() * 1000000000) << " nanoseconds to complete scenario 2 FF." << endl;

    cout << endl;

    vector<Process> process_queue_2_BF = create_copy_vector(process_queue);
    vector<Slot> memory_2_BF = memory_10mb;

    // Record times before and after scenario 2 and take the difference, and convert seconds to nanoseconds
    chrono::high_resolution_clock::time_point t_start_2_BF = chrono::high_resolution_clock::now();
    // reseed to same number at beginning of scenario
    scenario_2_FF(process_queue_2_BF, processor_list, memory_2_FF);
    chrono::high_resolution_clock::time_point t_end_2_BF = chrono::high_resolution_clock::now();

    chrono::duration<double> time_elapsed_2_BF = chrono::duration_cast<chrono::duration<double> >(t_end_2_BF-t_start_2_BF);

    cout << "It took " << (time_elapsed_2_BF.count() * 1000000000) << " nanoseconds to complete scenario 2 BF." << endl;
    
    
    
    
    // Create our simulated memory chunk for scenario 3
    vector<Slot> memory_5mb = create_memory_3();
   
    vector<Process> process_queue_3_FF = process_queue;
    vector<Slot> memory_3_FF = memory_5mb;

    // Record times before and after scenario 1 and take the difference, and convert seconds to nanoseconds
    chrono::high_resolution_clock::time_point t_start_3_FF = chrono::high_resolution_clock::now();
    scenario_3_FF(process_queue_3_FF, processor_list, memory_3_FF);
    chrono::high_resolution_clock::time_point t_end_3_FF = chrono::high_resolution_clock::now();

    chrono::duration<double> time_elapsed_3_FF = chrono::duration_cast<chrono::duration<double> >(t_end_3_FF-t_start_3_FF);

    cout << "It took " << (time_elapsed_3_FF.count() * 1000000000) << " nanoseconds to complete scenario 3 FF." << endl;

    cout << endl;
    
   
    
    vector<Process> process_queue_3_BF = process_queue;
    vector<Slot> memory_3_BF = memory_5mb;

    // Record times before and after scenario 1 and take the difference, and convert seconds to nanoseconds
    chrono::high_resolution_clock::time_point t_start_3_BF = chrono::high_resolution_clock::now();
    scenario_3_BF(process_queue_3_BF, processor_list, memory_3_BF);
    chrono::high_resolution_clock::time_point t_end_3_BF = chrono::high_resolution_clock::now();

    chrono::duration<double> time_elapsed_3_BF = chrono::duration_cast<chrono::duration<double> >(t_end_3_BF-t_start_3_BF);

    cout << "It took " << (time_elapsed_3_BF.count() * 1000000000) << " nanoseconds to complete scenario 3 BF." << endl;

    cout << endl;
    

    vector<Slot> memory_1mb = create_memory_4();

    
    vector<Process> process_queue_4_FF = process_queue;
    vector<Slot> memory_4_FF = memory_1mb;

    // Record times before and after scenario 1 and take the difference, and convert seconds to nanoseconds
    chrono::high_resolution_clock::time_point t_start_4_FF = chrono::high_resolution_clock::now();
    scenario_4_FF(process_queue_4_FF, processor_list, memory_4_FF);
    chrono::high_resolution_clock::time_point t_end_4_FF = chrono::high_resolution_clock::now();

    chrono::duration<double> time_elapsed_4_FF = chrono::duration_cast<chrono::duration<double> >(t_end_4_FF-t_start_4_FF);

    cout << "It took " << (time_elapsed_4_FF.count() * 1000000000) << " nanoseconds to complete scenario 4 FF." << endl;

    cout << endl;
    

   
   
    vector<Process> process_queue_4_BF = process_queue;
    vector<Slot> memory_4_BF = memory_1mb;

    // Record times before and after scenario 1 and take the difference, and convert seconds to nanoseconds
    chrono::high_resolution_clock::time_point t_start_4_BF = chrono::high_resolution_clock::now();
    scenario_4_BF(process_queue_4_BF, processor_list, memory_4_BF);
    chrono::high_resolution_clock::time_point t_end_4_BF = chrono::high_resolution_clock::now();

    chrono::duration<double> time_elapsed_4_BF = chrono::duration_cast<chrono::duration<double> >(t_end_4_BF-t_start_4_BF);

    cout << "It took " << (time_elapsed_4_BF.count() * 1000000000) << " nanoseconds to complete scenario 4 BF." << endl;

    cout << endl;

    // Signal to user that the main method is done.
    cout << "END OF MAIN" << endl;

    /*// Testing
    
    //vector<Slot> memory = create_memory_4();
    vector<Slot> memory(11);

    for(int i=0; i<memory.size(); i++)
    {
        memory[i].has_process = false;
        memory[i].current_process_id = -1;
    }

    test(memory);*/
}
