section .data 
newline: db 10

section .text

exit:
    mov rax, 60
    xor rdi, rdi
    syscall

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
    push rdi
    call string_length ; puts string length into rax
    pop rsi
    mov rdx, rax ; rax contains length
    mov rax, 1   ; write syscall
    mov rdi, 1   ; stdout file descriptor
    syscall
    ret

print_char:
    push rdi
    mov rdi, rsp ; rdi must be a memory location of the beginning of the string 
    call print_string
    pop rdi
    ret

print_newline:
    mov rdi, 10	  ; using a data member here will not work since it does not expect a memory address
    call print_char
    ret
 
print_uint:
    ; rdi holds 8-byte unsigned integer
    mov rax, rdi  ; rax will be dividend
    mov rcx, 10   ; divisor
    mov rsi, rsp  ; save location of the end of the buffer
    push 0        ; push null terminator, for end of string, 8 bytes
    dec rsi       ; this will point to the first char in the buffer
    sub rsp, 16   ; add space for 16 more bytes = null + 7 + 16 = 24
                  ; this gives us enough for 20 digits (unsigned long) and a null, aligned to 8 bytes

.print_uint_loop:
    cmp rax, 0
    jz .print_uint_print
    xor rdx, rdx  ; clear any garbage from last division
    div rcx ; DIV divides value in RDX:RAX by operand
                  ; quotient stored to RAX
                  ; remainder stored in RDX
    add rdx, 48   ; convert to ASCII
    dec rsi
    mov [rsi], dl ; add lower byte to buffer
    jmp .print_uint_loop

.print_uint_print:
    mov rdi, rsi  ; point rdi to beginning of string buffer
    call print_string
    add rsp, 24   ; pushing rsp at beginning and popping at end to restore will not work
                  ;     since I moved the stack pointer elsewhere
    ret

print_int:
    ; rdi holds 8-byte signed integer
    mov rsi, rdi  ; determine sign
    sar rsi, 63   ; propagate sign bit right
    cmp sil, 0xff ; see if lower bits are all on
    jne print_uint
    push rdi      ; caller-save
    mov rdi, '-'  ; print negative sign
    call print_char
    pop rdi       ; caller-restore
    neg rdi       ; turn from negative to positive: flips all bits and adds 1
    jmp print_uint

read_char:
    xor rax, rax
    ret

read_word:
    ret

; rdi points to a string ; returns rax: number, rdx : length parse_uint:
    xor rax, rax
    ret

; rdi points to a string ; returns rax: number, rdx : length parse_int:
    xor rax, rax
    ret

string_equals:
    ret

string_copy:
    ret

