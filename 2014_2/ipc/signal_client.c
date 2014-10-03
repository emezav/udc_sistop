#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char * argv[])
{

    if (argc < 3) {printf("Usage: %s PID SIGNUM\n", argv[0]);}
    kill(atoi(argv[1]), atoi(argv[2]));

}
