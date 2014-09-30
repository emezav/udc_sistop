#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define BIGNUM 0x80000

#define N 5 	

int count;

void * inc(void *);

//sem_t mutex;
pthread_mutex_t mutex;


pthread_t t[N];
int ids[N];

int main(int argc, char * argv[]) 
{
    

    int i;

    //sem_init(&mutex, 0, 1);
    count = 0;

    for (i=0; i< N; i++) {
    	ids[i] = i;
	pthread_create(&t[i], 0, inc, &ids[i]);
    }


    //TODO ESPERAR hasta que los hilos terminen!!
    
    for (i=0; i<N; i++) {
	pthread_join(t[i], 0);
    }

    if (count == BIGNUM* N) {
    	printf("OK ");
    }
    else
    {
    	printf("ERROR ");
    }
    fflush(stdout);


}

void * inc(void * arg ){
    int i;
    int id;

    id = *(int*)arg;
    //printf("Thread %d started\n", id);


    for (i=0; i<BIGNUM; i++) {
	//sem_wait(&mutex);
	pthread_mutex_lock(&mutex);
	    //printf("%c", 'a' + id);
	    count++;
	pthread_mutex_unlock(&mutex);
	//sem_post(&mutex);
    }
    //printf("Thread %d finished\n", id);

}
