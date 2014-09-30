#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 5

void * thread(void * arg);

pthread_mutex_t main_mutex;

pthread_t t[N];
int ids[N];

int main(int argc, char * argv[])
{
    int i;
    pthread_t id;
    for (i=0; i<N; i++) {
    	ids[i] = i;
    	pthread_create(&t[i], 0, thread, &ids[i]);
    }


  /*  for (i=0; i<N; i++) {
    	pthread_join(t[i], 0);
    }*/

    sleep(30);


    printf("Main finished\n");
}

void * thread(void * arg) {
    int id;

    id = * (int * )arg;

    while (1) {
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
