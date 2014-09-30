#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

#define N 10

typedef void (*thread_start_func)(void * arg);

typedef struct {
  pthread_t id;
  pthread_attr_t attr;
  thread_start_func start_func;
  void * arg;
}Thread;

sem_t mutex;
sem_t db;
int rc;
int ids[N];

Thread * start_thread(thread_start_func func, void * arg) {
  Thread* t;
  t=(Thread*)malloc(sizeof(Thread));
  t->start_func=func;
  t->arg = arg;
  pthread_attr_init(&(t->attr));
  pthread_create(&(t->id), &(t->attr), (void*)t->start_func, t->arg);
  return t;
}

void down(sem_t *sem) {
  sem_wait(sem);
}

void up(sem_t *sem) {
  sem_post(sem);
}

void reader(void *param) {
  int i;
  i = *((int *)(param));
  while (1) {
    printf("Reader %d preparing to read\n", i);
    down(&mutex);
    rc=rc+1;
    if (rc == 1) down(&db);
    printf("\tRead count is %d\n", rc);
    up(&mutex);
    printf("Reader %d reading data\n", i);
    sleep(rand() % 3);
    down(&mutex);
    rc=rc-1;
    printf("\tRead count is %d\n", rc);
    if (rc == 0) up(&db);
    up(&mutex);

    printf("Reader %d using data read\n", i);
    sleep(rand()%3);
  }
}

void writer(void *param) {
   int i;
  i = *((int *)(param));
  while (1) {
    printf("Writer %d preparing to write\n", i);
    sleep(rand()%3); 
    down(&db);
    printf("Writer %d is writing data\n", i);
    sleep(rand()%5); 
    up(&db);
    printf("Writer %d has finished writing\n", i);
  }
}



int main(int argc, char * argv[]) {
  int i;
  int writers;
  int readers;

  printf("Main Started\n");

  writers = 0;
  readers = 0;
  rc=0;

  sem_init(&mutex, 0, 1);
  sem_init(&db, 0, 1);

  for (i=0; i<N; i++) {
      if (i %2 == 0) {
        ids[i]=readers;
        start_thread(reader, (void*)&ids[i]);
        readers = readers + 1;
      }else {
        ids[i]=writers;
        start_thread(writer, (void*)&ids[i]);
        writers = writers + 1;
      }

  }

  sleep(10);
  printf("Main Finished\n");
}
