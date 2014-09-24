.intel_syntax noprefix

.section .text
.global myfork
myfork:
    /* Create stack frame */
    push ebp
    mov ebp, esp
	
	/* Print message */
    push OFFSET before_fork
    call printf
    add esp, 4

    /* fork() syscall */
    call fork

    /* Push ALL general purpose registers
    (push eax would be enough to preserve return value)
    */
    pusha

    /* Print message */
    push OFFSET after_fork
    call printf
    add esp, 4


    /* asm - c interaction */
    call print_stack

    popa

    mov esp, ebp
    pop ebp
    ret



.section .data
before_fork:
    .asciz "Before fork..\n"

after_fork:
    .asciz "After fork...\n"
