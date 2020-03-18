// The "Reader-Write Lock" using semaphores
//
// From the OSTEP book

typedef struct _rwlock_t { 
    sem_t writelock;
    sem_t lock;
    int readers;
} rwlock_t;

void rwlock_init(rwlock_t *L) {
    L->readers = 0;
    sem_init(&L->lock, 1); 
    sem_init(&L->writelock, 1);
}

void rwlock_acquire_readlock(rwlock_t *L) {
    sem_wait(&L->lock);
    L->readers++; 
    if (L->readers == 1) {
	    sem_wait(&L->writelock);
    }
    sem_post(&L->lock);
} 

void rwlock_release_readlock(rwlock_t *L) {
    sem_wait(&L->lock);
    L->readers--; 
    if (L->readers == 0) {
	    sem_post(&L->writelock);
    }
    sem_post(&L->lock);
}

void rwlock_acquire_writelock(rwlock_t *L) {
    sem_wait(&L->writelock);
}

void rwlock_release_writelock(rwlock_t *L) {
    sem_post(&L->writelock);
}

