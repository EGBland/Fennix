#include <stdio.h>
#include <stdarg.h>
#include <log.h>

union Printf_Possible_Types {
    int i;
    unsigned int ui;
};

int hex_string(char *buf, unsigned int val, unsigned char is_lowercase) {
    unsigned char i;
    unsigned char lo, hi, byte;
    for(i = 0; i < 4; i++) {
        byte = (val&(0xff<<8*i))>>(8*i);
        lo = (byte&0xf0)>>4;
        hi = byte&0xf;
        if(lo > 0x9) {
            if(is_lowercase) lo += 0x20;
            lo += 0x7;
        }
        if(hi > 0x9) {
            if(is_lowercase) hi += 0x20;
            hi += 0x7;
        }
        *(buf+7-2*i-1) = lo + 0x30;
        *(buf+7-2*i)   = hi + 0x30;
    }
    return 8;
}

int unsigned_dec_string(char *buf, unsigned int val) {
    unsigned int ctr;
    for(ctr = 0; val >= 10; ctr++) {
        *(buf+ctr) = (val % 10) + 0x30;
        val /= 10;
    }
    *(buf+ctr) = (val % 10) + 0x30;
    ctr++;
    for(unsigned int i = 0; i < ctr / 2; i++) {
        char swp = *(buf+i);
        *(buf+i) = *(buf+ctr-i-1);
        *(buf+ctr-i-1) = swp;
    }
    *(buf+ctr) = 0;
    return ctr;
}

int signed_dec_string(char *buf, int val) {
    if(val < 0) {
        val = -val;
        *buf = '-';
        buf++;
        return unsigned_dec_string(buf, (unsigned int)val) + 1;
    }
    else {
        return unsigned_dec_string(buf, (unsigned int)val);
    }
}

int sprintf(char *buf, const char *format, ...) {
    va_list lst;
    va_start(lst, format);
    return _sprintf(buf, format, lst);
}

int _sprintf(char *buf, const char *format, va_list lst) {
    char *buf_start = buf;
    union Printf_Possible_Types val;

    for(unsigned int i = 0; *(format+i) != 0; i++) {
        if(*(format+i) == '%') {
            i++;
            switch(*(format+i)) {
                case '%':
                    *buf = '%';
                    buf++;
                    continue;
                case 'd': case 'i':
                    val.i = va_arg(lst, int);
                    buf += signed_dec_string(buf, val.i);
                    continue;
                case 'u':
                    val.ui = va_arg(lst, unsigned int);
                    buf += unsigned_dec_string(buf, val.ui);
                    continue;
                case 'x':
                    // lowercase unsigned hex int
                    val.ui = va_arg(lst, unsigned int);
                    buf += hex_string(buf, val.ui, 1);
                    continue;
                case 'X':
                    // uppercase unsigned hex int
                    val.ui = va_arg(lst, unsigned int);
                    buf += hex_string(buf, val.ui, 0);
                    continue;
            }
        }
        else {
            *buf = *(format+i);
            buf++;
        }
    }
    va_end(lst);
    *buf = 0;
    return (int)(buf - buf_start);
}

void memcpy(char *dst, char *src, unsigned int len) {
    for(unsigned int i = 0; i < len; i++) {
        *(dst+i) = *(src+i);
    }
}