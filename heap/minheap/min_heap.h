#ifndef _MIN_HEAP_H_
#define _MIN_HEAP_H_

#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 10

int heap[HEAP_SIZE];

void min_heap_insert(int *heap, int *n, int item);
int  min_heap_delete(int *heap, int *n);

#endif /*_MIN_HEAP_H_*/