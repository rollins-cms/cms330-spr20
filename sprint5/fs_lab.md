# Exploring Linux File Systems

## Getting started
In this lab, you will explore the Linux file system and some key features of file systems that you've learned about.

Begin by creating two files which you'll use as input in subsequent steps:
1. Create a file named `foo.txt` using Mimir's built-in editor.  Put something simple in this file like just the line "hello".
2. Create a file full of numbers:
```
prompt$ for x in $(seq 1 1 20000); do echo $x >> data.txt; done
```
This is a simple bash script which outputs the numbers from 1 to 20000 by 1's.  We then redirect this sequence of numbers into a file named `data.txt`. 

Next, we'll need to install a package with special utilities we'll use in this lab:
```
prompt$ sudo apt-get install strace
```

## `strace` and File Descriptors
The next command we'll learn about is `strace`.  This utility shows the sequence system calls (syscalls) executed when a program/command is run.  Enter the following command:
```
prompt$ strace cat foo.txt > /dev/null
```
This command will show us the syscalls used when we run the command `cat foo.txt > /dev/null`

Remember that `cat` simply reads a file and displays its contents in a terminal window.  `/dev/null` is like a blackhole: data goes in, never to be seen again.  More technically, `/dev/null` is a special file which discards info written to it.  So by redirecting the output of the `cat` command to `/dev/null`, the contents of the file `foo.txt` won't be mixed in with the output of our `strace` command.

There will be a lot of output.  Turns out that even (seemingly) simple commands have a number of syscalls contained in them.  In particular, look at the lines beginning with open, read, write, and close.  

   Remember (from your shell project) that there are streams for standard input (STDIO), standard output (STDOUT) and standard error (STDERR) which are available.  However, you can manipulate these streams by closing them (as you did with STDOUT in the shell project) or opening new files which will be assigned their own unique file descriptor.  With this in mind, notice how a file descriptor is assigned to `foo.txt` when a `read` syscall occurs.  You can see the file descriptor at the end of the line after the = symbol.  
   
   At the end of the output, notice how all the input and output streams are closed.  See if you can find the syscall which reads from `foo.txt` and the syscall which follows it to write the contents of the file to `/dev/null`.

**File descriptors** are an abstract "handle" that allows us to access a file in some way.  Think of a file descriptor as a pointer to a file.  The file descriptor can be used as input to some syscalls or can be the result of a syscall.  The numbers you see in the `strace` output are file descriptors for various input and output streams.  

## `lseek`
Now open the file `lseek_demo.c`.  `lseek` is a function which can be used to move through files manually, and this program demonstrates its use.

The OS maintains an **offset** for each open file.  Reading or writing to a file changes the offset value by the amount read or written.  A read or write starts from the current offset in the file.  We can explicitly maneuver through a file by specifying an offset to start from, and we can use `lseek` to do this.

`lseek` takes three parameters: 
1. the first is a file descriptor
2. the second is the size (in bytes) to move forward/back
3. the last is the offset/starting location
  a. if this is set to the constant `SEEK_SET`, the offset begins at the start of the file
  b. if set to the constant `SEEK_CUR`, the offset begins at the current offset
  c. if set to the constant `SEEK_END`, the offset begins at the end of the file.
  
The `lseek_demo.c` program manually advances the offset by 10 bytes and then reads 10 bytes and prints them to standard output.  Remember that the read operation  will also advance the offset by another 10 bytes.  Currently the program does this 4 times, but you can vary that if you want to.

Compile the program and run it.  Then change the last parameter of the `lseek` function call to the other two values, recompile, and rerun.  You should be able to explain the output from each of the three runs, combining your knowledge of `lseek` and your knowledge of buffer overflows in C.

Question: Why would SEEK_END be useful?
Answer: It's not for reading from file but for writing to files.  Writing beyond the end of the file grows it!

## Buffered Output
The OS often buffers data from writes before committing them to disk.  (This is in addition to any buffering that may happen on disk due to the hardware of the disk.)  The function `fsync` lets applications force the OS to write any data associated with a file descriptor immediately.

Run the command
```
prompt$ strace cat data.txt >> /dev/null
```
Since `data.txt` is a large(ish) file, the trace will now show two reads to get all the file data.  The output is buffered so we see the buffer totally full (and written to standard out) once and then partially full next time.  When the end of the file is encountered, the syscall terminates and writes the not-quite-full buffer.

As you can see, the buffer is 65536 bytes or 64K in size.  You can also see the number of bytes in a file using the long listing command: `ls -l data.txt`

## Tracing Linux Commands
Back in the day (lo, those many ages ago), you learned some basic Linux commands like `cp`, `mv` and `rm`.  If you don't remember what these commands do, don't tell me.  Pretend you remember what I've taught you while you quietly Google.  I'll wait.  You remember now?  Excellent.  On we go.

Issue the command:
```
prompt$ strace cp foo.txt bar.txt
```
Observe the series of read and write syscalls and file descriptors used to create a copy of `foo.txt` called `bar.txt`.


Now try the command:
```
prompt$ strace mv bar.txt file.txt
```

Question: What syscall does this command use to accomplish the `mv` functionality?

Now the command:
```
prompt$ strace rm file.txt
```
This one is a bit cryptic.  Look for a syscall which begins `unlink`.  What is unlink?  Remember this; more on this in a minute.

## `stat`
As you've been looking at traces you may have noticed a number of lines beginning `stat` or `fstat`.  These are commands which get file metadata.  The metadata includes things like name, size, inode number, links (what are links anyways?), access time, permissions, and more.

Run the command:
```
prompt$ stat data.txt
```
to get an idea of the metadata for your large numbers file.

You can also call the functions `stat` or `fstat` in a C program to get metadata which you can use programatically.  Metadata is maintained in an on-disk structure called the **inode** (short for index node).  The low-level **inode number** is used to associate it with one particular inode structure.  `stat` shows the inode number in the metadata.

## Links
The command `ln` creates a link between two files.
```
prompt$ ln foo.txt bar.txt
```
`ln` takes two high-level (human readable) names and associates them with the same inode number.  These links are also referred to as **hard links**.

Issue the command:
```
stat foo.txt
```
Note that `stat` now says that there are two links.  Moreover, if you run
```
prompt$ stat foo.txt bar.txt
```
you will notice that the same inode number is reported for both files.

Q: So what do links do?  
A: It tracks the number of high-level names associated with the inode reference count

Now try:
```
prompt$ rm foo.txt
prompt$ stat bar.txt
```
Notice that links=1.  So removing a linked file didn't actually get rid of it.  Remember that we know from `strace` that the command `rm` used a system call to unlink a file.  

Question: So what does unlink actually do?

It may seem that `ln` and `cp` provide the same functionality.  This is a trap; they don't.  Use `cp` to create independent copies, not `ln`.

Try to use `ln` with a directory:
```
prompt$ mkdir dir_one
prompt$ ln dir_one dir_two
```
Question: What happened?  Try to reason about why this wouldn't be allowed.  

Answer: there are a lot of good reasons.  Hard linking directories allows you to create loops, it multiplies files, and it introduces ambiguity particularly in parent/child relationships which are crucial for file system coherency.

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
prompt$ ln -s data.txt data2.txt
prompt$ stat data.txt
prompt$ stat data2.txt
```
Notice the differences:
* the two files have different inode numbers (indicates they are different structures on the disk!)
* the sizes are different (very different!)
* the `File:` metadata shows the linking

It turns out that symbolic links are special links that contain the path to the linked file!  Think of these as a pointer to the original file.

Now try to remove the file which contains the data:
```
prompt$ rm data.txt
```
Look at the files in your directory using `ls`.  `data2.txt` still exists! How can this be?  Try to open that file: `more data2.txt`.  What happens?

The "file" `data2.txt` still exists.  The contents of that file was just a path to `data.txt` (which has just been deleted).  `data2.txt` is now unusable, and we refer to it as a *dangling* or *orphan* reference. 


