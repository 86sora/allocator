#include "alloc.h"
#include <stdio.h>
#include <unistd.h>

#define HEAP_INIT_SIZE (size_t) 4096
#define BLK_STRUCT_SIZE (size_t) sizeof(struct heap_blk)
#define PAYLOAD(blk) (void *)((char *)blk + BLK_STRUCT_SIZE)

struct heap_blk *head = NULL;

void print_blk() {
    struct heap_blk *curr = head;
    while (curr){  
        void *payload = PAYLOAD(curr);
        printf("BLOCK POINTER: %p\n", (void *) curr);
        printf("BLOCK SIZE: %zu\n", curr->size);
        printf("BLOCK NEXT: %p\n", (void *) curr->next);
        printf("BLOCK PREV: %p\n", (void *) curr->prev);
        printf("BLOCK STATUS: %d\n", (int) curr->status);
        printf("BLOCK CONTENTS: %p\n\n\n",payload);
        curr = curr->next;
    }
}

void init_heap() { 
    void *start_blk = sbrk(HEAP_INIT_SIZE);
    if (start_blk == (void *) -1) {
        perror("ERROR: sbrk initial allocation failed");
        return;
    }
    head = (struct heap_blk *) start_blk;
    head->size = HEAP_INIT_SIZE - BLK_STRUCT_SIZE;
    head->next = NULL;
    head->prev = NULL;
    head->status = FREE;
}

struct heap_blk *split_chunk(struct heap_blk *split_blk, size_t size) {
    struct heap_blk *blk = split_blk;
    split_blk->size -= size;  
    split_blk->prev = blk;
    split_blk = (void *)((char *)split_blk + size);
    blk->prev = split_blk->prev;
    blk->next = split_blk;
    blk->size = size;
    blk->status = ALLOC;
    return blk;
}

struct heap_blk *find_blk(size_t size) {
    struct heap_blk *curr = head;
    while (curr) {
        if (curr->size >= size && curr->status == FREE)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

void *alloc(size_t n, size_t size) {
    if (!head) 
        init_heap();
    size_t nbytes = n*size + BLK_STRUCT_SIZE;
    printf("BYTES: %zu\n",n*size);
    struct heap_blk *free_blk = find_blk(nbytes);
    if (!free_blk)
        return NULL;
    struct heap_blk *new_blk = split_chunk(head, nbytes);
    print_blk();
    return PAYLOAD(new_blk);
}



void alloc_free(void *ptr) {
    (void) ptr;
}
