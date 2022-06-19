#include <interrupt.h>
#include <vga.h>
#include <asm_routines.h>


unsigned char attempt_recover(struct CPUState cpu_state, struct ErrorState error_state) {
    return 0;
}

void interrupt_handler(struct CPUState cpu_state, struct ErrorState error_state) {
    vga_clear();
    vga_set_colour(VGA_COLOUR_LIGHT_GREY, VGA_COLOUR_BLACK);
    vga_print(0, "An interrupt occurred.");
    if(!attempt_recover(cpu_state, error_state)) {
        vga_print(80, "Unrecoverable fault, halting.");
        halt();
    }
}