/* Author: Jacob Krawitz (jkrawitz@muhlenberg.edu) 
   Date: 4/29/22
   Description: Defines classes used in simulations. 
*/


// PROCESS CLASS
class Process
{
    public:
        int id; // Process ID
        int service_time = 0;
        int memory_req = 1;
        int cycles_worked = 0;
};

// PROCESSOR CLASS
class Processor
{
    public:
        int id; // Processor ID
        float speed;    // How fast (GHz) does the processor run?
        Process current_process;    // Holds the current process on the processor (1 at a time)
        bool has_process = false;  // Is the processor currently being occupied?
};

class Slot
{
    public:
        int current_process_id;
        bool has_process = false;
};