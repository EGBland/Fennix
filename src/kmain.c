#include <vga.h>

void kmain() {
    vga_clear();
    char *mystr = "Hello from Fennix!";
    vga_print(0, mystr);
}