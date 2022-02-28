#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void hello_world(){
    printf("hello world");
}

void goodbye(){
    printf("goodbye");
}

int main(){
    pthread_t thread_id;

    pthread_create(&thread_id, NULL, (void *) hello_world, NULL);
    pthread_create(&thread_id, NULL, (void *) goodbye, NULL);

    pthread_exit(NULL);

    return 0;
}