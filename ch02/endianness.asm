section .data

newline_char: db 10
codes: db '0123456789abcdef'

global _start

print_newline:
    mov rax, 1			; 'write' syscall indentifier
    mov rdi, 1			; stdout file descriptor
    mov rsi, newline_char	; where we take data from
    mov rdx, 1			; number of bytes to write
    syscall
   ret

print_hex:
    mov rax, rdi		; puts function arg (char to print) into rax
    mov rdi, 1			; stdout
    mov rdx, 1			; number of bytes
    mov rcx, 64			; how far we're shifting rax
   ; there's no return so we fall through to iterate

iterate:
    push rax			; save initial rax value
    sub rcx, 4
    sar rax, cl			; shift to 60, 56, 52, ... 4, 0
    and rax, 0xf		; zero out all but the last 4 bits
    lea rsi, [codes + rax] 	; take a hex digit character code
    
    mov rax, 1

    push rcx			; syscall will break rcx
    syscall			; rax = 1 (31) -- the write identifier
				; rdi = 1 for stdout, rsi = character address
    pop rcx
    
    pop rax
    test rcx, rcx
    jnz iterate

   ret

section .data
demo1: dq 0x1122334455667788
demo2: db 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88

section .text

_start: 
    mov rdi, [demo1]
    call print_hex
    call print_newline
    
    mov rdi, [demo2]
    call print_hex
    call print_newline
 
    mov rax, 60
    xor rdi, rdi
    syscall

