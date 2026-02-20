section .bss
    tape resb 30000

section .text:
    global _start
    
_start:
    mov rax, 60
    mov rdi, 0
    syscall