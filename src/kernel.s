[global _start]
[extern kmain]
[extern load_idt]

section .text
_start:
    call load_idt
    call kmain
    
    ; for testing idt
    mov edx, 0
    mov eax, 1
    mov ecx, 0
    div ecx

done:
    hlt
    jmp done