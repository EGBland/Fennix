global outb
global inb
global asm_lgdt

outb:
    mov al, [esp+8]
    mov dx, [esp+4]
    out dx, al
    ret

inb:
    mov dx, [esp+4]
    in al, dx
    ret

asm_lgdt:
    lgdt [esp+4]
    ret