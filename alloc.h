#ifndef ALLOC_H
#define ALLOC_H

#include <stdlib.h>

struct blk_node {
    size_t size;
    char available;
    struct blk_node *next;
};

void *alloc(size_t n, size_t size);

void alloc_free(void *ptr);

#endif
