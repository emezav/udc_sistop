#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#define MAXITEMS 10
#define NEXT (current + 1)%MAXITEMS
#define PREVIOUS (current + MAXITEMS - 1) % MAXITEMS

typedef void * (*thread_start_func)(void * arg);

typedef struct {
  pthread_t id;
  pthread_attr_t attr;
  thread_start_func start_func;
  void * arg;
}Thread;



sem_t mutex;
sem_t full;
sem_t empty;
int current;
int items[MAXITEMS];


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

int insert_item() {
  int item;
  item=current;
  items[current] = item;
  current = NEXT;
  return item;
}

int remove_item() {
  int item;
  item = items[PREVIOUS];
  current = PREVIOUS;
  return item;
}

void * producer(void *param) {
  int item;
  while (1) {
        down(&empty);
        down(&mutex);
        printf("Produced: %d\n", insert_item());
        up(&mutex);
        up(&full);
  }
}

void * consumer(void *param) {
  int item;
   while (1) {
     down(&full);
     down(&mutex);
     printf("\tConsumed: %d\n", remove_item());
     up(&mutex);
     up(&empty);

   }
}



int main(int argc, char * argv[]) {
  printf("Main Started\n");

  sem_init(&mutex, 0, 1); //mutex=1
  sem_init(&empty, 0, MAXITEMS); //emtpy=MAXITEMS
  sem_init(&full, 0, 0); //full = 0

  start_thread(producer, NULL);
  start_thread(consumer, NULL);

  sleep(10);

  printf("Main Finished\n");
}



