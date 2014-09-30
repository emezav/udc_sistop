#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMLINES 255
#define LINESIZE 80

int pos;
char * buf[NUMLINES];

void init_buffer();

void * check_spelling(void *);
void * check_for_updates(void *);

int main(int argc, char * argv[]) 
{
    char line[LINESIZE];
    int len;
    int i;
    pthread_t t_check_spelling;
    pthread_t t_check_for_updates;
    printf("Hello\n");
    pos = 0;
    //Limpiar el buffer
    init_buffer();
    //Crear un nuevo hilo
    pthread_create(&t_check_spelling, 0, check_spelling, 0);
    pthread_create(&t_check_for_updates, 0, check_for_updates, 0);
    do {
    	
    	//Limpiar la linea
	memset(line, 0, LINESIZE);
	//Leer hasta LINESIZE - 1 caracteres
	fgets(line, LINESIZE - 1, stdin);
	len = strlen(line);
	if (len == 0) {continue;}

	if (strcmp(line, "exit\n") == 0) {break;}

	buf[pos] = (char *)malloc(len);
	memcpy(buf[pos], line, len); 
	pos++;
	if (pos == NUMLINES) {break;}
	
    }while(1);

    for (i = 0; i<pos; i++) {
    	printf("%s", buf[i]);
    }
    printf("Bye\n");
}

void * check_spelling(void * arg) 
{
    int i;
    char * s;
    int count;
    //buf , pos
    while (1) {
	    sleep(1);
	    count = 0;
	for (i=0; i<pos; i++) {
	    s = buf[i];
	    if (s == 0) {continue;}
	    while (*s != 0 && *s != '\n') {
	    	if (*s == 'a') {count++;}
	    	s++;
	    }
	}

	    printf("[%d]\n", count);

    }
}

void * check_for_updates(void * arg) 
{
    //buf , pos
    while (1) {
	sleep(1);
    	//printf(";");
    	//fflush(stdout);
    }
}

void init_buffer() {
    int i;
    for (i=0; i< NUMLINES; i++) {
	if (buf[i] != 0) { free(buf[i]);} 
	buf[i] = 0;
    }
}
