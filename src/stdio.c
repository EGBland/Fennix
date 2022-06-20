#include <stdio.h>

void memcpy(char *dst, char *src, unsigned int len) {
    for(unsigned int i = 0; i < len; i++) {
        *(dst+i) = *(src+i);
    }
}