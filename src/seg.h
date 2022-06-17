#ifndef __SEG_H_DEFINED
#define __SEG_H_DEFINED 1

#include "io.h"

struct GDT {
    unsigned int address;
    unsigned short size;
} __attribute__((packed));

void lgdt(struct GDT *gdt);

#endif