//From OSTEP, Ch 26
//compile with       gcc -Wall -o main-first -pthread main-first.c

#include <stdio.h>
#include "mythreads.h"
#include <stdlib.h>
#include <pthread.h>

int max;
volatile int balance = 0; //shared global variable

void* mythread(void *arg) {
    char* letter = arg;
    int i; //stack (private per thread)
    printf("%s: begin [addr of i: %p]\n", letter, &i);
    for(i = 0; i < max; i++) {
        balance = balance + 1;
    }
    printf("%s: done\n", letter);
    return NULL;
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        fprintf(stderr, "usage: main-first <loopcount>\n");
        exit(1);
    }
    max = atoi(argv[1]);
    pthread_t p1, p2;
    printf("main begin [balance=%d] [%p]\n", balance, &balance);
    Pthread_create(&p1, NULL, mythread, "A");
    Pthread_create(&p2, NULL, mythread, "B");
    
    //join waits for threads to finish
    Pthread_join(p1, NULL);
    Pthread_join(p2, NULL);
    printf("main: done\n[balance: %d] [should be: %d]\n", balance, max*2);
    return 0;
}
