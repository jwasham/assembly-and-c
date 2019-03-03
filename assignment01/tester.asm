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

    ;call read_char
    ;mov rdi, rax
    ;call print_char  
    ;call print_newline

    push 0
    push 0
    mov rdi, rsp
    mov rsi, 16
    call read_word
    mov rdi, rdx
    call print_string
    call print_newline
    mov rdi, rax
    call print_string
    call print_newline
    sub rsp, 16

    call exit

