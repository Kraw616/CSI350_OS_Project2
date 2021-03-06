# CSI350_OS_Project2
Welcome to Operating Systems Project 2: Memory Management!  
Author: Jacob Krawitz  
Professor: Dr. Helsing  
Muhlenberg College, 2022  

## Execution Instructions
1. Download the source code
2. Navigate to the directory where the files are locating using `cd ...` prompts.
3. Compile the .cpp files in your favorite C++ compiler, for example, in Terminal/a command prompt:                                                     `g++ main.cpp setup.cpp scenario_1.cpp scenario_2.cpp scenario_3.cpp scenario_4.cpp functions.cpp` (order does not matter) in the directory containing all the source files. Make sure that all 9 files are present (including the 2 headers!!), but **do not compile the .h files!** You will get a bunch of warnings, which is normal; pay no mind to them (as long as they aren't errors)!
4. In the same terminal/command window, type `./a.out` or just run the executable/object file.
5. If you have trouble compiling/running the program (like I did on Mac), I would recommend using an online C++ compiler such as [this](https://www.onlinegdb.com/online_c++_compiler). Just make sure to create 7 files on there and copy and paste from the originals.
6. Rejoice!
7. **Note**: If you run multiple times, you may get a malloc error. Please recompile and run it again if this occurs.
8. **Another note** - it seems like there is a bug in the program that causes the same processes to show up multiple times in the finished queue, but unfortunately I did not have time to fix it. Note that process order comparisons are emitted due to this error.
