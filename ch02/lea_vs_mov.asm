section .data
thing: db '012345'

section .text
global _start
_start: 
    ; rsi <- address of label 'thing', a number
    mov rsi, thing

    ; rsi <- memory contents starting at thing's address 
    mov rsi, [thing]

    ; rsi <- address of thing
    ; same as mov rsi, thing
    lea rsi, [thing]

    mov rax, 3

    ; rsi <- memory contents starting at thing + rax
    mov rsi, [thing + rax]

    ; rsi <- thing + rax
    ; can't do with single mov:
    ;     mov rsi, thing
    ;     add rsi, rax
    lea rsi, [thing + rax] 
