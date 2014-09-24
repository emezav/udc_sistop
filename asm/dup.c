#include <stdio.h>
#include <stdlib.h>


int main(int argc, char * argv[]){

    int x;
    int i;
	
    x = 0;

    if (argc >= 2) {
	for (i=0; i< argc - 1; i++) {
	    x = atoi(argv[1 + i]);
	    printf("Value is %d duplicate is %d\n", x, duplicate(x));
	}
    }

}
