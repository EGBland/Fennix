#include <interrupt.h>
#include <vga.h>
#include <log.h>
#include <pic.h>
#include <heap.h>
#include <asm.h>

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
    "CONTROL PROTECTION EXCEPTION",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    ""
};

void (*interrupt_handlers[0x10])(struct CPUState, struct ErrorState);

unsigned char fault_recover(struct CPUState cpu_state, struct ErrorState error_state) {
    return 0;
}

void interrupt_handler(struct CPUState cpu_state, struct ErrorState error_state) {
    //log_dword_hex(LOG_LEVEL_DEBUG, error_state.interrupt_number);
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
    else if(error_state.interrupt_number < 0x30) {
        unsigned char irq = error_state.interrupt_number - 0x20;
        // PIC exception
        if(*(interrupt_handlers+irq) != 0) {
            (*(interrupt_handlers+irq))(cpu_state, error_state);
        }
        pic_ack(error_state.interrupt_number-0x20);
    }
}

void set_handler(unsigned char irq, void (*handler)(struct CPUState, struct ErrorState)) {
    if(irq > 0xf) return;
    *(interrupt_handlers+irq) = handler;
}