[global _start]
[global _heap]
[global _splash]
[extern kmain]
[extern load_idt]
[extern halt]

section .bss
_heap:
    resb 1024*1024 ; 1mb of heap

section .text
_start:
    ; initialise the heap
    mov [_heap], dword 0
    mov [_heap+4], dword _heap

    call load_idt
    call kmain
    
    ; for testing idt
    ;mov edx, 0
    ;mov eax, 1
    ;mov ecx, 0
    ;div ecx
    call halt

; shouldn't get this far unless halt does something wacky
done:
    hlt
    jmp done

section .rodata
__splash:
    incbin "splash.txt"
_splash:
    dd __splash