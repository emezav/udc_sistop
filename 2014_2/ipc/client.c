#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#define MAXRCVLEN 500

#define PORTNUM 2348


int main(int argc, char *argv[])
{
   char buffer[] = "GET /versionP HTTP/1.1\n\n"; /* +1 so we can add null terminator */
   int len, mysocket;
   struct sockaddr_in dest; 


   mysocket = socket(AF_INET, SOCK_STREAM, 0);

   memset(&dest, 0, sizeof(dest));                /* zero the struct */
   dest.sin_family = AF_INET;
   dest.sin_addr.s_addr = inet_addr(argv[1]); /* set destination IP number */ 
   dest.sin_port = htons(atoi(argv[2]));                /* set destination port number */

   connect(mysocket, (struct sockaddr *)&dest, sizeof(struct sockaddr));
   perror("connect");

   len = send(mysocket, buffer, strlen(buffer), 0); 
  perror("len\n");

   /* We have to null terminate the received data ourselves */
   buffer[len] = '\0';

   printf("sent %s (%d bytes).\n", buffer, len);

   close(mysocket);
   return EXIT_SUCCESS;
}
