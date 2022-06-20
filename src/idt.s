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

%macro idt_entry 1
    mov eax, interrupt_handler_%1
    and eax, 0x0000ffff
    mov ecx, interrupt_handler_%1
    and ecx, 0xffff0000
    shr ecx, 16
    mov [idt_descriptors+8*%1  ], ax
    mov [idt_descriptors+8*%1+2], word 0x0008
    mov [idt_descriptors+8*%1+4], byte 0x00
    mov [idt_descriptors+8*%1+5], byte 10001111b
    mov [idt_descriptors+8*%1+6], cx
%endmacro

%macro idt_null 1
    mov [idt_descriptors+8*%1], dword 0
    mov [idt_descriptors+8*%1+4], dword 0
%endmacro


section .bss
align 16
idt_register:
    resb 8 ; word limit, dword start, word padding
idt_descriptors:
    resq 256 ; 48 interrupt handlers


section .text
load_idt:
    ;mov eax, idt_register
    mov [idt_register], word 256*8-1
    mov [idt_register+2], dword idt_descriptors
    idt_entry 0
    idt_entry 1
    idt_entry 2
    idt_entry 3
    idt_entry 4
    idt_entry 5
    idt_entry 6
    idt_entry 7
    idt_entry 8
    idt_entry 9
    idt_entry 10
    idt_entry 11
    idt_entry 12
    idt_entry 13
    idt_entry 14
    idt_null  15
    idt_entry 16
    idt_entry 17
    idt_entry 18
    idt_entry 19
    idt_entry 20
    idt_null  21
    idt_null  22
    idt_null  23
    idt_null  24
    idt_null  25
    idt_null  26
    idt_null  27
    idt_null  28
    idt_null  29
    idt_null  30
    idt_null  31
    idt_entry 32
    idt_entry 33
    idt_entry 34
    idt_entry 35
    idt_entry 36
    idt_entry 37
    idt_entry 38
    idt_entry 39
    idt_entry 40
    idt_entry 41
    idt_entry 42
    idt_entry 43
    idt_entry 44
    idt_entry 45
    idt_entry 46
    idt_entry 47
%assign i 48
%rep 256-48
    idt_null i
    %assign i i+1
%endrep
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
    pushad              ; TODO get ebp,esp from before
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

interrupt_handler_no_code   32  ; PIC
interrupt_handler_no_code   33
interrupt_handler_no_code   34
interrupt_handler_no_code   35
interrupt_handler_no_code   36
interrupt_handler_no_code   37
interrupt_handler_no_code   38
interrupt_handler_no_code   39
interrupt_handler_no_code   40
interrupt_handler_no_code   41
interrupt_handler_no_code   42
interrupt_handler_no_code   43
interrupt_handler_no_code   44
interrupt_handler_no_code   45
interrupt_handler_no_code   46
interrupt_handler_no_code   47