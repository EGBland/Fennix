#ifndef __ASM_H_DEFINED
#define __ASM_H_DEFINED 1

// just asm halt: hlt;jmp halt
void halt();

// same as halt() but sti first
void stop();

// write byte to i/o port
void outb(unsigned short port, unsigned char data);

// read byte from i/o port
unsigned char inb(unsigned short port);

// read from a dummy port as a delay
void io_wait();

#endif