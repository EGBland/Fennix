[org 0x7c00]


;;;;;;;;;;;;;;;;;;;;;;;;; boot sector ;;;;;;;;;;;;;;;;;;;;;;;;;;
section boot
[bits 16]
mov ax, 0x8fc0
mov ss, ax
mov bp, 0xffff
mov sp, bp

; tell user that we're loading the kernel
mov bx, msg_loading
call print

; load gdt to 0x1000
mov bx, 0x100           ; segment 0x1000
mov es, bx              ;
mov bx, 0               ; segment offset 0
mov cl, 2               ; first sector is 2
mov al, 1               ; load 1 sector
call load

; load kernel to 0x100000
mov bx, 0xffff          ; segment 0xffff0
mov es, bx              ;
mov bx, 0x10            ; offset 0x10 (so start at 0x100000)
mov cl, 3               ; first sector is 3
mov al, 0x20            ; load 0x20=32 sectors
call load

; tell the user that we've loaded the kernel
mov bx, msg_loaded
call print

; load gdt and elevate
mov bx, msg_elevating
call print
cli
lgdt [0x1000]
mov eax, cr0
or eax, 0x1
mov cr0, eax
jmp SEG_CODE:elevate_done

load:
    push ax
    mov ah, 0x02
    mov dl, 0       ; drive
    mov ch, 0       ; cylinder
    mov dh, 0       ; head
    int 0x13        ; do read
    pop bx

    cmp al, bl
    jnz load_error
    ret

load_error:
    mov bx, msg_disk_error
    call print
    jmp $

print:
    mov ah, 0x0e
    print_loop:
        mov al, [bx]
        cmp al, 0
        jz print_done
        int 0x10
        add bx, 1
        jmp print_loop
    print_done:
        ret

; we are now elevated
[bits 32]
elevate_done:
mov ax, SEG_DATA
mov ds, ax
mov ss, ax
mov es, ax
mov fs, ax
mov gs, ax
mov ebp, 0x9ebff
mov esp, ebp
jmp SEG_CODE:0x100000

[bits 16]
msg_loading:
    db "Fennix is loading... ",0
msg_loaded:
    db "Loaded. ",0
msg_elevating:
    db "Elevating to 32-bit...",0
msg_disk_error:
    db "Disk read error.",0

times 510-($-$$) db 0
dw 0xaa55


;;;;;;;;;;;;;;;;;;;;;;;;;;;;; gdt ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
section gdt
gdt_register:
    dw 23
    dd 0x1008
    dw 0

; null segment
    times 8 db 0

; code segment
    dw 0xffff
    dw 0x0000
    db 0x00
    db 10011010b
    db 11001111b
    db 0x00

; data segment
    dw 0xffff
    dw 0x0000
    db 0x00
    db 10010010b
    db 11001111b
    db 0x00

SEG_CODE equ 0x08
SEG_DATA equ 0x10

times 512-($-$$) db 0