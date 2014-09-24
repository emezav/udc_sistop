
.intel_syntax noprefix
.code32
.section .text

.global duplicate

duplicate:
    push ebp
    mov ebp, esp
    
    xor eax, eax
    
    mov eax, [ebp + 8]

    add eax, eax

    mov esp, ebp
    pop ebp
    ret
