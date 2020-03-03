This project is a short introduction to multit-hreaded programing and the `pthread` library. 

This project will use several data structures including arrays and linked lists.

As always, remember:
* to comment your code
* use `-pthread` or `-lpthread` when compiling
* complete your README before submission
* Include a `Makefile` which builds all your code from source

## Getting Started
Accept the GitHub assignment via the link on Canvas for the "Sprint 4 project" assignment.  Clone your repo to Mimir.  You may find it easier to complete the short lab activity (should take 30-45 minutes) to gain an overview of using the `pthread` library and what each function call does before you begin this project.

## Problem 1
The first problem creates multiple threads and has them increment elements of a shared global array in a loop. You need to add code to create the threads, declare and initialize a lock, protect the critical region, and make the parent wait until the threads have finished before exiting. Test the program for 2, 10, and 100 threads; your solution should work perfectly in each case.

## Problem 2
The second problem uses a multi-threaded linked list. This program illustrates a useful approach to testing: generate random input and make sure the program handles it correctly. This approach is called *fuzzing* and is frequently used in security testing.

Your program should create a set of threads and set them to run a test function that adds random values to the shared list. After all of the values have been added, the test program checks to make sure that each one is actually in the list. Every insertion will succeed if the list's critical region is protected. As before, test your program for 2, 10, and 100 threads.

`problem2.c` has an extensive set of comments marked `TODO` to help you understand how to approach this problem.  Note that the data structures are defined in `problem2.h`

## Submission
Before you push your final work to GitHub, make sure you have:
* commented each function (yes, even ones you didn't write) and longer sections of code with **meaningful** comments.
* removed extraneous comments (including the TODO comments which you have presumably now completed) and `printf` statements you added for debugging.
* completed the README file
