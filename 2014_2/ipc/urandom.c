#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <semaphore.h>

const char * full_name = "/full_sem";
const char * empty_name = "/empty_sem";
const char * mutex_name = "/mutex_sem";

#define N 10

int main(int argc, char * argv[]) {
    int fd;

    int buf[N];
    int i;

    sem_t * empty;
    sem_t * full;
    sem_t * mutex;

    srand(time(NULL));



    if ( (fd = open("/tmp/urandom", O_CREAT | O_WRONLY, S_IRWXU)) == -1) {
    	perror("open");
    	exit(0);
    }

    if ((empty = sem_open(empty_name, O_CREAT | O_RDWR , S_IRWXU, 1)) == SEM_FAILED) {
    	perror("Sem_open");
    }
    full = sem_open(full_name, O_CREAT | O_RDWR , S_IRWXU, 0);
    mutex = sem_open(mutex_name, O_CREAT | O_RDWR , S_IRWXU, 1);

    ftruncate(fd, sizeof(int) * N);

    while(1) {
	for (i=0; i < N; i++) {
	    buf[i] = rand() % N;
	}
    	sem_wait(empty);
    	sem_wait(mutex);
	write (fd, buf, sizeof(int) * N);
	sem_post(mutex);
	sem_post(full);
    }

    close(fd);

}
