section .data
message: db "hello", 10

section .text
%include "lib.inc"
global _start

_start:
    mov rdi, message
    call print_string

    mov rdi, 123
    call print_uint

    mov rax, 60
    xor rdi, rdi
    syscall

