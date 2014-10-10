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
    char line[MAXSIZE];


    struct sockaddr_un addr;

       
    if (( s = socket(PF_UNIX, SOCK_STREAM, 0)) == -1) {
    	perror("Socket");
    	exit(1);
    }
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, addr_name);
    //Connect to the server
    if (connect(s, (struct sockaddr *)&addr, sizeof(struct sockaddr)) < 0) {
    	perror("Connect");
    	unlink(addr_name);
    	exit(1);
    }

    msg = (message*)malloc(sizeof(message));

    while(1) {
	//Send, receive

	msg->code = 2;
	memset(msg->data, 0, MAXSIZE);
	
	//Read line from keyboard
	memset(line, 0, MAXSIZE);
	fgets(line, MAXSIZE - 1, stdin);

	//Skip blank lines
	if (strlen(line) <= 1) {
	    continue;
	}

	strncpy(msg->data, line, MAXSIZE);

	//attempt to send and break if error
    	if (send(s, (void *)msg, sizeof(message), 0) < 0) {
    	    printf("Client send error\n");
    	    break;
	}
	
	printf("Sent: %d %s\n", msg->code, msg->data);

	//attempt to receive and break if error
	if (recv(s, (void *)msg, sizeof(message), 0) < 0) {
    	    printf("Client receive error\n");
	    break;
	}

	printf("Received: %d %s\n", msg->code, msg->data);

       }
    close(c);
    printf("Finished\n");
}
