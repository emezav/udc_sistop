#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

#define MAXSIZE 512

const char * addr_name = "mysocket";

typedef struct {
    int code;
    char data[MAXSIZE];
} message;

int main(int argc, char * argv[]) 
{
    int s;
    int c;
    message *msg;


    struct sockaddr_un addr;

       
    if (( s = socket(PF_UNIX, SOCK_STREAM, 0)) == -1) {
    	perror("Socket");
    	exit(1);
    }
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, "mysocket");

	c = connect(s, (struct sockaddr *)&addr, sizeof(struct sockaddr));
	printf("Client connected\n");

       while(1) {
	
	//Send, receive
	    
	msg = (message*)malloc(sizeof(message));

	msg->code = 1;
	memset(msg->data, 0, MAXSIZE);
	strcpy(msg->data, "Hello");
	
	send(s, (void *)msg, sizeof(message), 0);
	recv(s, (void *)msg, sizeof(message), 0);
	printf("Received: %s\n", msg->data);

       }
}
