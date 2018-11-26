section .data
message: db 'hello, world!', 10

section .text
global _start

_start:
    mov rax, 1        ; system call number (write) should be stored in accumulator rax
    mov rdi, 1        ; syscall arg 1: where to write (stdout's file descriptor)
    mov rsi, message  ; syscall arg 2: what to write
    mov rdx, 14       ; syscall arg 3: how many bytes
    syscall
