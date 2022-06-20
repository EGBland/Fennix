#ifndef __PIC_H_DEFINED
#define __PIC_H_DEFINED 1

#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xa0
#define PIC2_DATA 0xa1

#define PIC_EOI 0x20

#define ICW1_ICW4 0x01       
#define ICW1_SINGLE 0x02
#define ICW1_INTERVAL4 0x04
#define ICW1_LEVEL 0x08
#define ICW1_INIT 0x10

#define ICW4_8086 0x01
#define ICW4_AUTO 0x02
#define ICW4_BUF_PIC1 0x08
#define ICW4_BUF_PIC2 0x0c
#define ICW4_SFNM 0x10

void pic_send_eoi(unsigned char irq);
void pic_remap(unsigned char offset1, unsigned char offset2);
void pic_mask(unsigned char mask1, unsigned char mask2);

#endif