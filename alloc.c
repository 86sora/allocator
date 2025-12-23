#include "alloc.h"
#include <stdio.h>
#include <unistd.h>

struct blk_node *head = NULL;
size_t heap_size = 0;

void *alloc(size_t n, size_t size) {
    size_t nbytes = n*size;
    void *alloc_ptr = sbrk(nbytes);
    if (alloc_ptr == (void *) -1) {
        perror("ERROR: sbrk allocation failed");
        return NULL;
    }
    return alloc_ptr;
}

void alloc_free(void *ptr) {
    void *mem_location = sbrk(0);

    if ( )

}
