#ifndef ALLOC_H
#define ALLOC_H

#define FREE 0
#define ALLOC 1

#include <uchar.h>

struct heap_blk {
    size_t size;
    struct heap_blk *next;
    struct heap_blk *prev;
    char status;
};

void *alloc(size_t n, size_t size);

void alloc_free(void *ptr);


#endif
