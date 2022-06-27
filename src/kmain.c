#include <vga.h>
#include <serial.h>
#include <log.h>
#include <heap.h>
#include <stdio.h>
#include <pic.h>

void kinit() {
    pic_remap(0x20, 0x28);
    pic_mask(253, 255);
    serial_init(SERIAL_PORT_COM1);
}

void kmain() {
    extern unsigned int _heap;
    log(LOG_LEVEL_INFO, "Hello from Fennix!");
    log(LOG_LEVEL_DEBUG, "Heap is at:");
    log_dword_hex(LOG_LEVEL_CONTINUE, (unsigned int)&_heap);
    vga_set_colour(VGA_COLOUR_LIGHT_GREY, VGA_COLOUR_BLACK);
}