.intel_syntax noprefix

.section .text
.global myfork
myfork:
    push ebp
    mov ebp, esp
	
    push OFFSET before_fork
    call printf
    add esp, 4


    call fork

    pusha

    push OFFSET after_fork
    call printf
    add esp, 4


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
