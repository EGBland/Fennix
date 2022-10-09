#ifndef __INTERRUPT_H_DEFINED
#define __INTERRUPT_H_DEFINED 1

struct CPUState {
    unsigned int edi;
    unsigned int esi;
    unsigned int ebp;
    unsigned int esp;
    unsigned int ebx;
    unsigned int edx;
    unsigned int ecx;
    unsigned int eax;
};

struct ErrorState {
    unsigned int interrupt_number;
    unsigned int error_code;
    unsigned int eip;
    unsigned int cs;
    unsigned int eflags;
};

// "master" handler, calls the appropriate individual handler
void interrupt_handler(struct CPUState cpu_state, struct ErrorState error_state);

// set handler for irq
void set_handler(unsigned char irq, void (*handler)(struct CPUState, struct ErrorState));

#endif