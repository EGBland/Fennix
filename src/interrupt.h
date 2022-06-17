#ifndef __INTERRUPT_H_DEFINED
#define __INTERRUPT_H_DEFINED

#define IDT_FLAGS(d, dpl) (3 | ((d&1)<<11) | (dpl&3)<<13 | (p&1)<<15)

struct IDTEntry {
    unsigned short offsetLow;
    unsigned short segSelector;
    unsigned short flags;
    unsigned short offsetHigh;
} __attribute__((packed));

#endif