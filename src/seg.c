#include "seg.h"
#include "io.h"

//#define SEGMENT_DESCRIPTOR(base, limit, g, type, dpl) 

void lgdt(struct GDT *gdt) {
    asm_lgdt(gdt);
}

void get_segment_descriptor(struct SegmentDescriptor *sd, unsigned int base, unsigned int limit, unsigned char type, unsigned char dpl) {
    sd->limit16 = limit&0xffff;
    sd->base16 = base&0xffff;
    sd->base24 = (base&0xff0000) >> 16;
    sd->flags = (type&0xf) | (1<<4) | ((dpl&3)<<5) | (1<<7) | ((limit&0xf0000)>>8) | (1<<14) | (1<<15);
    sd->base32 = (base&0xff000000) >> 24;
}