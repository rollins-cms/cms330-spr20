# Sprint 3: Virtual Memory - Part II

# Roadmap:
* Teams
* Sprint Duration: Feb. 20 - Mar. 5
* Quiz date/time: Th. Mar. 5 at the start of class
* Requirements due: 

# Rationale: 
In Sprint 3, we'll continue our dive into how many processes share the physical memory space.  We already looked at base-and-bounds and segmentation and saw several problems with each.  In this sprint, we'll investigate the scheme that most modern systems use: **paging.**  Along with this, we'll investigate how systems use **swapping** to dynamically allocate memory to currently active processes.  However, we'll see that paging has some problems (it's sloooow), so we'll take a look at a nifty way to speed it up: caching in the **translation lookaside buffer (TLB)**.

# Responsibilities (What you need to know):
1. 
   * 
   * 
   *  

# Requirements (What you need to do):
Your deliverables grade for this sprint is just the problem set.  The Scrumage grade is separate.

## Individual Requirements:
   * Participate in your team and help track backlog tasks and rate-of-progress.

## Team Requirements:
   * Complete the problem set.
   
# Resources:  
I may add to these as we go through the sprint.  Use the [Expert Request](https://rollins.co1.qualtrics.com/jfe/form/SV_0jNfbBpN1clDJfn?course=cms310s20&sprint=3) for more resources. 
* [Video with big picture] (https://www.youtube.com/watch?v=c5TD8QyRJcA) of paging (YouTube, 3 min).
* [Video showing a big picture](https://www.youtube.com/watch?v=l7HoguhFVQ4) of address translation via paging (5 minutes, YouTube).  In this example, he uses a 32-bit address space (each address composed of 32 bits) and a 4K page size and shows (conceptually) how to go from a program generated virtual address to a physical address.

   
   
# Reality Check:
  * Thursday class: After the Sprint 2 quiz and retrospective, setup your Trello board, appoint a Scrum master, and try to get a handle on the highest priority tasks for the weekend.
  * TODO by next class: Read and work through textbook readings.  Individually try the paging practice problem and check your answers.
  * Tuesday: Go over the practice paging problem as a group and start working on the problem set.
  * TODO by Thursday: Have "almost final" answers for all problems in problem set.  Some may still need group discussion or further clarification.
  * Thursday: Do final check of problem set.  Make sure problem set is neat, tidy, and meets guidelines.  Turn in your problem set at the end of class.
  * TODO before next class: Take the practice quiz and check your answers.  Study as a group.  
  * Next Tuesday: Quiz (30 minutes), Sprint 3 retrospective, and Sprint 4 planning.

# Retrospective:
  * Complete this [sprint retrospective survey](https://rollins.co1.qualtrics.com/jfe/form/SV_3rAIzhpHFYbIixf?course=330s20&sprint=3).  Each team member should complete a survey.
