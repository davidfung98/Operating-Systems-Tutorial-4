#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
// sometimes rand() gets seeded at the same time, so the random numbers are the same...

// Hello world function
void hello_world(){
    srand(time(NULL));
    int randomTime = rand() %10;
    sleep(randomTime);

    printf("hello world %i\n",randomTime);
}


// Goodbye function
void goodbye(){
    srand(time(NULL));
    int randomTime = rand() %10;
    sleep(randomTime);

    printf("goodbye %i\n",randomTime);
}

int main(){

    
    // Initialize threads
    pthread_t thread_id[2];

    // Create 2 threads
    pthread_create(&thread_id[0], NULL, (void *) hello_world, NULL);
    pthread_create(&thread_id[1], NULL, (void *) goodbye, NULL);

    // Exit thread
    pthread_exit(NULL);

    return 0;
}