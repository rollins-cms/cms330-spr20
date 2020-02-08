# Sprint 1: Vitualizing the CPU

# Roadmap:
* Teams:
* Sprint Duration: Thurs Jan. 23 - Thurs Feb. 6
* Quiz date/time: Feb. 6 at the beginning of class
* Requirements due:
   * problem set: Feb. 4 at end of class (12:15pm)
   * shell project: Feb 6th at 11:59pm

# Rationale: 
Sprint 1 will teach you the basics of several fundamental concepts in operating systems.  We have to be able to talk about how applications get running time on the hardware.  The concept of processes and context switching gets us started, but then we have to talk about how the operating system can schedule multiple applications' processes.  How do we prevent a process from hogging running time on the CPU?  How can we ensure that each process will eventually finish?  How can we fairly distribute fininte resources (and how do we even define "fair")?  These are important questions that we explore when we talk about several different scheduling algorithms.  We also need to introduce the concept of privileged code which does special things and we don't want applications to be able to mess with whenever they feel like it.  As an overview, I recommend you read OSTEP Ch. 3 Dialogue which sets the stage for these concepts.

# Responsibilities (What you need to know):
1. Processes - OSTEP Ch 4
   * Time sharing and space sharing
   * Context switching
   * Review some concepts from 230: address space, stack ptr, instruction ptr, program counter
   * Process API steps
   * Process states
   * Use of data structures by OS to store process info (PCBs)
2. Process API in C - OSTEP Ch 5
   * `fork()`, `wait()`, `exec()`
   * Linux utilities for processes: `kill`, `ps`, `man` pages
3. Limited Direction Execution - OSTEP Ch 6
   * privileged code
   * system calls (syscalls)
   * user mode vs. kernel mode
   * trapping mechanism - trap, return-from-trap, trap tables
   * cooperative and non-coooperative approaches for context switches
   * interrupts (especially timer interrupts)
4. Scheduling - OSTEP Ch 7 & 8
   * Concepts: workload, policies
   * Metrics: turnaround time, fairness, response time
   * Alogrithms: FIFO, SJF, STCF, Round Robin, MLFQ
      * Classifications: preemptive vs. non-preemptive
      * Be able to trace each algorithm
      * Pros/cons & tradeoffs of each algo.

# Requirements (What you need to do):
The "Requirements" grade is the problem set and shell project. The scrum artifacts will be graded in a "Scrumage" grade.

## Individual Requirements:
   * Understand the concepts on the *Responsibilities* list.
   * Complete the [shell project](./shell_project.md) in C.  The project repo is available via the GitHub classroom assignment link on Canvas.

## Team Requirements:
   * Set up a shared Trello board for Sprint 1.  Add team members and me to it (valeriehsummet).
   * Complete the problem set: [with space for answers](./sprint1_prob_set.pdf) or [without space (do your own writeup](./sprint1_prob_set-no_space.pdf).
   
# Resources:  
I may add to these as we go through the sprint.  Use the [Expert Request](https://rollins.co1.qualtrics.com/jfe/form/SV_0jNfbBpN1clDJfn?course=cms330s20&sprint=1) for more resources. 
* OSTEP: Ch 3 - 8 
* [Video lecture](https://www.youtube.com/watch?v=exlaEOVRWQM) (~40 min) on FIFO, SJF, SRFT, Round Robin scheduling
* [Video lecture](https://www.youtube.com/watch?v=_NlmflJQDI4) (~22 min) on MLFQ scheduling
* [Practice quiz](./sprint1_practice_quiz.pdf) and [answers](./sprint1_practice_quiz_ans.pdf)
* Redirection of output to a file (for shell project)
    * [Video](https://www.youtube.com/watch?v=Eyscu3ByNtg) (YouTube, up to about 4:00) explaining file redirection on Linux.  You do not need to support the `>>` (redirect and append) operator.  Just the redirect operator, `>`, is fine.
    * [Written Overview](http://linuxcommand.org/lc3_lts0070.php) of file redirection.  Just read the first section (through the end of the "Standard Output" section).  The rest is interesting and useful, but not required for the shell project.
* [Notes for C from CMS230](https://github.com/vsummet/cms230notes/blob/master/toc-credits.md) (scroll down to section on C)
* [Spring 20 Quiz](./sprint1_quiz_s20.pdf) and [Answer Key](./sprint1_quiz_s20_ans.pdf)
   
# Reality Check:
  * On Thursday (after previous sprint's quiz), do sprint planning meeting (planning poker?) and setup Trello board with topics, deliverables, and time estimates
  * TODO by next class:  Read OSTEP chapters and skim problem set.  Setup shell project in Mimir using Github.  Read shell project description and note any confusing aspects. Perhaps run example code in shell project and try to understand what's happening ( perhaps as you read OSTEP Ch. 5: *Process API*)
  * Tuesday class: Discuss readings.  Update Trello board with problematic topics.  Discuss shell project and make sure everyone understands API calls.  Start problem set together if extra time.
  * TODO by next class: Work on shell proect.  Work on problem set focusing on areas you're having trouble with. 
  * Thursday: Check problem set thus far & make sure everyone understands. Check/Ask professor for help if you're stuck or file expert request for next class period.  Discuss any problems or confusion on shell project.
  * TODO by next class: Have "almost final" answers for all problems in problem set.  Some may still need group discussion or further clarification, but you should be mostly finished.  Make progress on shell project.
  * Tuesday: Do final check of problem set.  Make sure problem set is neat, tidy, and meets guidelines.  Turn in your problem set at the end of class.  Discuss shell project blocking points if any.
  * TODO before next class: Take practice quiz if you haven't already and check your answers.  Study as a group.  Finish shell project.
  * Thursday: Make sure you push shell project to Github for final submission (neatly formatted, commented, etc).  Quiz (30 minutes), Sprint 1 retrospective, and Sprint 2 planning.

# Retrospective:
  * Complete [sprint retrospective survey](https://rollins.co1.qualtrics.com/jfe/form/SV_3rAIzhpHFYbIixf?course=330s20&sprint=1).  Each team member should complete a survey.
