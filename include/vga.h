#ifndef __VGA_H_DEFINED
#define __VGA_H_DEFINED 1

#define VIDEO_MEMORY_BEGIN 0xb8000

#define VGA_COLOUR_BLACK 0
#define VGA_COLOUR_BLUE 1
#define VGA_COLOUR_GREEN 2
#define VGA_COLOUR_CYAN 3
#define VGA_COLOUR_RED 4
#define VGA_COLOUR_MAGENTA 5
#define VGA_COLOUR_BROWN 6
#define VGA_COLOUR_LIGHT_GREY 7
#define VGA_COLOUR_DARK_GREY 8
#define VGA_COLOUR_LIGHT_BLUE 9
#define VGA_COLOUR_LIGHT_GREEN 10
#define VGA_COLOUR_LIGHT_CYAN 11
#define VGA_COLOUR_LIGHT_RED 12
#define VGA_COLOUR_LIGHT_MAGENTA 13
#define VGA_COLOUR_LIGHT_BROWN 14
#define VGA_COLOUR_WHITE 15

void vga_set_colour(unsigned char fg, unsigned char bg);
void vga_set_cursor(unsigned short pos);
void vga_clear();
void vga_print(unsigned short offset, char *str);
void vga_print_char(unsigned short offset, char c);

#endif