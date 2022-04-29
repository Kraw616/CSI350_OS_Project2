/* Author: Jacob Krawitz (jkrawitz@muhlenberg.edu) 
   Date: 4/19/22
   Description: Header file that contains the class definitions for the classes Process and Processor. Depending on the
   scenario chosen, the characteristics of the processes and processors change (i.e. different processor speeds).
*/

using namespace std;

// PROCESS CLASS
class Process
{
    public:
        int id; // Process ID
        unsigned long long service_time;    // AKA Burst time; how many cycles is required
        unsigned long long arrival_time;    // After how many cycles does the process arrive (only in scenario 4)
        int memory_req; // How much memory does the process require?
        unsigned long long wait_time = 0;   // How long was the process on the processor without getting work done?
        unsigned long long turnaround_time = 0; // Amount of time spent from process start to execution
        unsigned long long cycles_worked = 0;   // Starts at service_time, and goes down; how many cycles left in the process
};

// PROCESSOR CLASS
class Processor
{
    public:
        int id; // Processor ID
        float speed;    // How fast (GHz) does the processor run?
        int memory_capability;  // How much can the processor hold
        Process current_process;    // Holds the current process on the processor (1 at a time)
        bool has_process =  false;  // Is the processor currently being occupied?
};
