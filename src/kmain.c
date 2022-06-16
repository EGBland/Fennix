#include "fb.h"
#include "serial.h"

void kmain() {
    clear();
    print("Fennix");
    serial_init(SERIAL_PORT_COM1);
    serial_print(SERIAL_PORT_COM1, "Hello from Fennix!");
}