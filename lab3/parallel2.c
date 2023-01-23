#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#define ARRAY_SIZE 1000000
#define THREAD_NO 10
int sum = 0;
pthread_mutex_t mutex;

/*Parallel2 does generate the same results as sequential. Every sum besides the first seems to vary with each run*/
void *mythread(void *arg) {
    int *val = (int *)arg;
    int i;
    /*Sums the array using locks*/
    for(i = 0; i < ARRAY_SIZE/THREAD_NO; i++){
        pthread_mutex_lock(&mutex);
        sum += val[i];
        pthread_mutex_unlock(&mutex);
    }
    printf("sum = %d\n", sum);
}

int main(){

    pthread_t p[THREAD_NO];
    pthread_mutex_init(&mutex, NULL);
    int i, j;
    int num[THREAD_NO][ARRAY_SIZE/THREAD_NO];
    srand(100);
    //initialize arrays
    for(i=0; i< THREAD_NO; i++){
        for(j=0; j< ARRAY_SIZE/THREAD_NO; j++){
            num[i][j] = rand() % 100;
        }
    }
    
    for(i=0; i<THREAD_NO; i++){
        /*Creates the 10 threads*/
        pthread_create(&p[i], NULL, mythread, num[i]);
    }
    for(i=0; i<THREAD_NO; i++){
        pthread_join(p[i], NULL);
    }
    
    return 0;
}