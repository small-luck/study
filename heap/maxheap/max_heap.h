#ifndef _MAX_HEAP_H_
#define _MAX_HEAP_H_

#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 7

int heap[HEAP_SIZE];

void max_heap_insert(int *heap, int *n, int item);
int  max_heap_delete(int *heap, int *n);


#endif /*_MAX_HEAP_H_*/
