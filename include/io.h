#ifndef __IO_H_DEFINED
#define __IO_H_DEFINED 1

void outb(unsigned short port, unsigned char data);
unsigned char inb(unsigned short port);

#endif