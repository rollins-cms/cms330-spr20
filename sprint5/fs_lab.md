# Exploring Linux File Systems

## Getting started
In this lab, you will explore the Linux file system and some key features of file systems that you've learned about.

Begin by creating two files which you'll use as input in subsequent steps:
1. Create a file named `foo.txt` using Mimir's built-in editor.  Put something simple in this file like just the line "hello".
2. Create a file full of numbers:
```
prompt$ for x in $(seq 1 1 20000); do echo $x >> data.txt; done
```
This is a simple bash script which outputs the numbers from 1 to 20000 by 1's.  We then redirect this sequence of numbers into a file named `data.txt`.  You can take a look at the contents of file with `more data.txt`.  Use `[space]` to scroll through pages and `q` to exit `more`.

Next, we'll need to install a package with special utilities we'll use in this lab:
```
prompt$ sudo apt-get install strace
```
Note that since Mimir spins up a new virtual machine each time you start the IDE, you'll need to execute this command again if you don't finish the lab in one sitting.

## `strace` and File Descriptors
The next command we'll learn about is `strace`.  This utility shows the sequence system calls (syscalls) executed when a program/command is run and lets us explore the very thin layer between user processes and system calls.  If you need to, review the idea of system calls from all the way back at the beginning of the semester.  Remember that use processes are not allowed to make system calls willy nilly.  They have to ask the OS for permission and the OS supplies the code for the requested calls.  `strace` shows us exactly what system calls are occuring.  

Enter the following command:
```
prompt$ strace cat foo.txt > /dev/null
```
This command will show us the syscalls used when we run the command `cat foo.txt > /dev/null`

Remember that `cat` simply reads a file and displays its contents in a terminal window.  `/dev/null` is like a blackhole: data goes in, never to be seen again.  More technically, `/dev/null` is a special file which discards info written to it.  So by redirecting the output of the `cat` command to `/dev/null`, the contents of the file `foo.txt` won't be mixed in with the output of our `strace` command.

There will be a lot of output.  Turns out that even (seemingly) simple commands have a number of syscalls contained in them.  In particular, look at the lines beginning with open, openat, read, write, and close.  

Remember that there are streams for standard input (STDIN), standard output (STDOUT) and standard error (STDERR) which are available.  However, you can manipulate these streams by closing them (as you did with STDOUT in the shell project) or opening new files which will be assigned their own unique file descriptor.  With this in mind, notice how a file descriptor is assigned to `foo.txt` when a `openat` syscall occurs.  You can see the file descriptor at the end of the line after the `=` symbol.

**File descriptors** are an abstract "handle" that allows us to access a file in some way.  Think of a file descriptor as a pointer to a file.  The file descriptor can be used as input to some syscalls or can be the result of a syscall.  The numbers you see in the `strace` output are file descriptors for various input and output streams.  

**Question 1:** What file descriptor did the system assign when it opened `foo.txt`?
   
 At the end of the output, notice how all the input and output streams are closed.  
 
 **Question 2:** Find (and copy) the syscall which reads from `foo.txt` and the syscall which follows it to write the contents of the file to `/dev/null`.


## `lseek`

Copy/paste the following program into a file named `lseek_demo.c`.

```
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>

int main(int argc, char *argv[]) {
    char buffer[10];
    int i;
    int iterations = 4;
    
    int fd = open("data.txt", O_RDONLY);
    assert(fd >= 0);

    for(i = 0; i < iterations; i++) {
        //vary last parameter between SEEK_SET, SEEK_CUR, and 
        //SEEK_END to see different behaviors
        int rc = lseek(fd, 10, SEEK_SET);
        printf("offset %d\n", rc);
    
        //read 10 bytes & display them
        read(fd, buffer, sizeof(buffer));
        printf("contents: %s\n", buffer);
    }
    
    return 0;
}
```

`lseek` is a function which can be used to move through files manually, and this program demonstrates its use.

The OS maintains an **offset** for each open file.  Reading or writing to a file changes the offset value by the amount read or written.  A read or write starts from the current offset in the file.  We can explicitly maneuver through a file by specifying an offset to start from, and we can use `lseek` to do this.  Remember that a file can be thought of as a linear array of bytes; the offset can be thought of as an index into this (conceptual) array of bytes.

`lseek` takes three parameters: 
1. the first is a file descriptor
2. the second is the size (in bytes) to move forward/back
3. the last is the offset/starting location
  a. if this is set to the constant `SEEK_SET`, the offset begins at the start of the file
  b. if set to the constant `SEEK_CUR`, the offset begins at the current offset
  c. if set to the constant `SEEK_END`, the offset begins at the end of the file.
  
The `lseek_demo.c` program manually advances the offset by 10 bytes and then reads 10 bytes and prints them to standard output.  Remember that the read operation will also advance the offset by another 10 bytes.  Currently the program does this 4 times, but you can vary that if you want to.

Compile the program and run it.  Then change the last parameter of the `lseek` function call to the other two values, recompile, and rerun.  

**Question 3: ** Explain the output from each of the three runs, combining your knowledge of `lseek`, the program output, and your knowledge of buffer overflows in C.

**Question 4:** Why do you think SEEK_END would be useful?

## Buffered Output
The OS often buffers data from writes before committing them to disk.  (This is in addition to any buffering that may happen on disk due to the hardware of the disk.)  The function `fsync` lets applications force the OS to write any data associated with a file descriptor immediately.

Run the command
```
prompt$ strace cat data.txt >> /dev/null
```
Since `data.txt` is a large(ish) file containing one integer value per line, the trace will now show two reads to get all the file data.  The output is buffered so we see the buffer totally full (and written to standard out) once and then partially full next time.  When the end of the file is encountered, the syscall terminates and writes the not-quite-full buffer.


**Question 5:** How big (in bytes of kilobytes) is the buffer on this version of Linux and hardware?
**Question 6:** Remember, that you can also see the number of bytes in a file using the long listing command: `ls -l data.txt`.  Are all of these bytes read/written when you run the `strace` command?  How do you know?

## Tracing Linux Commands
Back in the day (lo, those many ages ago), you learned some basic Linux commands like `cp`, `mv` and `rm`.  If you don't remember what these commands do, don't tell me.  Pretend you remember what I've taught you while you quietly Google.  I'll wait.  You remember now?  Excellent.  On we go.

Issue the command:
```
prompt$ strace cp foo.txt bar.txt
```
Observe the series of read and write syscalls and file descriptors used to create a copy of `foo.txt` called `bar.txt`.

**Question 7:** In your own words, describe how `cp` works at the file system level.


Now try the command:
```
prompt$ strace mv bar.txt file.txt
```

**Question 8:** What syscall does this command use to accomplish the `mv` functionality?


What happens with `rm`?  Let's find out.  But first, tracing how to remove files generates a ton of output which is hard to sort through in the terminal.  So, let's redirect the output to a file which is much easier to comb through.  It turns out that `strace` dumps its output to STDERR.  So let's redirect STDERR (not STDOUT!) to a file and then we can sort through the data at our leisure (and not using the terminal).

Now the command:
```
prompt$ strace -f rm file.txt 2> output.txt
```

Notice that we have the direct symbol `>`, but right before it we have a `2`.  Remember that STDERR is opened (by default) with file descriptor 2!  So we're redirecting the output associated with file descriptor 2 into a file!  Cool!  

Now open `output.txt` and take a look at it.  This one is a bit cryptic.  Start by looking at the first line of the output and you should see something like:

```
execve("/usr/bin/rm", ["rm", "file.txt"]
```

Wait a second!  We know what `execvp` does that this `execve` looks pretty close to that.  It's almost like the professor of this course might be showing you that the stuff you learned in the past has an uncomfortable way of coming up again.

Also, notice the `-f` option we passed to `strace`.  That's new...  What does that do?  The `-f` option allows `strace` to follow any child processes created and report syscalls that they make as well.  Since `execve` creates a child process, this argument is important if we want to know the syscalls `rm` actually uses.

Now look for a syscall which begins `unlink`.  Notice that this system call was called by a child process.  So what is unlink?  Remember this idea; more on it in a minute.

## Counting System Calls
Another nifty feature of `strace` -- it can tell you the total number of system calls required to complete 1 high level command.  Try this
   * Create a new (empty) file:
      `touch newfile.txt`
   * Use the `-c` argument to summarize and display system call information from `strace`
      `strace -c rm newfile.txt`
      
**Question 9:** How many system calls did `strace` report to remove 1 (empty!) file?

## `stat`
As you've been looking at traces you may have noticed a number of lines beginning `stat` or `fstat`.  These are commands which get file metadata.  The metadata includes things like name, size, inode number, links (what are links anyways?), access time, permissions, and more.

Run the command:
```
prompt$ stat data.txt
```
to get an idea of the metadata for your large numbers file.  it should look something like:

```
prompt$> stat data.txt
  File: data.txt
  Size: 108894      Blocks: 216        IO Block: 4096   regular file
Device: 10300h/66304d   Inode: 11274321    Links: 1
Access: (0644/-rw-r--r--)  Uid: (    0/    root)   Gid: (    0/    root)
Access: 2020-04-05 19:50:13.204000000 +0000
Modify: 2020-04-05 19:50:13.416000000 +0000
Change: 2020-04-05 19:50:31.956000000 +0000
 Birth: -
```

You can also call the functions `stat` or `fstat` in a C program to get metadata which you can use programatically.  Metadata is maintained in an on-disk structure called the **inode** (short for index node).  The low-level **inode number** is used to associate it with one particular inode structure.  `stat` shows the inode number in the metadata.

**Question 10:** What is the inode associated with your data.txt file?

## Links
The command `ln` creates a link between two files.
```
prompt$ ln data.txt data2.txt
```
`ln` takes two high-level (human readable) names and associates them with the same inode number.  These links are also referred to as **hard links**.

Issue the command:
```
stat data.txt
```
Note that `stat` now says that there are two links.  Moreover, if you run
```
prompt$ stat data.txt data2.txt
```
you will notice that the same inode number is reported for both files (and the metadata is identical).

Q: So what do links do?  
A: It tracks the number of high-level names associated with the inode reference count

Now try:
```
prompt$ rm data2.txt
prompt$ stat data.txt
```
Notice that links=1.  So removing a linked file didn't actually get rid of it.  Instead, it just got rid of one of the high level (human readable) names (`data2.txt`) that referred to a specific inode.  But since the other filename (`data.txt`) is still linked, the inode (and the file) still exist.

Remember that we know from `strace` that the command `rm` used a system call to unlink a file.  

Question: So what does unlink actually do?

It may seem that `ln` and `cp` provide the same functionality.  This is a trap; they don't.  Use `cp` to create independent copies, not `ln`.  (If we wanted to, we could have done an activity to see that modifying `data.txt` also modified `data2.txt` but this lab was too long already.  That experiment is left as an exercise to the reader.  You're welcome.) 

Try to use `ln` with a directory:
```
prompt$ mkdir dir_one
prompt$ ln dir_one dir_two
```

What happened?  Try to reason about why this wouldn't be allowed.  Turns out, there are a lot of good reasons.  Hard linking directories allows you to create loops, it multiplies files, and it introduces ambiguity particularly in parent/child relationships which are crucial for file system coherency.

As an example of this badness, consider the following commands:
```
mkdir /tmp/one/two
cd /tmp/one/two
ln -d /tmp/one three
```
Now it's possible to try to do something like:
```
cd /tmp/one/two/three/two/three/two/
```

Badness.  Badness everywhere.

## Soft/Symbolic Links
We can also make **symbolic links** (sometimes also called soft links) using a slightly different version of the command:
```
prompt$ 
prompt$ ln -s data.txt data2.txt
prompt$ stat data.txt
prompt$ stat data2.txt
```

**Question 11:** List at least four differences shown in the metadata for `data.txt` and `data2.txt`. 
<!--
Notice the differences:
* the two files have different inode numbers (indicates they are different structures on the disk!)
* the sizes are different (very different!) and thus so are the number of blocks the file takes up
* the `File:` metadata shows the linking: symbolic link or file
-->

It turns out that symbolic links are special links that contain the path to the linked file!  Think of these as a pointer to the original file.

Now take a look at the contents of your directory and then try to remove the file which contains the data:
```
prompt$ ls
prompt$ rm data.txt
```
Take another look at the files in your directory using `ls`.  `data2.txt` still exists! How can this be?  Try to open that file: `more data2.txt`.  What happens?

The "file" `data2.txt` still exists.  The contents of that file was just a path to `data.txt` (which has just been deleted).  `data2.txt` is now unusable, and we refer to it as a *dangling* or *orphan* reference.

## Conclusions
It turns out there's a lot going on inside your operating system.  In this lab, we've gotten to see a lot of details about how the Linux operating system manipulates files and uses a very structured approach to keep track of all the data in your filesysem.  Next up, a look at how the filesystem itself is structured.


