/* Author: Jacob Krawitz (jkrawitz@muhlenberg.edu) 
   Date: 5/06/22
   Description: Defines classes used in simulations. The Process class is used to represent processes, Processors represent processors, and Slots represent 1kb memory
   slots.
*/


// PROCESS CLASS
class Process
{
    public:
        int id; // Process ID
        int service_time = 0;
        int memory_req = 1; // All processes require atleast 1kb of memory
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

// SLOT CLASS
class Slot
{
    public:
        int current_process_id; // What process is taking up this space in memory?
        bool has_process = false;   // Do I have a process on me/am I occupied?
};