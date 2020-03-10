# Sprint 4: Concurrency

# Roadmap:
* Teams
* Sprint Duration: Mar. 5 - Apr. 2 (3 week sprint, not including Spring Break!)
* Quiz date/time: Apr. 2 at the start of class
* Requirements due: Problem set due at the start of class Apr. 2, Project due (push to github) by 11:59pm on Apr. 2

# Rationale: 
Sprint 4 will introduce to another fundamental concept in modern operating systems: concurrency.  Concurrency means a program with multiple threads. Think of this like having minions: you can direct many small minions to run around and do your bidding.  In this sprint, you'll work with a new programming concept (threads) and hopefully get them to do your bidding by the end of the sprint.  You'll have to learn how to protect and synchronize access to resources that threads need to share. We'll also see classic concurrency and synchronization problems like deadlock and race conditions. 

# Responsibilities (What you need to know):
1. What are the similarities and differences between threads and processes? In particular, think about address spaces & the stack(s).
2. What is atomicity and why is it necessary?
3. Locks, different types and implementations
4. Define and understand critical regions, race conditions, and mutual exclusion
5. Write a pseudocode description of the test-and-set instruction. Show how to use test-and-set to write a working implementation of a spin-based lock.
6. Be able to look at code (for example, of a data structure implementation), identify the critical region, and add locks to implement mutual exclusion.
7. What is deadlock and give a pseudocode example.
8. Describe the four conditions that must exist if deadlock is possible.
9. Describe strategies for removing one or more of the precipitating conditions for deadlock.
10. Describe, understand, and know how to solve the Dining Philosophers problem and the Producer-Consumer problem. Be able to describe tradeoffs amongst different correct solutions.
11. Describe and understand semaphores
12. Write pseudocode definitions of the sem_init, sem_wait, and sem_post methods.
13. Know how to use a semaphore to: implement a lock, use wait and post to make one thread stop
and wait until it receives a signal from another thread, synchronize access to a shared buffer
between writer and reader threads (the correct initialization values are important in each case;
pay attention to initialization values for semphores!).

# Requirements (What you need to do):
Your deliverables for this sprint are the problem set (as a group) and the programming project (as individuals).  Your Scrumage grade is determined separately.

## Individual Requirements:
   * Participate in your team.
   * Complete the [programming project](./project.md)

## Team Requirements:
   * Maintain the Trello board and track your deliverables
   * Complete the short [problem set](./sprint4_problem_set.pdf)
   
# Resources:  
I may add to these as we go through the sprint.  Use the [Expert Request](https://rollins.co1.qualtrics.com/jfe/form/SV_0jNfbBpN1clDJfn?course=cms330s20&sprint=4) for more resources. 
   * OSTEP:
      * 26, 28 (only up to 28.8) -- these contain the theoretical background of threads
      * Chapter 27 and 29 (omit 29.1) -- code chapters particularly relevant to the project.  
      * 30.1 and 30.2 -- producer/consumer or bounded buffer problem for problem set question
      * 31.1-31.4, 32 (omit 32.2) -- semaphores and concurrency bugs
   * A 30-40 minute [hands-on lab activity](./lab-concurrency.md) which introduces the basics of how to create and manipulate threads.
   * Dr. Myers's [dramatic work](./dining-philosophers-play.pdf) about deadlock.
   * Videos on Canvas:
      * overview of threads (13 min)
      * working with `pthread` functions in C (14 min)
      * locks (13 min)
      * working with `pthread` mutexes (locks) in C (7 min)
   
# Retrospective:
  * Complete this [sprint retrospective survey](https://rollins.co1.qualtrics.com/jfe/form/SV_3rAIzhpHFYbIixf?course=cms330s20&sprint=4).  Each team member should complete a survey.
