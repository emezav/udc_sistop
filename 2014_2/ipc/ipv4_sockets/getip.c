#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>

char * getip(char * hostname);

/* Este programa obtiene la primera dirección IPv4 para un
 * de host dado.*/
int main(int argc, char * argv[]) {
    char * ip_addr;

    int i;

    if (argc == 1) {
    	printf("Usage: getip hostname");
    	exit(1);
    }

    ip_addr = getip(argv[1]);

    if (ip_addr != 0) {
    	printf("%s\n", ip_addr);
    }

    exit(0);


}

char * getip(char * hostname){

    char * ip;
    struct hostent * host;

    if ((host = gethostbyname(hostname)) == 0) {
    	return 0;
    }

    if (host->h_addr_list[0] != 0) {
    	ip = (char*)malloc(INET_ADDRSTRLEN);
    	if (inet_ntop(AF_INET, host->h_addr_list[0], ip, INET_ADDRSTRLEN) != 0) {
	    return ip;
	}
    }

    return 0;

}
