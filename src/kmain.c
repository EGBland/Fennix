#include "fb.h"
#include "serial.h"
#include "log.h"
#include "io.h"
#include "seg.h"

void kmain() {
    // serial logging
    serial_init(SERIAL_PORT_COM1);
    log(LOG_LEVEL_INFO, "Hello from Fennix!");

    // gdt
    extern struct GDT gdt;
    unsigned int addr = (unsigned int)&gdt;
    gdt.address = (unsigned int)(addr+8);
    gdt.size = 24;

    struct SegmentDescriptor *segs = (struct SegmentDescriptor *)(addr+8);
    log(LOG_LEVEL_DEBUG, "GDT is at");
    log_dword_hex(LOG_LEVEL_DEBUG, (unsigned int)&gdt);
    log(LOG_LEVEL_DEBUG, "Segments begin at");
    log_dword_hex(LOG_LEVEL_DEBUG, (unsigned int)segs);
    log_dword_hex(LOG_LEVEL_DEBUG, sizeof(*segs));
    log_dword_hex(LOG_LEVEL_DEBUG, sizeof(segs));

    // null segment
    segs->limit16 = 0;
    segs->base16 = 0;
    segs->base24 = 0;
    segs->flags = 0;
    segs->base32 = 0;

    // code and data segments
    get_segment_descriptor(segs+1, 0x00000000, 0xfffff, 11, 0);
    get_segment_descriptor(segs+2, 0x00000000, 0xfffff, 3, 0);
    //lgdt(&gdt);

    // greeting
    int i;
    const unsigned char colour = (FB_COLOUR_BLACK << 4) | FB_COLOUR_LIGHT_GREY;
    fb_clear(colour);
    for(i = 0; i < 16; i++) {
        fb_print(" ", i<<4);
    }
    fb_print("\r\n", colour);
    fb_print("Welcome to Fennix!", colour);
}