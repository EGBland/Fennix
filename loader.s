global loader

MAGIC_NUMBER equ 0x1BADB002
FLAGS        equ 0x0
CHECKSUM     equ -MAGIC_NUMBER

KERNEL_STACK_SIZE equ 4096

section .bss
align 4
extern print
extern clear
kernel_stack:
    resb KERNEL_STACK_SIZE

section .text:
mov esp, kernel_stack + KERNEL_STACK_SIZE
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

loader:
    call clear
    push title
    call print

.loop:
    jmp .loop

section .data
title db 'Fennix',0