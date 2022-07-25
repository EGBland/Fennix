#ifndef __ASM_H_DEFINED
#define __ASM_H_DEFINED 1

void halt();
void stop();

void outb(unsigned short port, unsigned char data);
unsigned char inb(unsigned short port);
void io_wait();

#endif