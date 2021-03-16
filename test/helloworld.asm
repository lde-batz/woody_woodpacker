global _start

section .text

_start:
    jmp msg     ; jmp to shellcode

goback:
    mov rax, 1  ; sys_write
    mov rdi, 1  ; stdout
    pop rsi     ; pop address of msg
    mov rdx, 12 ; length of string
    syscall

    mov rax, 60 ; sys_exit
    mov rdi, 0  ; exitcode
    syscall

msg:
    call goback
    db "Hello World",0x0a
