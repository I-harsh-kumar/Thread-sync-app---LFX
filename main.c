//Thread Synchronization and Signal Handling in C with Shared Memory and Bash Script Control.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

// Structure for shared memory
typedef struct {
    char message[100];
    int counter;
    pthread_mutex_t lock;
} shared_memory;

shared_memory *shm;

// Signal handler
void handle_sigint(int sig) {
    printf("SIGINT received, cleaning up and exiting...\n");
    munmap(shm, sizeof(shared_memory)); // Release shared memory
    exit(0); // Exit cleanly
}

void* thread_func(void* arg) {
    for (int i = 0; i < 20 ; i++) {
        pthread_mutex_lock(&(shm->lock));
        shm->counter += 1; // Increment shared counter
        sprintf(shm->message, "Counter: %d", shm->counter);
        printf("Thread %ld: %s\n", (long)arg, shm->message);
        pthread_mutex_unlock(&(shm->lock));
        sleep(1); // Simulate work
    }
    return NULL;
}

int main() {
    signal(SIGINT, handle_sigint); // Setup signal handler

    // Allocate shared memory
    shm = mmap(NULL, sizeof(shared_memory), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    shm->counter = 0;
    pthread_mutex_init(&(shm->lock), NULL);

    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread_func, (void*)1);
    pthread_create(&t2, NULL, thread_func, (void*)2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Clean up
    pthread_mutex_destroy(&(shm->lock));
    munmap(shm, sizeof(shared_memory));

    return 0;
}
