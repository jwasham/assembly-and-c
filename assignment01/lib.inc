section .data
newline: db 10

section .text

string_length:
    xor rax, rax
    ; without ret, it falls through to loop

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
    jmp print_char

print_uint:
    ; rdi holds 8-byte integer
    mov rax, rdi  ; rax will be dividend
    xor rsi, rsi  ; counter of how many times we've pushed
    mov rcx, 10   ; divisor
    push newline  ; sets newline at end of buffer to indicate end of string
    inc rsi

.print_uint_loop:
    cmp rax, 0
    jz .print_uint_print
    xor rdx, rdx  ; clear any garbage from last division
    div rcx       ; DIV divides value in RDX:RAX by operand
                  ; quotient stored to RAX
                  ; remainder stored in RDX
    add rdx, 48   ; convert to ASCII
    push rdx      ; push to stack for printing
    inc rsi       ; keep track of how many times we pushed
    jmp .print_uint_loop

.print_uint_print:
    lea rdi, [rsp] ; point rdi to beginning of string 
    call print_string
    mov rax, rsi  ; move push counter to rax for multiplication
    mov rsi, 8    ; register size
    mul rsi       ; multiply rax (counter) by register size
    add rsp, rax  ; effectively pop all we pushed
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
