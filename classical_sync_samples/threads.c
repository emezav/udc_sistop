#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 5

typedef void * (*thread_start_func)(void * arg);

typedef struct {
  pthread_t id;
  pthread_attr_t attr;
  thread_start_func start_func;
  void * arg;
}Thread;


Thread * start_thread(thread_start_func func, void * arg) {
  Thread* t;
  t=(Thread*)malloc(sizeof(Thread));
  t->start_func=func;
  t->arg = arg;
  pthread_attr_init(&(t->attr));
  pthread_create(&(t->id), &(t->attr), (void*)t->start_func, t->arg);  
  
  return t;
}

void * funcion(void *param) {
  int i;
  int * id;
 
  id = (int*)param;
	
  printf("Thread %d created\n", (int)*id);
  fflush(stdout);
   for (i=0; i<5; i++) {
	printf("\t[%d] %d\n", (int)*id, 5-i);
	fflush(stdout);
	sleep(rand() % 3); //Simular una demora aleatoria en la llegada  
  }
  printf("Thread %d finished\n", (int)*id);
  fflush(stdout);
  //pthread_exit(0);
}


Thread * hilos[N];
int id[N];

int main(int argc, char * argv[]) {
  printf("Main Started\n");
  char c;
  int i;

  for (i=0; i<N; i++) { 
    id[i] = i;
    hilos[i] = start_thread(funcion, (void*)&id[i]);
  }

  printf("Waiting for threads to finish...\n" );

  //Esperar hasta que terminen todos los hilos
  for (i=0; i<N; i++) {
     pthread_join(hilos[i]->id, NULL);  
  }

  printf("Main Finished\n");
}



