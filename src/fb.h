#ifndef __FB_H_DEFINED
#define __FB_H_DEFINED 1

#define FB_COLOUR_BLACK 0
#define FB_COLOUR_BLUE 1
#define FB_COLOUR_GREEN 2
#define FB_COLOUR_CYAN 3
#define FB_COLOUR_RED 4
#define FB_COLOUR_MAGENTA 5
#define FB_COLOUR_BROWN 6
#define FB_COLOUR_LIGHT_GREY 7
#define FB_COLOUR_DARK_GREY 8
#define FB_COLOUR_LIGHT_BLUE 9
#define FB_COLOUR_LIGHT_GREEN 10
#define FB_COLOUR_LIGHT_CYAN 11
#define FB_COLOUR_LIGHT_RED 12
#define FB_COLOUR_LIGHT_MAGENTA 13
#define FB_COLOUR_LIGHT_BROWN 14
#define FB_COLOUR_WHITE 15

void fb_print(char *s, unsigned char colour);
void fb_clear(unsigned char colour);

#endif