#include <vga.h>
#include <serial.h>
#include <log.h>
#include <heap.h>
#include <stdio.h>
#include <pic.h>
#include <ps2.h>
#include <asm.h>
#include <interrupt.h>
#include <timer.h>
#include <terminal.h>

#define MIN(x,y) (((x)<(y)) ? (x) : (y))
#define MAX(x,y) (((x)>(y)) ? (x) : (y))

#define NUMBER_OF_TERMINALS 8
unsigned char current_terminal_index;
struct Terminal *current_terminal;
struct Terminal terminals[NUMBER_OF_TERMINALS];

#define KB_BUF_LEN 8
unsigned char kb_buf_start[KB_BUF_LEN];
unsigned char *kb_buf_head = kb_buf_start;
unsigned char *kb_buf_tail = kb_buf_start;


void kb_check(struct CPUState cpu, struct ErrorState error) {
    unsigned char read_byte = 0;
    unsigned char read_result = ps2_read(&read_byte);
    log_dword_hex(LOG_LEVEL_DEBUG, read_byte);
    if(read_result && (kb_buf_tail < kb_buf_start + KB_BUF_LEN)) {
        *kb_buf_tail = read_byte;
        kb_buf_tail++;
    }
}

void kinit() {
    // serial
    serial_init(SERIAL_PORT_COM1);

    // PIC
    pic_remap(0x20, 0x28);
    pic_mask(252, 255);

    // timer
    timer_init();

    // PS/2 driver
    unsigned char ps2_result = ps2_init();
    log(LOG_LEVEL_DEBUG, "PS/2 init result:");
    log_dword_hex(LOG_LEVEL_CONTINUE, (unsigned int)ps2_result);

    // initialise terminals
    log(LOG_LEVEL_DEBUG, "terminal addresses:");
    for(unsigned char i = 0; i < NUMBER_OF_TERMINALS; i++) {
        log_dword_hex(LOG_LEVEL_CONTINUE, (unsigned int)(terminals+i));
        term_init(terminals+i);
    }

    // make kb_check interrupt handler for keyboard
    set_handler(1, kb_check);
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

    term_store_vmem(terminals); // first terminal stores the splash
    current_terminal = terminals;
    current_terminal->cursor_pos = 80;

    unsigned char discard_next = 0;
    unsigned char terminal_colour = (VGA_COLOUR_BLACK << 4) | VGA_COLOUR_LIGHT_GREY;
    while(1) {
        term_draw(current_terminal);

        // update timer
        unsigned short old_cursor_pos = current_terminal->cursor_pos;
        current_terminal->cursor_pos = 0;
        term_printf(current_terminal, terminal_colour, "Timer: %X", timer_get_time());
        current_terminal->cursor_pos = old_cursor_pos;
        
        // keyboard and printing stuff
        if(kb_buf_head == kb_buf_tail) {
            kb_buf_head = kb_buf_start;
            kb_buf_tail = kb_buf_start;
        }
        else {
            unsigned char scancode = *kb_buf_head;
            kb_buf_head++;
            if(discard_next) {
                discard_next = 0;
                continue;
            }

            switch(scancode) {
                case 0xf0: // release scancode
                    discard_next = 1;
                    break;
                case 0x66: // backspace
                    if(current_terminal->cursor_pos != 0) {
                        *(current_terminal->buf+current_terminal->cursor_pos-1) = (terminal_colour << 8) | ' ';
                        current_terminal->cursor_pos--;
                    }
                    break;
                case 0x5a: case 0x79: // return/enter
                    current_terminal->cursor_pos += (80 - (current_terminal->cursor_pos % 80));
                    break;
                default:
                    char character = ps2_translate(scancode);
                    term_write(current_terminal, terminal_colour, character);
            }
        }
    }
}