#define _XOPEN_SOURCE 600 
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


#define COUNT 10
#define INFILE "grades.txt"     //input file is grade.txt (reads from this one)
#define OUTFILE "bellcurve.txt"     //output file is bellcurve.txt (saves to this one)

pthread_mutex_t t_mutex;
pthread_barrier_t t_barrier;

int grade[COUNT];       //global variable 
int total_grade = 0;        //global variable
float total_bellcurve = 0;  //global variable

void *save_bellcurve(void *arg) {
	pthread_barrier_wait(&t_barrier); 
	pthread_mutex_lock(&t_mutex); 
	
	int i = *((int*)arg);
	total_grade += grade[i];
	total_bellcurve += (float)grade[i]*1.5;    
	
	FILE *fp = fopen(OUTFILE, "a");     //sets file pointer to output file
	fprintf(fp, "%f\n", (float)grade[i]*1.5);

	pthread_mutex_unlock(&t_mutex); 
	pthread_exit(0);
}

void *read_grades() {
	pthread_mutex_lock(&t_mutex); 
	
	FILE *fp = fopen(INFILE, "r");      //sets file pointer to input file
	int i;
	for (i=0; i<COUNT; i++)
		fscanf(fp, "%d", &grade[i]);
	fclose(fp);
	
	pthread_mutex_unlock(&t_mutex); 
	pthread_barrier_wait(&t_barrier); 
	return NULL;
}

int main() {
	pthread_t r_thread;
	pthread_t w_threads[COUNT];
	
	//initializes mutex
	if (pthread_mutex_init(&t_mutex, NULL)) {
		printf("Error, unable to initialize the barrier. Exiting.\n");
		return -1;
	}
    //initializes barrier
	if (pthread_barrier_init(&t_barrier, NULL, COUNT+1)) { // 11 threads to sync
		printf("Error, unable to initialize the barrier. Exiting.\n");
		return -1;
	}
	
	//creates a read thread
	if (pthread_create(&r_thread, NULL, &read_grades, NULL)) {
		printf("Error, failed to create read thread. Exiting.\n");
		return -1;
	}

	//Creates multiple write threads
	int i;
	for (i=0; i<COUNT; i++) {
		if (pthread_create(&w_threads[i], NULL, &save_bellcurve, (void *)(&i))) {
			printf("Error, failed to create write thread %d. Exiting", i);
			return -1;
		}
	}

	//Lets the threads exit
	if (pthread_join(r_thread, NULL)) {
		printf("Error, failed to join the read thread. Exiting");
		return -1;
	}
	for (i=0; i<COUNT; i++) {
		if (pthread_join(w_threads[i], NULL)) {
			printf("Error, failed to join write thread %d. Exiting\n", i);
			return -1;
		}
	}
	pthread_barrier_destroy(&t_barrier);
	pthread_mutex_destroy(&t_mutex);
	
    //prints the total and avg before bell curve
    printf("Total: %d\n", total_grade);
    printf("Average: %f\n", (float)(total_grade/COUNT));

	// print the total and avg after bell curve
	printf("Total after Bellcurve: %f\n", total_bellcurve);
    printf("Average after Bellcurve: %f\n", total_bellcurve/COUNT);
	
	return 0;
}