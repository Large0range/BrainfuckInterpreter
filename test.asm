section .bss
buf resb 1

section .text
global _start

_start:
    mov al, 'A'          ; put 'A' in AL
    mov [buf], al        ; store in buf

    mov rax, 1           ; syscall: write
    mov rdi, 1           ; stdout
    mov rsi, buf         ; buffer
    mov rdx, 1           ; 1 byte
    syscall

    mov rax, 60          ; exit
    mov rdi, 0
    syscall