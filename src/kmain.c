#include <vga.h>
#include <serial.h>
#include <log.h>
#include <heap.h>
#include <stdio.h>
#include <pic.h>

void kinit() {
    pic_remap(0x20, 0x28);
    pic_mask(0, 0);
    serial_init(SERIAL_PORT_COM1);
}

void kmain() {
    log(LOG_LEVEL_INFO, "Hello from Fennix!");
    vga_set_colour(VGA_COLOUR_LIGHT_GREY, VGA_COLOUR_BLACK);
}