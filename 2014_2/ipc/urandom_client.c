#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>

const char * full_name = "/full_sem";
const char * empty_name = "/empty_sem";
const char * mutex_name = "/mutex_sem";

#define N 10

int main(int argc, char * argv[]) {
    int fd;

    int buf[N];
    int i;
    sem_t * full;
    sem_t * empty;
    sem_t * mutex;

    if ( (fd = open("/tmp/urandom", O_RDONLY)) == -1) {
    	perror("open");
    	exit(0);
    }

    if ((empty = sem_open(empty_name, O_CREAT | O_RDWR , S_IRWXU, 1)) == SEM_FAILED) {
    	perror("Sem_open");
    }
    full = sem_open(full_name, O_CREAT | O_RDWR , S_IRWXU, 0);
    mutex = sem_open(mutex_name, O_CREAT | O_RDWR , S_IRWXU, 1);

    while(1) {
    	sem_wait(full);
    	sem_wait(mutex);
	read (fd, buf, sizeof(int) * N);

	for (i=0; i<N; i++) {
	    printf("%d\n", buf[i]);
	}
	sem_post(mutex);
	sem_post(empty);
    }

    close(fd);


}
