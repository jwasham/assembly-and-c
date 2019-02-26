section .data
    message: db 'hello', 10

section .text
%include "lib.inc"
global _start

_start:
    mov rdi, message
    call print_string

    mov rdi, 123
    call print_uint
    call print_newline

    mov rdi, 5678
    call print_int
    call print_newline

    mov rdi, -5678
    call print_int
    call print_newline

    call exit    

