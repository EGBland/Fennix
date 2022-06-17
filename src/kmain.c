#include "fb.h"
#include "serial.h"
#include "log.h"

void kmain() {
    int i;
    const unsigned char colour = (FB_COLOUR_BLACK << 4) | FB_COLOUR_LIGHT_GREY;
    serial_init(SERIAL_PORT_COM1);
    log(LOG_LEVEL_INFO, "Hello from Fennix!");
    
    fb_clear(colour);
    for(i = 0; i < 16; i++) {
        fb_print(" ", i<<4);
    }
    fb_print("\r\n", colour);
    fb_print("Welcome to Fennix!", colour);
}