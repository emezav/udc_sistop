#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

#define MAXSIZE 512


char * getip(char * hostname);

int main(int argc, char * argv[]) 
{

    int n;
    int s;
    int c;
    int sent;
    char line[MAXSIZE];
    char buf[BUFSIZ + 1];

    struct hostent * host;
    struct sockaddr_in addr;

    char * ip;
       
    if (( s = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
    	perror("Socket");
    	exit(1);
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);

    ip = getip(argv[1]);
    if (ip == 0) {
    	printf("Invalid host\n");
    	exit(1);
    }
    
    //addr.sin_addr.s_addr = inet_addr(argv[1]);
    if (inet_pton(AF_INET, ip, &addr.sin_addr.s_addr) <= 0) {
    	perror("inet_pton");
    	exit(1);
    }
    
    //Connect to the server
    if (connect(s, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) < 0) {
    	perror("Connect");
    	exit(1);
    }

    printf("Connected to host\n");

    memset(line, 0, MAXSIZE);
    sprintf(line, "GET %s HTTP/1.1\r\nConnection: close\r\n\r\n",
    	    argv[2]);

    printf("Sending request... \n===\n%s===\n", line);

    //attempt to send

      //Send the query to the server
      sent = 0;
      while(sent < strlen(line))
      {
         n = send(s, line+ sent, strlen(line)-sent, 0);
        if(n < 0){
          perror("Can't send query");
          exit(1);
        }
        sent  = sent + n;
      }


    n = 0;
    printf("receiving...\n");
    memset(buf, 0, BUFSIZ + 1);
    while((n = recv(s, buf, BUFSIZ, 0)) > 0){
    	if (strlen(buf) == 0) {break;}
    	fprintf(stdout, buf);
	memset(buf, 0, BUFSIZ + 1);
    }
    close(s);

}

char * getip(char * hostname){

    char  * ip;
    struct hostent * host;

    if (hostname == 0) { return 0;}

    if ((host = gethostbyname(hostname)) == 0) {
    	return 0;
    }

    if (host->h_addr_list[0] != 0) {
    	ip = (char*)malloc(INET_ADDRSTRLEN);
    	/* inet_ntoa retorna un buffer estatico, que se sobreescribe en la
    	 * siguiente llamada. Copiarlo a otra variable*/
    	if (inet_ntop(AF_INET, host->h_addr_list[0], ip, INET_ADDRSTRLEN) != 0) {
	    return ip;
	}
    }

    return 0;

}
