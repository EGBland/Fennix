#include "fb.h"
#include "io.h"

char *fb = (char *) 0x000b8000;

unsigned int current_pos = 0;

void fb_write(unsigned int i, char c, unsigned char colour) {
    fb[2*i] = c;
    fb[2*i+1] = colour;
}

void fb_set_cursor(unsigned short pos) {
    outb(0x3d4, 14);
    outb(0x3d5, (pos>>8)&0xff);
    outb(0x3d4, 15);
    outb(0x3d5, pos&0xff);
}


void fb_print(char *str, unsigned char colour) {
    int j = 0;
    while(*(str+j) != 0) {
        if(*(str+j) == '\n') {
            current_pos += 80;
        }
        else if(*(str+j) == '\r') {
            current_pos /= 80;
        }
        else {
            fb_write(current_pos, *(str+j), colour);
            current_pos++;
        }
        j++;
    }
    fb_set_cursor(current_pos);
}

void fb_clear(unsigned char colour) {
    int x, y;

    for(y = 0; y < 25; y++) {
        for(x = 0; x < 80; x++) {
            fb_write(80*y+x, ' ', colour);
        }
    }

    fb_set_cursor(0);
}