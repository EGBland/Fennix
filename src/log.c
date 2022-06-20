#include <log.h>
#include <serial.h>

#define SWAP_PTR(x,y) { *(x) ^= *(y); *(y) ^= *(x); *(x) ^= *(y); }


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
        case LOG_LEVEL_CONTINUE:
        default:
            serial_print(SERIAL_PORT_COM1, "\t");
            break;
    }
    serial_print(SERIAL_PORT_COM1, msg);
    serial_print(SERIAL_PORT_COM1, "\r\n");
}

void log_dword_dec(unsigned char level, unsigned int num) {
    int i = 0;
    int j;
    char decrep[11];
    while(num > 0) {
        decrep[i] = (num%10) + 0x30;
        num /= 10;
        i++;
    }
    for(j = 0; j < i/2; j++) {
        SWAP_PTR(decrep+j, decrep+i-j-1);
    }
    decrep[i] = 0;
    log(level, decrep);
}

void log_dword_hex(unsigned char level, unsigned int num) {
    int i;
    unsigned char lo, hi, byte;
    char hexrep[9];
    for(i = 0; i < 4; i++) {
        byte = (num&(0xff<<8*i))>>(8*i);
        lo = (byte&0xf0)>>4;
        hi = byte&0xf;
        if(lo > 0x9) lo += 0x7;
        if(hi > 0x9) hi += 0x7;
        hexrep[7-2*i-1] = lo + 0x30;
        hexrep[7-2*i] = hi + 0x30;
    }
    hexrep[8] = 0;
    log(level, hexrep);
}

void log_dword_bin(unsigned char level, unsigned int num) {
    int i;
    char binrep[33];
    for(i = 0; i < 32; i++) {
        if((num&(1<<i))>>i) {
            binrep[31-i] = '1';
        }
        else {
            binrep[31-i] = '0';
        }
    }
    binrep[32] = 0;
    log(level, binrep);
}