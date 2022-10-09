#ifndef __TERMINAL_H_DEFINED
#define __TERMINAL_H_DEFINED 1

struct Terminal {
    unsigned short *buf;
    unsigned short cursor_pos;
};

// init a terminal struct
void term_init(struct Terminal *term);

// draw the terminal buffer to the screen
void term_draw(struct Terminal *term);

// write a character to the terminal at its cursor pos
void term_write(struct Terminal *term, unsigned char colour, char character);

// printf to terminal
void term_printf(struct Terminal *term, unsigned char colour, const char *format, ...);

// store the current screen in this terminal
void term_store_vmem(struct Terminal *term);

#endif