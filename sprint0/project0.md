# Project 0

This project is designed to 
* refresh your understanding of how to use `git` from a command line.
* make sure you can use Mimir.
* make sure you can modify, compile, and run basic C programs.
* refresh your understanding of command line arguments.

This project investigates three fundamental topics in operating systems: virtualization of the CPU, virtualization of memory, and concurrency.  It follows along with the reading in OSTEP Chapter 2.  

It is designed to be easy.  Ask for help quickly if you are struggling or something goes wrong.  Your grade for this project will be determined by the answers in your `README` file as well as your history of commits in Github.

## Setup
* Setup your Mimir account and open the IDE (click the 3-dot menu in the upper right corner and select "Open Mimir IDE")
* At a prompt, make a directory for this semester: `mkdir cms330`
* Change into that directory: `cd cms330`
* Make sure you have your Github ID and password ready to go
* Find the `project0` assignment on Canvas, and click the assignment link.  You may have to give the organization permission to create the repo for you.  Once you do this, you should see a repo with a name of `project0-yourGitHubID`.  

* Click the big green button which says "Clone Repo" and copy the URL.  At a prompt on Mimir, type the command `git clone URL-you-copied`
* This will create a directory named `project0-yourGitHubID` which contains your specific GitHub repo.  You must be in this project directory do work on project 0 and eventually be able to submit your finished project.
* Change into your repo: `cd project0-yourGitHubID` and look at the files by typing the command `ls`.  You should see 7 files.
* *Protip: remember that you can use the tab-complete feature in Linux so that you don't have to type the entire repo name*

## The OSTEP code
The code in the repo includes the example code from OSTEP - Chapter 2.
* a `Makefile`
* `common.h` and `common_threads.h`
* `mem.c`, `cpu.c`, and `threads.c`

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

**Checkpoint 1:**
Once you have modified the code and recorded your observations recorded in the readme, push your code to github.  It's good practice to do this frequently to make sure your work is backed up on both Mimir and GitHub.

From your repo directory
```
git add .
git commit -m "checkpoint 1"
git push origin master
```

You will need to enter your github ID and password.  You will then see a confirmation message.  If you look at the repo on github.com, you should see your new commit message next to the changed files (`cpu.c` and `README.md`).

**A review of the git commands:**
1. `git add .` adds all the modified files (in this case `cpu.c` and `README.md` to the "staging area".  This means that they have been changed and you're ready to commit them.
2. `git commit -m "checkpoint 1"` makes a new commit to `git` with the previously staged files.  The `-m` flag allows you to specify the message that will appear with this commit.  In this case a message of "checkpoint 1" was appropriate, but you'll need to choose other appropriate messages in the future.
3. `git push origin master` pushes the commit(s) to the remote repo (on github.com).  This command basically syncs up the files you've committed.

### Memory Virtualization
Now we'll use the OSTEP code to examine memory virtualization.  Read OSTEP 2.2.  Then compile and run `mem.c`.  Again, this program contains an infinite loop, so you will need to use `Ctl-c` to end it.

As we did in the other program, change `mem.c` to remove the infinite loop.  Change this program so that the loop runs **10 times**.  You don't need to add the counter variable to the output this time; it's fine to leave the output as it is.  Compile and test to ensure that your program automatically stops after 10 iterations.

Examine the output of your code and make sure you understand the output.  In particular, take a look at the **pid** (process id) and the address of `p`.

At a prompt, run the following command:
```
setarch $(uname --machine) --addr-no-randomize /bin/bash
```

I recommend you copy-paste this line to avoid typos.  This command will change your prompt and, more important, turn off address space randomization.

Now, lets run 3 copies of this program at the same time.  At the prompt, type:
```
./mem & ./mem & ./mem
```

In your `README` file for Question 2, copy and paste the output which shows that all three programs appear to be using the same address space.

Type `exit` at the prompt to get rid of the weird prompt and back to your usual Mimir prompt.

**Checkpoint 2**
Add, commit, and push your changes to Github.  This should be just the changes to `mem.c` and your `README`.  Again, it's good practice to commit/push your work everytime you finish a logical "chunk".  In this case, we're finished investigating virtual memory (for now), so it's a good time to commit/push.

### Concurrency
Now let's take a brief look at the topic of concurrency.  Read OSTEP 2.3.  We now understand that concurrency is a bit different than just making multiple processes.  In the previous exercises, we just made multiple copies of a program.  In a concurrent program, we break the program's functionality up into discrete pieces and each pieces runs on its own thread.  However, each thread might share common resources within the overall structure of the program.

Open `threads.c`.  The program creates two threads and asks them to each run the function `worker`.  This function just loops and increments a variable as it does so.  When a thread has finished, it ends.  The entire program doesn't print the final value and end until all threads are finished.

This program takes a command line argument.  The integer specified after the program name tells the program how many times each thread should increment the variable.  Begin by running the program with a small number, say 1000:
```
./threads 1000
```

Now run the program with 10000, 100000, 1000000, and 10000000 as arguments.  Copy and paste the output into your `README` for Question 3.  In your own words, explain your results.

**Checkpoint 3***
Commit and push the changes in your `README` file to Github.

## Submission
In this class, code will be submitted via Github.  I grade the last thing you submit.  It is your responsibility to make sure that what you intended to submit to Github was, in fact, submitted.  You can always log-in to github.com and view the code in your repo (which is what I grade).  Make sure to complete the honor code and collaboration statements in the `README` file and do a final push to github.  Verify your submission and you're done!

