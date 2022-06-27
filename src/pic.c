#include <pic.h>
#include <io.h>

void pic_ack(unsigned char irq) {
    if(irq >= 8) {
        outb(PIC2_COMMAND, PIC_EOI);
    }
    outb(PIC1_COMMAND, PIC_EOI);
}

void pic_mask(unsigned char mask1, unsigned char mask2) {
    outb(PIC1_DATA, mask1);
    outb(PIC2_DATA, mask2);
}

void pic_mask_set(unsigned char irq) {
    irq &= 0x0f;
    unsigned char pic_addr = 0x21;
    if(irq > 0x07) {
        // PIC 2
        pic_addr += 0x80;
        irq -= 8;
    }
    unsigned char mask = inb(pic_addr) | (1 << irq);
    outb(pic_addr, mask);
}

void pic_mask_clear(unsigned char irq) {
    irq &= 0x0f;
    unsigned char pic_addr = 0x21;
    if(irq > 0x07) {
        // PIC 2
        pic_addr += 0x80;
        irq -= 8;
    }
    unsigned char mask = inb(pic_addr) & ~(1 << irq);
    outb(pic_addr, mask);
}

void pic_remap(unsigned char offset1, unsigned char offset2) {
    // get masks
    unsigned char m1, m2;
    m1 = inb(PIC1_DATA);
    m2 = inb(PIC2_DATA);

    // prepare to (re)initialise PICs
    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    
    // give PICs new offsets
    outb(PIC1_DATA, offset1);
    io_wait();
    outb(PIC2_DATA, offset2);
    io_wait();

    // tell PIC1 that PIC2 is at IRQ2
    outb(PIC1_DATA, 4);
    io_wait();
    // tell PIC2 that it is at IRQ2 on PIC1
    outb(PIC2_DATA, 2);
    io_wait();

    // tell PICs to run in 8086 mode
    outb(PIC1_DATA, ICW4_8086);
    io_wait();
    outb(PIC2_DATA, ICW4_8086);
    io_wait();

    // restore masks
    outb(PIC1_DATA, m1);
    outb(PIC2_DATA, m2);
}