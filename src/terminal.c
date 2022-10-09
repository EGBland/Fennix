#include <terminal.h>

#include <heap.h>
#include <vga.h>
#include <stdio.h>
#include <log.h>
#include <asm.h>

void set_cursor_pos(unsigned short pos) {
    outb(0x3d4, 14);
    outb(0x3d5, (pos>>8)&0xff);
    outb(0x3d4, 15);
    outb(0x3d5, pos&0xff);
}

void term_init(struct Terminal *term) {
    //log(LOG_LEVEL_DEBUG, "initing terminal at:");
    //log_dword_hex(LOG_LEVEL_CONTINUE, (unsigned int)term);
    term->buf = (unsigned short *)calloc(sizeof(unsigned short)*80*25);
    term->cursor_pos = 0;
}

void term_draw(struct Terminal *term) {
    memcpy((char *)VIDEO_MEMORY_BEGIN, (char *)term->buf, 80*25*2);
    set_cursor_pos(term->cursor_pos);
}

void term_write(struct Terminal *term, unsigned char colour, char character) {
    *(term->buf + term->cursor_pos) = (colour << 8) | character;
    term->cursor_pos++;
}

void term_printf(struct Terminal *term, unsigned char colour, const char *format, ...) {
    char term_buf[80];

    va_list lst;
    va_start(lst, format);
    int len = _sprintf(term_buf, format, lst);
    va_end(lst);

    for(int i = 0; i < len; i++) {
        term_write(term, colour, *(term_buf+i));
    }
}

void term_store_vmem(struct Terminal *term) {
    memcpy((char *)term->buf, (char *)VIDEO_MEMORY_BEGIN, 80*25*2);
}