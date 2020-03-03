//counter implemented w/ threads

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 100
#define NUM_ITERATIONS 5000

//data structure definition
typedef struct __counter_t {
    int value;
    pthread_mutex_t lock;
} counter_t;

void init(counter_t *c) {
    c->value = 0;
    pthread_mutex_init(&c->lock, NULL);
}

void increment(counter_t *c) {
    pthread_mutex_lock(&c->lock);  // To lock the mutex
    c->value++;
    pthread_mutex_unlock(&c->lock);  // To unlock the mutex
}

int get(counter_t *c) {
    pthread_mutex_lock(&c->lock);
    int rc = c->value;
    pthread_mutex_unlock(&c->lock);
    return rc;
}

void* incrementCounter(void * arg) {
    counter_t *counterPtr = (counter_t *)arg;
    int i;
    for(i = 0; i < NUM_ITERATIONS; i++) {
        increment(counterPtr);
    }
}

int main() {
    //set up array of threads
    pthread_t threads[NUM_THREADS];
    
    //initialize shared counter variable
    counter_t *my_counter = malloc(sizeof(counter_t));  
    init(my_counter);
    
    // Create those threads!
    long i;
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, incrementCounter, (void *)my_counter);
    }
    
    // Use pthread_join to make the main thread pause
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("my counter's value: %d\n", get(my_counter));
    return 0;
}
