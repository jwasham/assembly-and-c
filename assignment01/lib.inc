section .data
newline: db 10

section .text

string_length:
    xor rax, rax

.length_loop:
    cmp byte[rdi + rax], 0
    jz .length_end
    inc rax
    jmp .length_loop

.length_end:
    ret

print_string:
    call string_length  ; puts string length into rax
    mov rdx, rax        ; rax contains length
    mov rax, 1          ; write syscall
    mov rsi, rdi        ; string pointer
    mov rdi, 1          ; stdout file descriptor
    syscall
    ret

print_char:
    call print_string
    ret

print_newline:
    mov rdi, newline
    call print_char
    ret

print_uint:
    xor rax, rax
    ret

print_int:
    xor rax, rax
    ret

string_equals:
    xor rax, rax
    ret

read_char:
    xor rax, rax
    ret 

read_word:
    ret

; rdi points to a string
; returns rax: number, rdx : length
parse_uint:
    xor rax, rax
    ret

; rdi points to a string
; returns rax: number, rdx : length
parse_int:
    xor rax, rax
    ret 

string_copy:
    ret
