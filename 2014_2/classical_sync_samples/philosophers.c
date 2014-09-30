#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

#define N 10
#define LEFT (i+N-1)%N
#define RIGHT (i+1)%N
#define THINKING 0
#define HUNGRY 1
#define EATING 2

typedef void (*thread_start_func)(void * arg);

typedef struct {
  pthread_t id;
  pthread_attr_t attr;
  thread_start_func start_func;
  void * arg;
}Thread;

sem_t mutex;
sem_t s[N];
int state[N];
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

void test(int i) {
  if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
    state[i]=EATING;
    up(&s[i]);
  }
}


void take_forks(int i) {
  down(&mutex);
  state[i]=HUNGRY;
  printf("\tPhilosopher %d is trying to take forks...\n", i);
  test(i);
  up(&mutex);
  down(&s[i]);
  printf("\tPhilosopher %d has aquired the forks!\n", i);
}

void put_forks(int i) {
  down(&mutex);
  state[i]=THINKING;
  printf("\tPhilosopher %d has just released the forks...\n", i);
  test(LEFT);
  test(RIGHT);
  up(&mutex);

}

void philosopher(void *param) {

  int i;

  i = *((int *)(param));
  printf("Philosopher %d is thinking...\n", i);
  sleep(rand()%3); 
  while (1) {
    printf("Philosopher %d is hungry!\n", i);
    take_forks(i);
    printf("\tPhilosopher %d is eating.\n", i);
    sleep(rand()%5);
    put_forks(i);
    printf("Philosopher %d is thinking...\n", i);
    sleep(rand()%3);
  }
}

int main(int argc, char * argv[]) {
  int i;

  printf("Main Started\n");

  sem_init(&mutex, 0, 1);
  for (i=0; i<N; i++) {
    state[i]=THINKING;
    sem_init(&s[i], 0, 0);
    ids[i]=i;
    start_thread(philosopher, (void*)&ids[i]);
  }


  sleep(20); //Dormir 20 segundos y luego terminar (todos los hilos)
  printf("Main Finished\n");
}
