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
    // Create our simulated memory chunk for scenario 2
    vector<Slot> memory = create_memory();

    // Seed and create processors
    vector<Process> process_queue = seed_and_create_processes();
    vector<Processor> processor_list = create_processors();

    // Record times before and after scenario 1 and take the difference, and convert seconds to nanoseconds
    chrono::high_resolution_clock::time_point t_start_1 = chrono::high_resolution_clock::now();
    scenario_1(process_queue, processor_list);
    chrono::high_resolution_clock::time_point t_end_1 = chrono::high_resolution_clock::now();

    chrono::duration<double> time_elapsed_1 = chrono::duration_cast<chrono::duration<double> >(t_end_1-t_start_1);

    cout << "It took " << (time_elapsed_1.count() * 1000000000) << " nanoseconds to complete scenario 1." << endl;

    cout << endl;

    // Record times before and after scenario 2 and take the difference, and convert seconds to nanoseconds
    chrono::high_resolution_clock::time_point t_start_2 = chrono::high_resolution_clock::now();
    scenario_2(process_queue, processor_list, memory);
    chrono::high_resolution_clock::time_point t_end_2 = chrono::high_resolution_clock::now();

    chrono::duration<double> time_elapsed_2 = chrono::duration_cast<chrono::duration<double> >(t_end_2-t_start_2);

    cout << "It took " << (time_elapsed_2.count() * 1000000000) << " nanoseconds to complete scenario 2." << endl;
    
    // Signal to user that the main method is done.
    cout << "END OF MAIN" << endl;
}
