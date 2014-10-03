#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int finished;
void my_handler(int num);

int main(int argc, char * argv[])
{

    struct sigaction act;
    struct sigaction oldact;

    printf("Process started\n");

    act.sa_handler = my_handler;
    sigemptyset(&act.sa_mask);

    if (sigaction(SIGHUP, &act, &oldact) != 0) {
    	perror("Sigaction");
    	exit(0);
    }
    finished  = 0;
    
    while(!finished) {
    }

    printf("Process finished\n");
}
void my_handler(int num) {
    printf("Signal %d received\n", num);
    finished = 1;
}
