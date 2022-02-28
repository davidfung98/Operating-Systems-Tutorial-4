#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// Hello world function
void hello_world(){
    printf("hello world");
}


// Goodbye function
void goodbye(){
    printf("goodbye");
}

int main(){

    // Initialize threads
    pthread_t thread_id;

    // Create 2 threads
    pthread_create(&thread_id, NULL, (void *) hello_world, NULL);
    pthread_create(&thread_id, NULL, (void *) goodbye, NULL);

    // Exit thread
    pthread_exit(NULL);

    return 0;
}