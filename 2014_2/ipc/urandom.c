#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <semaphore.h>
#include <signal.h>

const char * random_filename = "/tmp/urandom";
const char * full_name = "/full_sem";
const char * empty_name = "/empty_sem";
const char * mutex_name = "/mutex_sem";

//Signal handler
void handle_sigint(int num);

//Cleanup routine
void cleanup(void);

#define N 10

//Global variables to use in main and signal handler
int fd;
sem_t * empty;
sem_t * full;
sem_t * mutex;

int main(int argc, char * argv[]) {

    int buf[N];
    int i;

    struct sigaction new_action;


    srand(time(NULL));

    //Install SIGINT signal handler
    new_action.sa_handler = handle_sigint;
    sigemptyset(&new_action.sa_mask);
    new_action.sa_flags = 0;

    sigaction(SIGINT, &new_action, 0);



    if ((empty = sem_open(empty_name, O_CREAT | O_RDWR , S_IRWXU, 1)) == SEM_FAILED) {
    	perror("Sem_open");
    	exit(0);
    }

    if ( (full = sem_open(full_name, O_CREAT | O_RDWR , S_IRWXU, 0)) == SEM_FAILED) {
    	sem_unlink(empty_name);
    	perror("sem_open");
    	exit(0);
    }
    
    if ((mutex = sem_open(mutex_name, O_CREAT | O_RDWR , S_IRWXU, 1)) == SEM_FAILED) {
    	sem_unlink(empty_name);
    	sem_unlink(full_name);
    	perror("sem_open");
    	exit(0);
    }

    while(1) {
	for (i=0; i < N; i++) {
	    buf[i] = rand() % N;
	}
    	sem_wait(empty);
    	sem_wait(mutex);
	if ( (fd = open(random_filename, O_CREAT | O_WRONLY, S_IRWXU)) == -1) {
	    cleanup();
	    perror("open");
	    exit(1);
	}
	ftruncate(fd, sizeof(int) * N);
	if (write (fd, buf, sizeof(int) * N) <= 0) {
	    break;
	}
	close(fd);
	sem_post(mutex);
	sem_post(full);
    }

    cleanup();
    exit(0);

}

void handle_sigint(int num) {
    cleanup();
    exit(1);
}

void cleanup() {
    unlink(random_filename);
    sem_unlink(empty_name);
    sem_unlink(full_name);
    sem_unlink(mutex_name);
}
