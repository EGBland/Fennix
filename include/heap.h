#ifndef __HEAP_H_DEFINED
#define __HEAP_H_DEFINED 1

struct HeapHeader {
    unsigned short flags;
    unsigned short size;
    struct HeapHeader *next;
} __attribute__((packed));

void *malloc(unsigned short len);
void free(void *ptr);

#endif