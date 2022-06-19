#include <vga.h>
#include <serial.h>
#include <log.h>

void kmain() {
    serial_init(SERIAL_PORT_COM1);
    log(LOG_LEVEL_INFO, "Hello from Fennix!");
    vga_clear();
    char *mystr = "Hello from Fennix!";
    vga_print(0, mystr);
}