[global _start]
[global _heap]

[extern load_idt]
[extern kinit]
[extern kmain]
[extern halt]

section .bss
_heap:
    resb 1024*1024 ; 1mb of heap

section .text
_start:
    ; initialise idt
    call load_idt

    ; initialise the heap
    mov [_heap], dword 0
    mov [_heap+4], dword _heap

    ; main
    call kinit
    sti
    call print_splash
    call kmain
    call halt

; shouldn't get this far unless halt does something wacky
done:
    hlt
    jmp done

print_splash:
    pushad
    mov eax, 0xb8000
    mov ebx, __splash
    print_splash_loop:
        mov ecx, [ebx]
        mov [eax], cl
        add eax, 1
        add ebx, 1
        cmp ebx, __splash+4000
        jnz print_splash_loop
    popad
    ret

section .rodata
_splash:
    dd __splash
__splash:
    incbin "splash.bin"
    db 0