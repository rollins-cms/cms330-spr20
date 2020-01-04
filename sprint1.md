# Sprint 1: Vitualizing the CPU

# Roadmap:
* Teams:
* Sprint Duration: Jan. 22 - Feb. 5
* Quiz date/time: Feb. 5 at the beginning of class
* Requirements due: 

# Rationale: 
Sprint 1 will teach you the basics of several fundamental concepts in operating systems.  We have to be able to talk about how applications get running time on the hardware.  The concept of processes and context switching gets us started, but then we have to talk about how the operating system can schedule multiple applications' processes.  How do we prevent a process from hogging running time on the CPU?  How can we ensure that each process will eventually finish?  How can we fairly distribute fininte resources (and how do we even define "fair")?  These are important questions that we explore when we talk about several different scheduling algorithms.  We also need to introduce the concept of privileged code which does special things and we don't want applications to be able to mess with whenever they feel like it.  As an overview, I recommend you read OSTEP Ch. 3 Dialogue which sets the stage for these concepts.

# Responsibilities (What you need to know):
1. 
   * Processes - OSTEP Ch 4
      * Time sharing and space sharing
      * Context switching
      * Review some concepts from 230: address space, stack ptr, instruction ptr, program counter
      * Process API steps
      * Process states
      * Use of data structures by OS to store process info (PCBs)
   * Process API in C - OSTEP Ch 5
      * `fork()`, `wait()`, `exec()`
      * Linux utilities for processes: `kill`, `ps`, `man` pages
   * Limited Direction Execution
      * privileged code
      * system calls (syscalls)
      * user mode vs. kernel mode
      * trapping mechanism - trap, return-from-trap, trap tables
      * cooperative and non-coooperative approaches for context switches
      * interrupts (especially timer interrupts)
   * Scheduling
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
   * Complete the shell project in C.  This project is available via the GitHub classroom assignment link on Canvas.

## Team Requirements:
   * Set up a shared Trello board for Sprint 1.  Add team members and me to it (valeriehsummet).
   * Complete the problem set.
   
# Resources:  
I may add to these as we go through the sprint.  Use the [Expert Request](https://rollins.co1.qualtrics.com/jfe/form/SV_0jNfbBpN1clDJfn) for more resources. 
   * OSTEP: Ch 3 - 8 
   * [https://www.youtube.com/watch?v=exlaEOVRWQM](Video lecture) (~40 min) on FIFO, SJF, SRFT, Round Robin scheduling
   * [https://www.youtube.com/watch?v=_NlmflJQDI4](Video lecture) (~22 min) on MLFQ scheduling
   * Practice quiz
   
# Reality Check:
  * On Wednesday (after previous sprint's quiz), do sprint planning meeting (planning poker?) and setup Trello board with topics, deliverables, and time estimates
  * TODO by next class:  Read OSTEP chapters and skim problem set.  Setup shell project in Mimir using Github.  Read shell project description and note any confusing aspects.
  * Monday class: Discuss readings.  Update Trello board with problematic topics.  Discuss shell project and make sure everyone understands API calls.  Start problem set together if extra time.
  * TODO by next class: Work on shell proect.  Work on problem set focusing on areas you're having trouble with. 
  * Wednesday: Check problem set thus far & make sure everyone understands. Check/Ask professor for help if you're stuck or file expert request for next class period.  Discuss any problems or confusion on shell project.
  * TODO by Monday: Have "almost final" answers for all problems in problem set.  Some may still need group discussion or further clarification, but you should be mostly finished.  Make progress on shell project.
  * Monday: Do final check of problem set.  Make sure problem set is neat, tidy, and meets guidelines.  Turn in your problem set at the end of class.  Discuss shell project blocking points if any.
  * TODO before next class: Take practice quiz if you haven't already and check your answers.  Study as a group.  Finish shell project.
  * Wedneday: Make sure you push shell project to Github for final submission (neatly formatted, commented, etc).  Quiz (30 minutes), Sprint 1 retrospective, and Sprint 2 planning.

# Retrospective:
  * Complete this survey.  Each team member should complete a survey.
