#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5

void * thread(void * arg);

pthread_mutex_t main_mutex;

sem_t s[N];
pthread_t t[N];
int ids[N];

int main(int argc, char * argv[])
{
    int i;
    int x;
    pthread_t id;
    for (i=0; i<N; i++) {
    	ids[i] = i;
    	sem_init(&s[i], 0, 0);
    	pthread_create(&t[i], 0, thread, &ids[i]);
    }


    while (1) {
	sleep(rand()%5);
	x = rand()%N;
	printf("The walking thread %d\n", x);
	fflush(stdout);
	sem_post(&s[x]);
    }


  /*  for (i=0; i<N; i++) {
    	pthread_join(t[i], 0);
    }*/


    printf("Main finished\n");
}

void * thread(void * arg) {
    int id;

    id = * (int * )arg;

    while (1) {
	sem_wait(&s[id]);
	printf("%d trying to aquire the mutex\n", id);
	pthread_mutex_lock(&main_mutex);
	printf("%d has acquired the mutex\n", id);
	fflush(stdout);
	sleep(rand() % 3);
	pthread_mutex_unlock(&main_mutex);
	printf("%d has released the mutex\n", id);
	fflush(stdout);
    }

}
