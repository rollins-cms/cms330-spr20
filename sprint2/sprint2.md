# Sprint 2: Virtual Memory (Part 1)

# Roadmap:
* Teams
* Sprint Duration: Feb. 6 - 20
* Quiz date/time: Th. Feb. 20 at the start of class
* Requirements due: 
   * Problem set: Tu. Feb. 18 at the end of class
   * Project 1: Th. Feb. 20 by 11:59pm

# Rationale: 
Sprint 2 introduces us to virtual memory.  Just like we saw in Sprint 1 with the processor, memory is a finite resource that must be shared among many processes.  So how do we make each process think that it has total freedom in its use of memory?  Virtualization! In this sprint, we'll look at two techniques for memory virtualization: 1) base and bounds and 2) segmentation.  In the next sprint, we'll look at some more. 

# Responsibilities (What you need to know):
1. Virtual address space (review)
   * Code
   * Heap
   * Stack
2. Virtual address translation
    A. Policies: address translation (conceptually)
    B. Mechanisms:
       * Base and bounds (a.k.a dynamic relocation)
       * Segmentation (generalized base and bounds)
3. Issues and Problems with different memory policies
   A. framentation
   B. why base and bounds has problems
   C. why segementation has problems
    

# Requirements (What you need to do):
Your deliverable grade for this sprint comes from the problem set (50%) and your individual Project 1 (50%).  Your Scrumage grade is recorded separately and consists of your backlog tracking, teamwork, burndowns, and sprint retrospectives.

## Individual Requirements:
* Understand the responsiblities on the list.
* Complete [Project 1](https://github.com/rollins-cms/cms330-spr20/blob/master/sprint2/project-virt-mem.md) on Mimir.

## Team Requirements:
* track deliverables and estimates using Scrum -- you can use something other than Trello beginning this sprint, but you have to share it with me in some way.  See me to arrange to use something else.
* Complete the problem set: [Document with space for answers](./sprint2_prob_set_space.pdf) or [Document without space](./sprint2_prob_set_no_space.pdf)

# Resources:  
I may add to these as we go through the sprint.  Use the [Expert Request](https://rollins.co1.qualtrics.com/jfe/form/SV_0jNfbBpN1clDJfn?course=cms330s20&sprint=2) for more resources. 
   * OSTEP: Ch 12 (quick read to orient yourself)
   * OSTEP: Ch 13 (mostly conceptual with big goals of memory virtualization)
   * OSTEP: Ch 15 (base and bounds, skim 15.4 and 15.5)
   * OSTEP: Ch 16 (segmentation -- skim 16.4 and 16.6, omit 16.5)
   * [Concise summary](http://pages.cs.wisc.edu/~bart/537/lecturenotes/s15.html) of base-and-bounds and segmentation translation techniques.

# Reality Check:
  * On Thursday, do basic technology setup (Trello or other).  Do sprint planning meeting.  
  * TODO by next class:  Skim problem set, project, and readings.  As your skim, make notes of relevant sections for problems on problem set.
  * Tuesday class: Work on problem set as group.
  * TODO by next class: Get code for project and work on Part 1.  Make expert requests if needed.
  * Thursday: Make sure everyone has started project and discuss Part 1 and how to approach Part II.
  * TODO by Tuesday: Have "almost final" answers for all problems in problem set.  Some may still need group discussion or further clarification.  
  * Tuesday: Do final check of problem set.  Make sure problem set is neat, tidy, and meets guidelines.  Turn in your problem set at the end of class. Finish Part II of project.
  * TODO before next class: Take the practice quiz and check your answers.  Study as a group.  Make sure Lab is written up and ready to go.
  * Next Tuesday: Quiz (30 minutes), Sprint 2 retrospective, and Sprint 3 planning.

# Retrospective:
  * Complete this [sprint retrospective survey](https://rollins.co1.qualtrics.com/jfe/form/SV_3rAIzhpHFYbIixf?course=330s20&sprint=2).  Each team member should complete a survey.
