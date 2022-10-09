#include <serial.h>
#include <asm.h>

#define SERIAL_DATA_PORT(base) (base)
#define SERIAL_FIFO_COMMAND_PORT(base) (base+2)
#define SERIAL_LINE_COMMAND_PORT(base) (base+3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base+4)
#define SERIAL_LINE_STATUS_PORT(base) (base+5)

#define SERIAL_LINE_ENABLE_DLAB 0x80

void serial_set_baud(unsigned short com, unsigned short divisor) {
    outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com), (divisor>>8)&0xff);
    outb(SERIAL_DATA_PORT(com), divisor&0xff);
}

void serial_configure_line(unsigned short com) {
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

void serial_configure_buffer(unsigned short com) {
    outb(SERIAL_FIFO_COMMAND_PORT(com), 0xc7);
}

void serial_configure_modem(unsigned short com) {
    outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}

char serial_ready(unsigned short com) {
    return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}


void serial_init(unsigned short com) {
    serial_set_baud(com, 1);
    serial_configure_line(com);
    serial_configure_buffer(com);
    serial_configure_modem(com);
}

void serial_print(unsigned short com, char *s) {
    int j = 0;
    while(*(s+j) != 0) {
        while(!serial_ready(com));
        outb(SERIAL_DATA_PORT(com), *(s+j));
        j++;
    }
}