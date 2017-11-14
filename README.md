# USF COP 4600 Fall 2017 Operating Systems Group Project
## By Spencer Turkel And Nicolas Hempe
## Building
There is a Makefile provided in ./build; running `make` in the build directory will build the project on Linux. A version of g++ with C++14 support is required.

There is a CMakeLists.txt file in the root directory. CMake (version 3.5+) may be used to generate build systems for any platform with a C++14 compiler.

In either case, a library called cxxopts will be downloaded through git, from the url https://github.com/jarro2783/cxxopts

cxxopts is an MIT licensed project, see its LICENSE file for details. Special thanks to jarro2783
## Project Prompt
### Problem 4. Measuring the Performance of Page Replacement Algorithms

In this project you are to evaluate how applications respond to a variety of page replacement algorithms. For this, you are to write a memory simulator and evaluate memory performance using traces from real or simulated applications.

#### Simulator Requirements

Your job is to build a simulator that reads a memory trace and simulates the action of a virtual memory system with a single level page table. Your simulator should keep track of what pages are loaded into memory. As it processes each memory event from the trace, it should check to see if the corresponding page is loaded. If not, it should choose a page to remove from memory. If the page to be replaced is “dirty” (that is, previous accesses to it included a Write access), it must be saved to disk. Finally, the new page is to be loaded into memory from disk, and the page table is updated. Assume that all pages and page frames are 4 KB (4096 bytes).

Of course, this is just a simulation of the page table, so you do not actually need to read and write data from disk. Just keep track of what pages are loaded. When a simulated disk read or write must occur, simply increment a counter to keep track of disk reads and writes, respectively.

Implement the following page replacement algorithms:

1.  FIFO: first in first out. 

2.  LRU: least recently used. 

3.  LFU: least frequently used. 

4.  MFU: most frequently used. 

5.  OPT: optimal page replacement. 
