#include "alloc.h"
#include <stdio.h>
#include <unistd.h>

#define HEAP_INIT_SIZE (size_t) 4096
#define BLK_STRUCT_SIZE (size_t) sizeof(struct heap_blk)
#define PAYLOAD(blk) (void *)((char *)blk + BLK_STRUCT_SIZE)
#define BLK_HEADER(payload) (struct heap_blk *)((char *)payload - BLK_STRUCT_SIZE)

struct heap_blk *head = NULL;

void print_blk() {
    struct heap_blk *curr = head;
    size_t cnt = 0;
    while (curr){  
        void *payload = PAYLOAD(curr);
        printf("BLOCK POINTER: %p\n", (void *) curr);
        printf("BLOCK SIZE: %zu\n", curr->size);
        printf("BLOCK NEXT: %p\n", (void *) curr->next);
        printf("BLOCK PREV: %p\n", (void *) curr->prev);
        printf("BLOCK STATUS: %d\n", (int) curr->status);
        printf("BLOCK CONTENTS: %p\n\n\n",payload);
        cnt += curr->size;
        curr = curr->next;
    }
    printf("TOTAL HEAP SIZE: %zu\n\n",cnt);
}

void init_heap() { 
    void *start_blk = sbrk(HEAP_INIT_SIZE);
    if (start_blk == (void *) -1) {
        perror("ERROR: sbrk initial allocation failed");
        return;
    }
    head = (struct heap_blk *) start_blk;
    head->size = HEAP_INIT_SIZE;
    head->next = NULL;
    head->prev = NULL;
    head->status = FREE;
}

struct heap_blk *split_chunk(struct heap_blk *split_blk, size_t size) {
    struct heap_blk *blk = split_blk;

    size_t sp_size = split_blk->size;
    struct heap_blk *sp_next = split_blk->next;
    struct heap_blk *sp_prev = split_blk->prev;

    split_blk = (void *)((char *)split_blk + size);
    split_blk->size = sp_size - size;  
    split_blk->prev = blk;
    split_blk->next = sp_next;
    split_blk->status = FREE;

    if (sp_prev)
        sp_prev->next = blk;
    blk->prev = sp_prev;
    blk->next = split_blk;
    blk->size = size;
    blk->status = ALLOC;
    if (head == split_blk)
        head = blk;
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

struct heap_blk *extend_heap(size_t bytes) {
    struct heap_blk *last = head;
    while (last->next != NULL) last = last->next;

    struct heap_blk *blk = (struct heap_blk *) sbrk(bytes);
    blk->status = FREE;
    blk->prev = last;
    blk->size = bytes;
    blk->next = NULL;
    last->next = blk;
    return blk;
}

void *alloc(size_t n, size_t size) {
    if (!head) 
        init_heap();
    size_t nbytes = n*size + BLK_STRUCT_SIZE;
    printf("BYTES: %zu\n\n",n*size);
    struct heap_blk *free_blk = find_blk(nbytes);
    if (!free_blk)
        free_blk = extend_heap(nbytes);
    struct heap_blk *new_blk = split_chunk(free_blk, nbytes);
    print_blk();
    return PAYLOAD(new_blk);
}



void alloc_free(void *ptr) {
    struct heap_blk *blk = BLK_HEADER(ptr);
    blk->status = FREE;
    //TODO: merge blocks??
}
