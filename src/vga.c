#include <vga.h>
#include <io.h>

#define VIDEO_MEMORY_BEGIN 0xb8000

unsigned char video_colour = (VGA_COLOUR_BLACK << 4) | VGA_COLOUR_LIGHT_GREY;

void vga_set_colour(unsigned char fg, unsigned char bg) {
    video_colour = ((bg&0xf) << 4) | (fg&0xf);
}

void vga_set_cursor(unsigned short pos) {
    outb(0x3d4, 14);
    outb(0x3d5, (pos>>8)&0xff);
    outb(0x3d4, 15);
    outb(0x3d5, pos&0xff);
}

void vga_clear() {
    unsigned short *vmem = (unsigned short *)(VIDEO_MEMORY_BEGIN);
    for(unsigned short i = 0; i < 80*25; i++) {
        *(vmem+i) = (video_colour << 8) | 0x20;
    }
}

void vga_print(unsigned short offset, char *str) {
    unsigned short j;
    unsigned short *start = (unsigned short *)(VIDEO_MEMORY_BEGIN + 2*offset);
    for(j = 0; *(str+j) != 0; j++) {
        *(start+j) = (video_colour << 8) | *(str+j);
    }
    vga_set_cursor(offset+j);
}