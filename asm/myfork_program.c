#include <stdio.h>
#include <stdlib.h>

extern void myfork(void);

int main(int argc, char * argv[])
{
    printf("Hello\n");
    myfork();

}

void print_stack(unsigned int ebp, unsigned int esp,
		unsigned int edi, unsigned int esi,
		unsigned int ebx, unsigned int edx,
		unsigned int ecx, unsigned int eax ) 
{
    printf("General register values: EAX=%x EBX=%x ECX=%x EDX=%x ESI=%x ESP=%x EBP=%x\n", eax, ebx, ecx, edx, esi, edi, esp, ebp);
}

