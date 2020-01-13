# Lab - Concurrency

## Introduction
This is a short lab to let you practice writing some code using the `pthread` library.

Remember that you need to `#include <pthread.h>` at the start of your program and compile with `-lpthread` or `-pthread` to link in the library.

## Execution of Threads
Let's write a basic program that creates some threads.  Open a file named `threads1.c` and enter the following code:

```
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 99


// Print the thread's input id argument
void * print_thread_id (void *arg) {
    long id = (long) arg;
    printf("I'm thread %ld!\n", id);
    return NULL;
}


int main() {
    // Declare an array of threads
    pthread_t threads[NUM_THREADS];

    // Create those threads!
    long i;
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, print_thread_id
, (void *) i);
    }

    // Use pthread_join to make the main thread pause
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
```

Run this program **a few** times.  Remember, we're working with non-deterministic programs now, so it's important to not take a single run as the definitive answer.

Then answer the following questions:
* **Question 1:** When the program runs, does it print the numbers from 0 to 98 in order?
* **Question 2:** What does the output (from multiple runs of the program) tell you about the relationship between when threads are created and when they actually run?

Look at the fourth argument to `pthread_create`. It takes the value of `i` and casts it to the generic pointer type `void *`. This is okay: it's just a way to move the value of `i` into the `print_thread_id` function while going through the required `void *` type.

## Driving the Point Home
Modify the thread creation loop in `main` to include another print statement:

```
  for (i = 0; i < NUM_THREADS; i++) {
    pthread_create(&threads[i], NULL, print_thread_id, (v
oid*) i);
    printf("Parent process created thread %ld\n", i);
  }
```

Compile and run your code again.  Observe when threads are created vs. when they are run.  There is **a lot** of variability in the results.

## Importance of Join
Comment out the loop in `main` which calls `pthread_join`.

Run your code several times and observe the results.

* **Question 3:** What is the highest thread ID created by the parent?
* **Question 4:** What is the highest thread ID you see printed from the `print_thread_id` function with the `Hi, I'm thread X!` output?
* **Question 5:** Based on your answers to the previous two questions, speculate on what happens to threads when the parent process finishes and terminates.

Once you have finished answering the above questions and testing, uncomment the `join` calls because, as we've just proved, those are kind of important. 

Re-compile and make sure you're back to normal before proceeding.

## Pointers and References
Change two lines to the statements given below, compile and re-run the program, and see what happens:

In `main`, edit a line to be:
```
pthread_create(&threads[i], NULL, print_thread_id, &i);
// In main
```

In `print_thread_id`, edit a line to be:

```
long id = * ((long *) arg);  // In print_thread_id
```

* **Question 5:** Explain how this code is now passing the value of `i` by reference rather than by value. Be sure to note the use of the reference `&` operator and de-reference `*` operator.
* **Question 6:** Since you are now passing `i` by reference, how would you describe `i` and the address of `i`? Select all that apply.
   * `i` is now a shared resource among all threads
   * `i` is a local variable and thus allocated to each thread's individual stack
   * the address of `i` is a shared resource among all threads
   * the address of `i` is a local variable which is allocated on each thread's individual stack

## Locks
Now write a program `threads2.c` that creates two threads.

The first thread should run a function that **increments** a shared global variable in a loop. The second should run a function that **decrements** the same shared global variable in a loop. Print the value of the variable at the end of main after both threads have finished: it should be 0.

```
#include <stdio.h>
#include <pthread.h>

int value;  // Shared global

#define NUM_ITERATIONS 1000000

void * increment(void *arg) {
    int i;
        for (i = 0; i < NUM_ITERATIONS; i++) {
        value++;
    }
}

void * decrement(void *arg) {
    int i;
    for (i = 0; i < NUM_ITERATIONS; i++) {
        value--;
    }
}

int main() {

    pthread_t incrementer, decrementer;

    pthread_create(&incrementer, NULL, increment, NULL);
    pthread_create(&decrementer, NULL, decrement, NULL);
    
    pthread_join(incrementer, NULL);
    pthread_join(decrementer, NULL);

    printf("value = %d\n", value);
    return 0;
}
```

* **Question 7:** Select all the critical regions in the above program:
   * `value++;`
   * `pthread_join(incrementer, NULL);`
   * `i++;`
   * `value--;`
   * `pthread_join(decrementer, NULL);`

## Code It
* **Question 8:** Add code to `threads2.c` which protects the critical region code:
```
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;  // declare global mutex variable

pthread_mutex_lock(&lock);  // To lock the mutex
pthread_mutex_unlock(&lock);  // To unlock the mutex
```
