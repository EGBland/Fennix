#include "log.h"
#include "serial.h"

void log(unsigned char level, char *msg) {
    switch(level) {
        case LOG_LEVEL_INFO:
            serial_print(SERIAL_PORT_COM1, "INFO\t");
            break;
        case LOG_LEVEL_WARN:
            serial_print(SERIAL_PORT_COM1, "WARN\t");
            break;
        case LOG_LEVEL_ERR:
            serial_print(SERIAL_PORT_COM1, "ERROR\t");
            break;
        case LOG_LEVEL_DEBUG:
            serial_print(SERIAL_PORT_COM1, "DEBUG\t");
            break;
    }
    serial_print(SERIAL_PORT_COM1, msg);
    serial_print(SERIAL_PORT_COM1, "\r\n");
}