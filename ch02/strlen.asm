global _start

section .data

test_string: db "abcdef", 0    ; the string to check for length, terminated with null

section .text

strlen:
    xor rax, rax               ; zero out rax - we'll increment from 0

.loop:
    cmp byte[rdi + rax], 0     ; look at string's byte, string is indexed starting at rdi
 
    je .end

    inc rax                    ; increment rax: increments str len size, and our rdi index
    jmp .loop

.end:
    ret

_start:
    mov rdi, test_string
    call strlen
    mov rdi, rax               ; from command line, determine str len by calling echo $?
                               ; $? returns exit code from last command
    mov rax, 60
    syscall

