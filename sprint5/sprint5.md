# Sprint 5: File Systems and Networking

# Roadmap:
* Teams:
* Sprint Duration: Until Th. 4/23
* Quiz date/time: Th. 4/23 - Fri. 4/24
* Requirements due: Th. 4/23

# Rationale: 
In Sprint 5 we'll cover file systems which demonstrate a fundamental property of operating systems: persistence.  Think about how horrible it would be if data did not persist on our systems!  If data did not persist, we wouldn't be able to save our files and retrieve them when we needed them again.  If fact, we would have to reload our operating system each time we wanted to use our computer.  (In fact, this is exactly what you had to do in the early days of computers.)  We'll do a deep dive into how the operating system organizes all your files on the hardware (solid state drives or hard disk drives).  What happens when you create a directory/folder?  What happens when you move a file from your Desktop to a folder?  By the end of this sprint, you'll have an understanding of the inner workings of file systems.

# Responsibilities (What you need to know):
1. How files and directories are stored
   * inodes
   * paths
   * directory heirarchy
2. Linux file systems
   * file descriptors and file pointers
   * file manipulation functions: `open`, `close`, `lseek`
   * file system utilities: `stat`, `strace`
3. Very Simple File System (VSFS) basics
   * on-disk structures (inodes, data blocks)
   * tracking data blocks and inodes
   * API operations
      * create
      * read
      * write
      * close
   * how are big files handled?
4. Networking (just the basics)
   * packets and packet switching
   * protocols and addresses
   * routers and DNS
   * how WWW works
5. Interprocess communication
   * client-server architecture
   * sockets 

# Requirements (What you need to do):
1.  Work with your team to understand the sprint requirements and maintain your Trello board

## Individual Requirements:
   * Particpate in your team and undertand all the concepts on the responsibilities list. 

## Team Requirements:
   * Maintain a Trello board to track your sprint
   * Complete the [File Systems Lab](./fs_lab.md) and prepare answers to the questions in it. (30 pts)
   * Complete the [Networking Lab](./networking_lab.md) and prepare answers to the questions in it. (30 pts)
   * Complete the [Problem Set](./problem_set.pdf)  (40 pts)
   
# Resources:  
I may add to these as we go through the sprint.  Use the [Expert Request](https://rollins.co1.qualtrics.com/jfe/form/SV_0jNfbBpN1clDJfn?course=cms310s20&sprint=5) for more resources. 
   * OSTEP: Ch 39, 40 (omit 40.7)
   * Videos on Canvas:
     * Overview of file systems (13 min)
     * File descriptors in-depth (12 min)
     * Very Simple File Systems - Part 1 (11 min)
     * VSFS - Part 2 (10 min)
     * VSFS - Part 3 (API calls for read & create)  (16 min)
     * VSFS - Part 4 (API calls for write & close)
     * VSFS - Part 5 (Dealing with large files)
     * Overview of networking
     * Protocols
     * Routers and DNS
     * WWW
     * Sockets and interprocess communication
     


# Retrospective:
  * Complete this [sprint retrospective survey](https://rollins.co1.qualtrics.com/jfe/form/SV_3rAIzhpHFYbIixf?course=330s20&sprint=5).  Each team member should complete a survey.
