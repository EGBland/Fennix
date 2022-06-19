[global load_idt]
[extern interrupt_handler]

%macro interrupt_handler_no_code 1
interrupt_handler_%1:
    push 0  ; dummy error code
    push %1 ; interrupt
    jmp interrupt_handler_asm
%endmacro

%macro interrupt_handler_with_code 1
interrupt_handler_%1:
    push %1 ; interrupt
    jmp interrupt_handler_asm
%endmacro

%macro idt_entry 2
    mov eax, interrupt_handler_%1
    and eax, 0x0000ffff
    mov ecx, interrupt_handler_%1
    and ecx, 0xffff0000
    shr ecx, 16
    mov [idt_descriptors+8*%2  ], ax
    mov [idt_descriptors+8*%2+2], word 0x0008
    mov [idt_descriptors+8*%2+4], byte 0x00
    mov [idt_descriptors+8*%2+5], byte 10001111b
    mov [idt_descriptors+8*%2+6], cx
%endmacro


section .bss
align 16
idt_register:
    resb 8 ; word limit, dword start, word padding
idt_descriptors:
    resq 20 ; 20 interrupt handlers


section .text
load_idt:
    mov [idt_register], word 20*8-1
    mov [idt_register+2], dword idt_descriptors
    idt_entry 0,0
    idt_entry 1,1
    idt_entry 2,2
    idt_entry 3,3
    idt_entry 4,4
    idt_entry 5,5
    idt_entry 6,6
    idt_entry 7,7
    idt_entry 8,8
    idt_entry 9,9
    idt_entry 10,10
    idt_entry 11,11
    idt_entry 12,12
    idt_entry 13,13
    idt_entry 14,14
    idt_entry 16,15
    idt_entry 17,16
    idt_entry 18,17
    idt_entry 19,18
    idt_entry 20,19
    lidt [idt_register]
    ret

interrupt_handler_asm:
    ; preserve registers and flags
    ; stack: ebp+52 | ebp+48 | ebp+44 | ebp+40 | ebp+36
    ;        eflags | cs     | eip    | code   | int
    pushad   ; ebp+32
    push ebp ; ebp
    mov ebp, esp

    ; push the arguments for the handler in interrupt.h
    push dword [ebp+52]
    push dword [ebp+48]
    push dword [ebp+44]
    push dword [ebp+40]
    push dword [ebp+36]
    pushad
    call interrupt_handler

    ; time to leave
    leave
    popad
    add esp, 8
    iret

interrupt_handler_no_code   0   ; divide error
interrupt_handler_no_code   1   ; debug exception
interrupt_handler_no_code   2   ; nmi interrupt
interrupt_handler_no_code   3   ; breakpoint
interrupt_handler_no_code   4   ; overflow
interrupt_handler_no_code   5   ; BOUND range exceeded
interrupt_handler_no_code   6   ; invalid opcode
interrupt_handler_no_code   7   ; no math coprocessor
interrupt_handler_with_code 8   ; double fault
interrupt_handler_no_code   9   ; coprocessor segment overrun
interrupt_handler_with_code 10  ; invalid TSS
interrupt_handler_with_code 11  ; segment not present
interrupt_handler_with_code 12  ; stack-segment fault
interrupt_handler_with_code 13  ; general protection exception
interrupt_handler_with_code 14  ; page fault
interrupt_handler_no_code   16  ; x87 FPU floating-point error
interrupt_handler_with_code 17  ; alignment check
interrupt_handler_no_code   18  ; machine check
interrupt_handler_no_code   19  ; SIMD floating-point exception
interrupt_handler_no_code   20  ; virtualization exception
