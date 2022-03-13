#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#include "q3.h"

// bellcurve function
void *bellcurve(void *args){

    struct Student *s = args;

    // bellcurve grade multiplier
    (*s).grade *= 1.5;

    printf("\nStudent name: %s", (*s).name);
    printf("\nStudent ID: %i", (*s).student_id);
    printf("\nStudent grade: %f\n", (float)(*s).grade);

    return NULL;
}

int main(){
    struct Student students[5];
    pthread_t thread_id[5];

    for(int i = 0; i<5; i++){
        printf("\nEnter student's name: ");
        scanf("%s", students[i].name);
        printf("Enter student's ID: ");
        scanf("%i", &students[i].student_id);
        printf("Enter student's grade: ");
        scanf("%d", &students[i].grade);
    }

    // create threads
   for (int i = 0; i < 5; i++)
    {
        pthread_create(&thread_id[i], NULL, &bellcurve, &students[i]);
    }

    //pthread_join loop so threads wait for each other to finish first, otherwise output is a mess

    for (int i = 0; i < 5; i++)
    {
        pthread_join(thread_id[i], 0);
    }

    pthread_exit(NULL);

    return 0;

}