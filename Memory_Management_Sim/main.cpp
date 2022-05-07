/* Author: Jacob Krawitz (jkrawitz@muhlenberg.edu) 
   Date: 5/06/22
   Description: The driver file to run the simulator. First, prompts the user for a value to seed the randomly generated processes.
   Then, for each scenario, calls the appropriate method to generate appropriately sized memory arrays, and creates a copy of the process queue (so that it does
   not change scenario from scenario). Each scenario is run, and the time taken for the scenario to run is calculated using the chrono library, and output.

    ALGORITHMS:

    1. FIRST-FIT

    2. BEST-FIT
    
    SCENARIOS:

    1. We let the operating system handle memory allocation, using malloc() and free() calls when we need to load or deallocate a process into the system.

    2. We create our own representation of a contiguous chunk of 10mb of memory. To allocate/deallocate, we define our own versions of malloc() and free() in the methods
    my_alloc() and my_free(). A first-fit and best-fit strategy is implemented.

    3. We create our own representation of a contiguous chunk of 5mb of memory. To allocate/deallocate, we define our own versions of malloc() and free() in the methods
    my_alloc() and my_free(). A first-fit and best-fit strategy is implemented.

    4. We create our own representation of a contiguous chunk of 1mb of memory. To allocate/deallocate, we define our own versions of malloc() and free() in the methods
    my_alloc() and my_free(). A first-fit and best-fit strategy is implemented.
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

    // Seed and create processors and processes
    vector<Process> process_queue = seed_and_create_processes(seed_value);
    vector<Processor> processor_list = create_processors();

    // SCENARIO 1
    
    // Create a copy of the process queue for use in scenario 1
    vector<Process> process_queue_1 = process_queue;

    // Record times before and after scenario 1 and take the difference, and convert seconds to nanoseconds
    chrono::high_resolution_clock::time_point t_start_1 = chrono::high_resolution_clock::now();
    scenario_1(process_queue_1, processor_list);
    chrono::high_resolution_clock::time_point t_end_1 = chrono::high_resolution_clock::now();

    chrono::duration<double> time_elapsed_1 = chrono::duration_cast<chrono::duration<double> >(t_end_1-t_start_1);

    // Output nanoseconds taken for the method to resolve to the user
    cout << "It took " << (time_elapsed_1.count() * 1000000000) << " nanoseconds to complete scenario 1." << endl;
    cout << endl;

    // SCENARIO 2

        // FF

    // Create our simulated memory chunk for scenario 2 (10mb vector of Spot objects, used in both FF and BF)
    vector<Slot> memory_10mb = create_memory_2();

    // Create a copy of the process queue for use in scenario 2 first-fit
    vector<Process> process_queue_2_FF = process_queue;
    // Create a copy of the memory vector for use in scenario 2 first-fit
    vector<Slot> memory_2_FF = memory_10mb;

    // Record times before and after scenario 2 FF and take the difference, and convert seconds to nanoseconds
    chrono::high_resolution_clock::time_point t_start_2_FF = chrono::high_resolution_clock::now();
    // reseed to same number at beginning of scenario
    scenario_2_FF(process_queue_2_FF, processor_list, memory_2_FF);
    chrono::high_resolution_clock::time_point t_end_2_FF = chrono::high_resolution_clock::now();

    chrono::duration<double> time_elapsed_2_FF = chrono::duration_cast<chrono::duration<double> >(t_end_2_FF-t_start_2_FF);

    // Output nanoseconds taken for the method to resolve to the user
    cout << "It took " << (time_elapsed_2_FF.count() * 1000000000) << " nanoseconds to complete scenario 2 FF." << endl;
    cout << endl;

        // BF

    // Create a copy of the process queue for use in scenario 2 best-fit
    vector<Process> process_queue_2_BF = process_queue;
    // Create a copy of the memory vector for use in scenario 2 best-fit (still 10mb)
    vector<Slot> memory_2_BF = memory_10mb;

    // Record times before and after scenario 2 BF and take the difference, and convert seconds to nanoseconds
    chrono::high_resolution_clock::time_point t_start_2_BF = chrono::high_resolution_clock::now();
    // reseed to same number at beginning of scenario
    scenario_2_BF(process_queue_2_BF, processor_list, memory_2_FF);
    chrono::high_resolution_clock::time_point t_end_2_BF = chrono::high_resolution_clock::now();

    chrono::duration<double> time_elapsed_2_BF = chrono::duration_cast<chrono::duration<double> >(t_end_2_BF-t_start_2_BF);

    // Output nanoseconds taken for the method to resolve to the user
    cout << "It took " << (time_elapsed_2_BF.count() * 1000000000) << " nanoseconds to complete scenario 2 BF." << endl;
    cout << endl;
    
    // SCENARIO 3

        // FF
    
    // Create our simulated memory chunk for scenario 3 (5mb vector of Spot objects, FF and BF)
    vector<Slot> memory_5mb = create_memory_3();
   
    // Create a copy of the process queue for use in scenario 3 first-fit
    vector<Process> process_queue_3_FF = process_queue;
    // Create a copy of the memory array for use in scenario 3 first-fit
    vector<Slot> memory_3_FF = memory_5mb;

    // Record times before and after scenario 3 FF and take the difference, and convert seconds to nanoseconds
    chrono::high_resolution_clock::time_point t_start_3_FF = chrono::high_resolution_clock::now();
    scenario_3_FF(process_queue_3_FF, processor_list, memory_3_FF);
    chrono::high_resolution_clock::time_point t_end_3_FF = chrono::high_resolution_clock::now();

    chrono::duration<double> time_elapsed_3_FF = chrono::duration_cast<chrono::duration<double> >(t_end_3_FF-t_start_3_FF);

    // Output nanoseconds taken for the method to resolve to the user
    cout << "It took " << (time_elapsed_3_FF.count() * 1000000000) << " nanoseconds to complete scenario 3 FF." << endl;
    cout << endl;

        // BF

    // Create a copy of the process queue for use in scenario 3 best-fit
    vector<Process> process_queue_3_BF = process_queue;
    // Create a copy of the memory array for use in scenario 3 best-fit
    vector<Slot> memory_3_BF = memory_5mb;

    // Record times before and after scenario 3 BF and take the difference, and convert seconds to nanoseconds
    chrono::high_resolution_clock::time_point t_start_3_BF = chrono::high_resolution_clock::now();
    scenario_3_BF(process_queue_3_BF, processor_list, memory_3_BF);
    chrono::high_resolution_clock::time_point t_end_3_BF = chrono::high_resolution_clock::now();

    chrono::duration<double> time_elapsed_3_BF = chrono::duration_cast<chrono::duration<double> >(t_end_3_BF-t_start_3_BF);

    // Output nanoseconds taken for the method to resolve to the user
    cout << "It took " << (time_elapsed_3_BF.count() * 1000000000) << " nanoseconds to complete scenario 3 BF." << endl;
    cout << endl;
    
    // SCENARIO 4

        // FF

    // Create our simulated memory chunk for scenario 4 (1mb vector of Spot objects, used in both FF and BF)
    vector<Slot> memory_1mb = create_memory_4();

    // Create a copy of the process queue for use in scenario 4 FF
    vector<Process> process_queue_4_FF = process_queue;
    // Create a copy of the memory array for use in scenario 4 FF
    vector<Slot> memory_4_FF = memory_1mb;

    // Record times before and after scenario 4 FF and take the difference, and convert seconds to nanoseconds
    chrono::high_resolution_clock::time_point t_start_4_FF = chrono::high_resolution_clock::now();
    scenario_4_FF(process_queue_4_FF, processor_list, memory_4_FF);
    chrono::high_resolution_clock::time_point t_end_4_FF = chrono::high_resolution_clock::now();

    chrono::duration<double> time_elapsed_4_FF = chrono::duration_cast<chrono::duration<double> >(t_end_4_FF-t_start_4_FF);
        
    // Output nanoseconds taken for the method to resolve to the user
    cout << "It took " << (time_elapsed_4_FF.count() * 1000000000) << " nanoseconds to complete scenario 4 FF." << endl;
    cout << endl;

        //BF

    // Create a copy of the process queue for use in scenario 4 BF
    vector<Process> process_queue_4_BF = process_queue;
    // Create a copy of the memory array for use in scenario 4 BF
    vector<Slot> memory_4_BF = memory_1mb;

    // Record times before and after scenario 1 and take the difference, and convert seconds to nanoseconds
    chrono::high_resolution_clock::time_point t_start_4_BF = chrono::high_resolution_clock::now();
    scenario_4_BF(process_queue_4_BF, processor_list, memory_4_BF);
    chrono::high_resolution_clock::time_point t_end_4_BF = chrono::high_resolution_clock::now();

    chrono::duration<double> time_elapsed_4_BF = chrono::duration_cast<chrono::duration<double> >(t_end_4_BF-t_start_4_BF);

    // Output nanoseconds taken for the method to resolve to the user
    cout << "It took " << (time_elapsed_4_BF.count() * 1000000000) << " nanoseconds to complete scenario 4 BF." << endl;
    cout << endl;

    // Signal to user that the main method is done.
    cout << "END OF MAIN" << endl;
}
