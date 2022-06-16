#ifndef __SERIAL_H_DEFINED
#define __SERIAL_H_DEFINED 1

#define SERIAL_PORT_COM1 0x3f8

void serial_init(unsigned short com);
void serial_print(unsigned short com, char *s);

#endif