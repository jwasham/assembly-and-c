section .data 

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
    mov [rsi], dl ; add lower byte of rdx to buffer
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
    cmp sil, 0xff ; see if lower 8 bits of rsi are all on
    jne print_uint
    push rdi      ; caller-save
    mov rdi, '-'  ; print negative sign
    call print_char
    pop rdi       ; caller-restore
    neg rdi       ; turn from negative to positive: flips all bits and adds 1
    jmp print_uint

read_char:
    ; returns char in rax (char at beginning)

    xor rax, rax  ; 0 is read syscall number: https://web.archive.org/web/20120210203233/http://www.acsu.buffalo.edu/~charngda/linux_syscalls_64bit.html
    mov rdi, 0    ; 0 is stdin file descriptor
    push 0        ; allocate 8 bytes on stack
    mov rsi, rsp  ; beginning of buffer
    mov rdx, 1    ; read one byte
    syscall

    ; to print input char:
    ;xor rdi, rdi
    ;mov dil, byte[rsp]
    ;sal rdi, 64 ; zero-out (null-terminate) all but first 8 bits, move 8 bits to beginning of register
    ;call print_char
    ;call print_newline
    
    pop rax
    ret

read_word:
    ; rdi - address of buffer
    ; rsi - size of buffer
    ; return 0 in rax if too large
    ; return addr in rax if it fits
    ;        and word length in rdx 
   
    ; reading a single word, so skip all whitespace until we reach
    ; a non-whitespace, then if we hit another whitespace char, 
    ; add null terminator and return

    mov rbx, rsi  ; save size of buffer
    xor rcx, rcx  ; initialize byte counter
    dec rbx       ; account for null terminator

.read_word_find_word:
    push rdi
    push rbx
    push rcx
    call read_char
    pop rcx
    pop rbx
    pop rdi
    ; char returned in rax (al)

    cmp al, 0x09       ; tab
    je .read_word_find_word
    cmp al, 0x0A       ; line feed
    je .read_word_find_word
    cmp al, 0x0D       ; carriage return
    je .read_word_find_word
    cmp al, 0x20       ; space
    je .read_word_find_word
    test al, al        ; null terminator
    jz .read_word_done

.read_word_letters_in_word:
    mov byte[rdi + rcx], al
    inc rcx

    push rdi
    push rbx
    push rcx
    call read_char
    pop rcx
    pop rbx
    pop rdi

    cmp al, 0x09       ; tab
    je .read_word_done
    cmp al, 0x0A       ; line feed
    je .read_word_done
    cmp al, 0x0D       ; carriage return
    je .read_word_done
    cmp al, 0x20       ; space
    je .read_word_done
    test al, al        ; null terminator
    jz .read_word_done

    cmp rcx, rbx       ; run out of space?
    je .read_word_too_long	

    jmp .read_word_letters_in_word

.read_word_done:
    mov byte[rdi + rcx], 0  ; null terminate the string
    mov rax, rdi
    mov rdx, rcx
    ret

.read_word_too_long:
    xor rax, rax
    ret

parse_uint:	
    ; rdi points to a string 
    ; returns rax: number, rdx : length

    xor rax, rax
    ret

parse_int:
    ; rdi points to a string 
    ; returns rax: number, rdx : length
    
    xor rax, rax
    ret

string_equals:
    ret

string_copy:
    ret

