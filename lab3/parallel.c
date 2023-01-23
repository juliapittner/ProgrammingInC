#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#define ARRAY_SIZE 1000000
#define THREAD_NO 10
int sum = 0;

/*Parallel1 does not generate the same results as sequential. The results vary with each run*/
void *mythread(void *arg) {
    int *val = (int *)arg;
    int i;
    for(i = 0; i < ARRAY_SIZE/THREAD_NO; i++){
        sum += val[i];
    }
    printf("sum = %d\n", sum);
}

int main(){

    pthread_t p[THREAD_NO];
    
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
        
        pthread_create(&p[i], NULL, mythread, num[i]);
    }
    for(i=0; i<THREAD_NO; i++){
        pthread_join(p[i], NULL);
    }
    
    return 0;
}