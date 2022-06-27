[global halt]
[global stop]

section .text
halt:
    hlt
    jmp halt

stop:
    cli
    jmp halt