#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int max;
int balance = 0; // shared global variable



void * mythread(void *arg) {
    int i;
    for (i = 0; i < max; i++) {
        
		balance = balance + 1;
		
    }

    return NULL;
}

                                                                             
int main(int argc, char *argv[]) {                    
    if (argc != 2) {
	    fprintf(stderr, "usage: main-first <loopcount>\n");
	    exit(1);
    }
    max = atoi(argv[1]);
    
    
    
    printf("main: begin [balance = %d] [%p]\n", balance, &balance);

    // Declare and start threads
   	pthread_t p1, p2;
    pthread_create(&p1, NULL, mythread, NULL); 
    pthread_create(&p2, NULL, mythread, NULL);
    
    // Wait for threads to finish
    pthread_join(p1, NULL); 
    pthread_join(p2, NULL); 
    printf("main: done\n [balance: %d]\n [should: %d]\n", balance, max*2);
    return 0;
}

