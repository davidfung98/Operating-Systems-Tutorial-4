#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

struct Student {
    char name[256];
    int student_id;
    double grade;
};
