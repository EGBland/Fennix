global outb
global inb
global io_wait

section .text
outb:
    mov al, [esp+8]
    mov dx, [esp+4]
    out dx, al
    ret

inb:
    mov dx, [esp+4]
    in al, dx
    ret

io_wait:
    mov al, 0
    out 0x80, al
    ret
