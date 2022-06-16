#include "gdt.h"
#include "io.h"

void lgdt(struct GDT *gdt) {
    asm_lgdt(gdt);
}