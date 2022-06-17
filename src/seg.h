#ifndef __SEG_H_DEFINED
#define __SEG_H_DEFINED 1

#include "io.h"

struct GDT {
    unsigned int address;
    unsigned short size;
} __attribute__((packed));

struct SegmentDescriptor {
    unsigned short limit16; // segment limit, bits 1-16
    unsigned short base16;  // base address, bits 1-16
    unsigned char base24;   // base address, bits 17-24
    unsigned short flags;  // flags, segment limit bits 17-20
    unsigned char base32;   // base address, bits 25-32
} __attribute__((packed));

void lgdt(struct GDT *gdt);

void get_segment_descriptor(struct SegmentDescriptor *sd, unsigned int base, unsigned int limit, unsigned char type, unsigned char dpl);

#endif