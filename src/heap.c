#include <heap.h>
#include <asm_routines.h>
#include <log.h>

#define HEAP_MAX_SIZE 1048576

#define HEAP_BLOCK_BEGIN(block) ((unsigned int)(block)+8)
#define HEAP_BLOCK_END(block) (((unsigned int)(block)) + 8*((block)->size) + 8)
#define HEAP_BLOCK_GAP(b,c) (unsigned short)((unsigned int)(c) - HEAP_BLOCK_END(b))

void *new_block(struct HeapHeader *prev, unsigned short blockLen) {
    struct HeapHeader *nextFree = (struct HeapHeader *)(HEAP_BLOCK_END(prev));
    nextFree->size = blockLen;
    nextFree->next = prev->next;
    prev->next = nextFree;
    return (void *)(((unsigned int)nextFree)+8);
}

void *malloc(unsigned short len) {
    // get number of 8-byte blocks required to allocate this memory; return if 0
    unsigned short blockLen = (len+7)/8;
    if(blockLen == 0) return 0; // TODO error of some kind?

    // reference the heap
    extern struct HeapHeader _heap;

    // the first block is the only block
    if(_heap.next == &_heap) {
        if(_heap.size == 0) {
            // this block is free, use it
            _heap.size = blockLen;
            return (void *)(((unsigned int)&_heap) + 8);
        }
        else {
            // this block is the only one being used, use the next one
            return new_block(&_heap, blockLen);
        }
    }
    else {
        struct HeapHeader *cur = &_heap;
        while(cur->next != &_heap) {
            if(HEAP_BLOCK_GAP(cur,cur->next) > 8*blockLen) {
                return new_block(cur, blockLen);
            }
            cur = cur->next;
        }
        if(HEAP_MAX_SIZE + ((unsigned int)&_heap) - HEAP_BLOCK_END(cur) > 8*blockLen) {
            return new_block(cur, blockLen);
        }
        return 0; // no space on the heap!
    }
}

void free(void *ptr) {
    extern struct HeapHeader _heap;
    if(ptr == &_heap) {
        _heap.size = 0;
    }
    else {
        struct HeapHeader *cur = &_heap;
        while(cur->next != &_heap) {
            if(HEAP_BLOCK_BEGIN(cur->next) == (unsigned int)ptr) {
                cur->next = cur->next->next;
                return;
            }
            cur = cur->next;
        }
        // TODO here we've tried to free something that isn't on the heap, maybe flag this?
    }
}