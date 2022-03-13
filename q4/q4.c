#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define STUDENT 10

pthread_mutex_t x;
int total_grade = 0;   //global variable which function class_total(grade) will add to

void *class_total(void *grades) {
    pthread_mutex_lock(&x);
    int *grade = grades;
    total_grade += *grade;
    pthread_mutex_unlock(&x);
    return NULL;
}

int main() {
    pthread_t thread[STUDENT];          //makes 10 threads, 1 for each student
    int grade[STUDENT];

//for loop to get the input 
    for (int i = 0; i<STUDENT; i++) {
        printf("Enter the grade of student %d: ", i);
        scanf("%d", &grade[i]);
    }

//if statement initializes the mutex
    if(pthread_mutex_init(&x,NULL)){
        printf("Initializing mutex failed. Exiting.");
        return 1;
    }

//for loop to create threads
    for (int i =0; i<STUDENT; i++){
        //if statement checking for fail case
        if(pthread_create(&thread[i], NULL, &class_total, &grade[i])){
            printf("Error. Creating a thread failed. Exiting.");
            return 1;
        }
    }
//for loop to let all the threads exit
    for (int i = 0; i<STUDENT;i++){
        if(pthread_join(thread[i],NULL)) {
            printf("Exiting thread %d failed. Exiting.", i);
            return 1;
        }
    }
    
    //list the class total
    printf("Class Total = %d\n", total_grade);

    pthread_mutex_destroy(&x);
    return 0;
}