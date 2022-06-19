[global _start]
[extern kmain]

section .text
_start:
    call kmain

done:
    hlt
    jmp done