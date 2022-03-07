#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#include "q3.h"

void bellcurve(struct Student *student){

    (*student).grade *= 1.5;

    printf("\nStudent name: %s", (*student).name);
    printf("\nStudent ID: %i", (*student).student_id);
    printf("\nStudent grade: %d\n", (*student).grade);

}

int main(){
    struct Student students[5];

    //TODO: initialize the threads in a for loop 
    pthread_t thread_id[5];

    for(int i = 0; i<5; i++){
        printf("\nEnter student's name: ");
        scanf("%s", students[i].name);
        printf("Enter student's ID: ");
        scanf("%i", &students[i].student_id);
        printf("Enter student's grade: ");
        scanf("%d", &students[i].grade);
    }

   for (int i = 0; i < 5; i++)
    {
        pthread_create(&thread_id[i], NULL, (void *) bellcurve, &students[i]);
    }

    //TODO: add pthread_join loop here
    for ()

    pthread_exit(NULL);

    return 0;

}