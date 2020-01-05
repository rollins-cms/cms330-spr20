# Project 0

This project is designed to be very easy and refresh your understanding of how to use git from a command line.  You grade for this project will be determined by the answers in your `README` file as well as your history of commits in Github.

## Setup
* Setup your Mimir account and open the IDE (click the 3-dot menu in the upper right corner and select "Open Mimir IDE")
* At a prompt, make a directory for this semester: `mkdir cms330`
* Change into that directory: `cd cms330`
* Make sure you have your Github ID and password ready to go
* Find the `project0` assignment on Canvas, and click the assignment link.  You may have to give the organization permission to create the repo for you.  Once you do this, you should see a repo with a name of `project0-yourGitHubID`.  

* Click the big green button which says "Clone Repo" and copy the URL.  At a prompt on Mimir, type the command `git clone URL-you-copied`
* This will create a directory named `project0-yourGitHubID` which contains your specific GitHub repo.  You must be in this project directory do work on project 0 and eventually be able to submit your finished project.
* Change into your repo: `cd project0-yourGitHubID` and look at the files by typing the command `ls`.  You should see 8 files.
* *Protip: remember that you can use the tab-complete feature in Linux so that you don't have to type the entire repo name*

## The OSTEP code
The code in the repo includes the example code from OSTEP - Chapter 2.
* a `Makefile`
* `common.h` and `common_threads.h`
* `mem.c`, `io.c`, `cpu.c`, and `threads.c`

There is also a `README.md` file which will be used later on.

Open the `Makefile` and refresh your memory about how a Makefile works.  What executables will be built when you type `make`?  See if you were correct by typing the `make` command at a prompt.  Then type `ls` to list all the files in the current directory.  How can you tell the difference between executables and source code files on Mimir?

### CPU Virtualization
Read OSTEP 2.1.  Open `cpu.c` and examine the code (note the purposeful infinite loop!).  Use the `cpu` program to make the OS run a single copy of the program to make sure everything is working:
```
prompt> ./cpu A
```
The program currently contains an infinite loop so will run forever.  Use `Ctl-c` to kill it.

As described in the chapter, we want to run multiple copies of the program at the same time and observe how the operating system switches between different running programs.  But first, let's make some modifications so the program doesn't run in an infinite loop.
1. Add an `int` variable which makes the `while` loop run only 7 times instead of infinitely.  This variable can count up to 7 or down from 7; just make sure it only runs 7 times.
2. Modify the print statement inside the loop to include the `int` variables value in the form `number - process_name` instead of just `process_name` (which is currently passed via a command line argument.
3. Don't forget to modify the `int` variable each time the loop runs so you don't have an infinite loop.

Test and run your program frequently.  Remember that if you change your source code, you must recompile!  Don't proceed to the next step until you have removed the infinite loop.

4. Now, let's kick it up a notch and run 3 copies of our program (each with a different name) at the same time and watch how the OS changes control:
```
prompt> ./cpu V & ./cpu H & ./cpu S
```
The `&` causes the next program to immediately start running rather than waiting for the previous one to finish.  You should now get a series of output from all 3 programs intermingled.

**Record your observations about the output displayed in the terminal in your `README` file for `Question 1`.**

## Submission
In this class, code will be submitted via Github.  I grade the last thing you submit.  It is your responsibility to make sure that what you intended to submit to Github was, in fact, submitted.  You can always log-in to github.com and view the code in your repo (which is what I grade).  Make sure to complete the honor code and collaboration statements in the `README` file and do a final push to github.  Verify your submission and you're done!

