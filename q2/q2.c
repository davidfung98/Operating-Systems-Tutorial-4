#define _XOPEN_SOURCE 600 // required for barriers to work 
#include <stdlib.h> 
#include <stdio.h> 
#include <pthread.h> 

//bellcurve function
void* bellcurve(void *argp){
    //casting to a float from the void pointer
    float *grade = (float *)argp;
    float bellcurve = *grade * 1.5; // calculating the 

    //printing the inital grade and what it bellcurves to. Output is limited to 2 decimal places
    printf("%.2f after bellcurve becomes %.2f\n", *grade, bellcurve);
}

int main(void) {
    //Setting up and taking an input for each of the 5 grades
    float grade[5];
    for(int i = 0; i < 5; i++){
        printf("Please enter the grade of student %d: ", i+1);
        scanf("%f", &grade[i]);
    }

    /*creating and intializing the 5 threads (one thread per grade)*/
    for (i = 0; i < 5; i++){
        pthread_t pid[i];
        pthread_create(&pid[i],NULL,bellcurve,(void *)&grade[i]);
    }

    //exiting when all threads are complete
    pthread_exit(NULL);
} 