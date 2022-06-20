#include <vga.h>
#include <serial.h>
#include <log.h>
#include <heap.h>
#include <stdio.h>

void kmain() {
    serial_init(SERIAL_PORT_COM1);
    log(LOG_LEVEL_INFO, "Hello from Fennix!");
    vga_clear();
    extern char *_splash;
    vga_print(0, _splash);
    for(unsigned char i = 0; i < 16; i++) {
        vga_set_colour(i, i);
        vga_print(5*i, "     ");
    }
    vga_set_colour(VGA_COLOUR_LIGHT_GREY, VGA_COLOUR_BLACK);
    vga_print(80, "Hello from Fennix!");

    // heap test
    void *my_heap_location = malloc(21);
    log(LOG_LEVEL_DEBUG, "Allocated 21 bytes onto the heap, beginning at:");
    log_dword_hex(LOG_LEVEL_CONTINUE, (unsigned int)my_heap_location);
    memcpy(my_heap_location, "Hello from the heap!", 21);
    vga_print(160, my_heap_location);
}