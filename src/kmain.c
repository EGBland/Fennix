#include <vga.h>
#include <serial.h>
#include <log.h>
#include <heap.h>
#include <stdio.h>
#include <pic.h>
#include <ps2.h>
#include <asm.h>
#include <interrupt.h>

#define MIN(x,y) (((x)<(y)) ? (x) : (y))

unsigned char *kb_handler_buffer;
unsigned char semaphore = 0;

void kb_handler(struct CPUState cpu, struct ErrorState error) {
    if(semaphore&1) return;
    unsigned char byte;
    unsigned char counter = 0;
    for(counter = 0; (ps2_status() & 1) && counter < 15; counter++) {
        byte = inb(PS2_DATA_PORT);
        *(kb_handler_buffer+counter) = byte;
    }
    *(kb_handler_buffer+counter) = 0;

    semaphore |= 1;
}

void kinit() {
    // serial
    serial_init(SERIAL_PORT_COM1);

    // PS/2 driver
    unsigned char ps2_result = ps2_init();
    if(!ps2_result) {
        ps2_kb_set_mode(PS2_KB_COMMAND_MODE_MAKE_AND_RELEASE);
    }
    log(LOG_LEVEL_DEBUG, "PS/2 init result:");
    log_dword_hex(LOG_LEVEL_CONTINUE, (unsigned int)ps2_result);

    // PIC
    pic_remap(0x20, 0x28);
    pic_mask(253, 255);

    // set handlers
    kb_handler_buffer = (unsigned char *)calloc(16);
    set_handler(1, &kb_handler);
}

void kmain() {
    extern unsigned int _heap;
    log(LOG_LEVEL_INFO, "Hello from Fennix!");
    log(LOG_LEVEL_DEBUG, "Heap is at:");
    log_dword_hex(LOG_LEVEL_CONTINUE, (unsigned int)&_heap);
    while(ps2_status() & 1) {
        log_dword_hex(LOG_LEVEL_CONTINUE, inb(PS2_DATA_PORT));
    }
    vga_set_colour(VGA_COLOUR_LIGHT_GREY, VGA_COLOUR_BLACK);

    unsigned char vga_pos = 0;
    while(1) {
        if(semaphore&1) {
            log(LOG_LEVEL_INFO, "Keypress scancode");
            for(unsigned char i = 0; *(kb_handler_buffer+i) != 0; i++) {
                log_dword_hex(LOG_LEVEL_CONTINUE, *(kb_handler_buffer+i));
            }
            if(*kb_handler_buffer != 0xf0) {
                char translated = ps2_kb_translate(*kb_handler_buffer);
                vga_print_char(vga_pos, translated);
                vga_pos++;
            }
            semaphore &= ~1;
        }
    }
}