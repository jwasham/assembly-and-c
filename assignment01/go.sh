#!/bin/bash

nasm -f elf64 tester.asm -o tester.o
ld -o tester tester.o
chmod 755 tester

