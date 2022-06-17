global loader
global gdt

MAGIC_NUMBER equ 0x1BADB002
FLAGS        equ 0x0
CHECKSUM     equ -MAGIC_NUMBER

KERNEL_STACK_SIZE equ 4096

section .bss
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE
extern kmain
gdt:
    resb 6 ; gdt
    resq 3 ; segs; null, code, data

section .text
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

loader:
    mov esp, kernel_stack + KERNEL_STACK_SIZE
    call kmain
    done:
        hlt
        jmp done ; this seems to stop QEMU freaking out