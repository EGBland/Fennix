#ifndef __SERIAL_H_DEFINED
#define __SERIAL_H_DEFINED 1

#define SERIAL_PORT_COM1 0x3f8
#define SERIAL_PORT_COM2 0x2f8

// init given COM
void serial_init(unsigned short com);

// print a string to given COM
void serial_print(unsigned short com, char *s);

#endif