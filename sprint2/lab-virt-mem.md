# Lab - Virtual Memory and Memory Management*
`*`Adapted with permission from Dr. Jared Moore and Dr. Greg Wolff, GVSU

## Overview
The main purpose of this lab is to investigate the cooperative role played by the compiler and the operating system in the organization of a process' logical address space. It is designed to improve your understanding of memory allocation protocols. A secondary purpose is to introduce a tool for detecting a common memory error -- a memory bound violation.

## Activities
Part I of the lab introduces a tool to help you test your program for memory leaks.  This tool is significantly lighter weight than `valgrind` which we worked with in CMS230.  (But of course, it's much less powerful.)

The rest of the lab consists of an open-ended investigation into the memory mapping of the current Mimir system environment (the GNU gcc compiler running under Linux on an Intel processor).

## Getting Started
Accept the Virtual Memory Lab assignment (link available on Canvas).  Clone the repo to your Mimir workspace.  You will submit all your work for this lab through `git`/GitHub, so look back at `project0` if you need a refresher on how to push your work.

You will also need to install the program Electric Fence, a memory management tool.:
```
prompt> sudo apt-get install electric-fence
```

## Part I - Memory Bound Protection
One of the common problems operating systems face is incorrect memory usage by user programs. This problem can be hard to detect -- most often, systems will "allow" a process to make memory errors, provided they do not corrupt memory belonging to the system or to another process. Basically, a high-performance language like C/C++ will not take the time to check every memory access to ensure it is correct; as that would incur a performance hit. Instead, the operating system will intervene only to protect itself and other users from a misbehaving program.

This section introduces a tool for performing dynamic memory debugging, in order to allow a user to validate a program's use of memory while it is executing. It is most often used together with a debugger such as `gdb`.

### Buffer Overruns
The scenario induced in `program.c` illustrates a common memory problem: the buffer overrun. The problem will be examined using a tool called Electric Fence. 

Compile and run the program a few times.  Although the program appears to run correctly (i.e. it does not abort), it includes a potentially dangerous error that can be detected by using Electric Fence.

Study the code carefully. Review the man pages on Electric Fence by typing `man efence`.  You can press `[SPACE]` to scroll through the man pages or type `q` to exit the viewer. Now, perform the following:

* compile and run the program
* when prompted, enter the username `myname`
* re-run, entering the username `notarealusername`
* re-compile the program, this time using the debug option and linking in the Electric Fence library:
```
prompt> gcc -Wall -Werror -o program -g program.c -lefence
```
Note that it's important for the `-lefence` argument to come after everything else for reasons I won't get into here.
* re-run the program.  You should now see some extra information in your program output:
```
prompt> ./program 

  Electric Fence 2.2 Copyright (C) 1987-1999 Bruce Perens <bruce@perens.com>
Please input username: 
```
* when prompted, enter the username `myname`
* re-run, entering the username `notarealusername`

This outcome might not seem like a good thing.  But consider this: the program used to illegally use memory but not fail/crash in all circumstances.  Now we have a program which creates very reproducible results.  This is actually a huge win in the C programming world where seg faults often seem to mysteriously appear and disappear.

Electric Fence is a pretty cool little program which uses some of the features of virtual memory we've been talking about (and will continue to talk about in the next sprint).  It places a barrier (really, an inaccessible memory segment) immediately after a process's allocated memory. This will cause any memory problems in an executing program to suffer a segmentation fault. 

To find the exact location of the problem, you can use a debugger to step through the code to find the offending line.  If you want to refresh your memory on how to use `gdb` here's the [CMS230 lab](https://github.com/vsummet/cms230notes/blob/master/labs/lab-gdb.md) on that very topic!

Examine the code, use `gdb` if necessary, and determine the problem in the code.  

In your README, answer Question 1 at this point.

Fix the problem.  Two hints for you:
* [`getline`](https://c-for-dummies.com/blog/?p=1112) is a function which can dynamically allocate an array that is just the size of the user input
* Remember that proper memory management in C means that you (the programmer!) must `free` any space you allocate


## Part II - Memory Management Overview
The second part of this lab examines memory management from the system point-of-view. Modern operating systems provide the user with a logical view of memory as an extremely large, contiguous address space. This address space is usually partitioned conceptually into segments: functional partitions of logical memory. The operating system, together with the memory management hardware (known as the Memory Management Unit -- MMU), transparently maps the logical pages of a process into physical memory frames.

### Review (and more detail) on Address Space
Programs consist fundamentally of code and data. However, there are several other distinct regions of user mode logical memory:
* program text - this constitutes the machine instructions or program code. It is read-only and of fixed size and initially resides on disk as part of the executable. The size is determined at compile-time and is communicated to the operating system via the header of the executable, so that it can be loaded into the correct amount of memory when run.
* initialized data - this data segment holds persistent objects (i.e. globals) that have been initialized with values. Since the data object is to be initialized with a value, the value must be stored as part of the executable.
* uninitialized data - this segment holds static (global) objects that have been declared but not initialized. The space for these objects is constructed at run-time by the kernel and initialized to 0 or NULL.
* run-time data - this refers to heap space used for dynamic memory allocation. Heap space fluctuates during execution as memory is obtained via `malloc()`, and released via `free()`. Farther away from the programmer, the `brk()` and `sbrk()` system calls facilitate these operations.
* stack - there is a run-time stack associated with each executing process. It contains stack frames for process context and includes all automatic variables (e.g. function parameters and local variables).
* shared C libraries - shared libraries loaded during program execution (i.e. dynamically bound code).

The compiler partitions the logical view of your program into these respective regions as it creates the format of the executable. It also places information regarding the sizes of these regions into the program header of your executable. Note that the dynamic regions (stack, heap, uninitialized data) are not actually created until run-time.

These regions each have their own specific locations in virtual memory. As an example, consider Linux memory management. The simplified logical address space of an executing process typically looks like this:

```
A canonical 32-bit address space

-----------------------------  Byte index 0
|           Code            |
|---------------------------|
|       static data         |
----------------------------- 
|           Heap            |
|  (dynamically-allocated)  |
|                           |
-----------------------------
|             |             |
|             |             | Heap grows and shrinks as data is dynamically allocated
|             v             | and freed by the program (new and garbage collection in
|                           | Java, malloc and free in C).
|     Unallocated space     |         
|                           |
|             ^             | Stack grows and shrinks as the program calls and returns
|             |             | from functions.
|             |             |
-----------------------------
|           Stack           |
|                           |
|   (local variables and    |
|  function call history)   |
|                           |
-----------------------------  Byte index 2^32 - 1
```

The code and data regions are static in size and are created by the operating system at program load time using the information inserted into the program header by the compiler. The dynamic regions are created and managed at run-time in response to function calls, system calls and process resource requests. Memory management hardware and software cooperate to implement the mapping. For example, using a page table, page #2 of the program code might be mapped into frame# 0x400006 of physical memory.

### Memory Mapping Exercise
Perform the following operations:

* create an annotated memory map of GNU/Linux/Intel virtual memory organization
* include all of the segments described above
* determine the direction of growth of the dynamic segments
* specify the approximate location of each of the segments for a sample program you have written

Hints:
* think about, and create, the type of information each segment stores
* it is possible to obtain the logical address of any data object using the "address of" operator (&).
* Note: the "%p" format modifier can be used to print addresses (in hexadecimal)
* creating multiple objects will indicate their direction of growth
* do not compile your program with Electric Fence included; it changes the location of heap variables

Alternative mapping options:
* access system variables that contain pointers to specific memory areas
* memory mapping information is available from the kernel
* pause your process and look in /proc/PID#
* the maps file will provide memory mapping information
* some utilities (e.g. readelf) interpret binary headers (i.e. they parse an executable)
* some utilities (e.g. ldd) give information about libraries and executables
* the pmap command and the valgrind utility can be used to determine process memory usage

Synthesize all of this information to help create your annotated diagram.

In addition, run your sample program multiple times. Notice that the dynamic segments appear to "hop around" or re-locate in memory.
What's going on here, and why? *Hint: google "address obfuscation"*
