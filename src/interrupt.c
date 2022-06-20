#include <interrupt.h>
#include <vga.h>
#include <log.h>
#include <asm_routines.h>
#include <pic.h>

unsigned char fault_recover(struct CPUState cpu_state, struct ErrorState error_state) {
    return 0;
}

void interrupt_handler(struct CPUState cpu_state, struct ErrorState error_state) {
    if(error_state.interrupt_number < 0x20) {
        // intel exception
        vga_clear();
        vga_set_colour(VGA_COLOUR_LIGHT_GREY, VGA_COLOUR_BLACK);
        vga_print(0, "A fault occurred.");
        if(!fault_recover(cpu_state, error_state)) {
            vga_print(80, "Unrecoverable, halting.");
            halt();
        }
    }
    else {
        
    }
}