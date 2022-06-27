#include <interrupt.h>
#include <vga.h>
#include <log.h>
#include <asm_routines.h>
#include <pic.h>
#include <heap.h>
#include <io.h>

char *interrupt_names[] = {
    "DIVIDE ERROR",
    "DEBUG EXCEPTION",
    "NMI INTERRUPT",
    "BREAKPOINT",
    "OVERFLOW",
    "BOUND RANGE EXCEEDED",
    "INVALID OPCODE",
    "NO MATH COPROCESSOR",
    "DOUBLE FAULT",
    "COPROCESSOR SEGMENT OVERRUN",
    "INVALID TSS",
    "SEGMENT NOT PRESENT",
    "STACK-SEGMENT FAULT",
    "GENERAL PROTECTION EXCEPTION",
    "PAGE FAULT",
    "", // intel reserved 15
    "MATH FAULT",
    "ALIGNMENT CHECK",
    "MACHINE CHECK",
    "SIMD FLOATING-POINT EXCEPTION",
    "VIRTUALISATION EXCEPTION",
    "CONTROL PROTECTION EXCEPTION"
};

unsigned char fault_recover(struct CPUState cpu_state, struct ErrorState error_state) {
    return 0;
}

void interrupt_handler(struct CPUState cpu_state, struct ErrorState error_state) {
    log_dword_hex(LOG_LEVEL_DEBUG, error_state.interrupt_number);
    if(error_state.interrupt_number < 0x20) {
        // intel exception
        vga_clear();
        vga_set_colour(VGA_COLOUR_LIGHT_GREY, VGA_COLOUR_BLACK);
        vga_print(0, "A fault occurred: ");
        vga_print(18, interrupt_names[error_state.interrupt_number]);
        if(!fault_recover(cpu_state, error_state)) {
            vga_print(80, "Unrecoverable, halting.");
            stop();
        }
    }
    else {
        pic_ack(error_state.interrupt_number-0x20);
    }
}