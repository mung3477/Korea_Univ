#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define HEAP_ARR_SIZE 100

typedef struct heap 
{
	int* heapArr;
	int size;			// Number of elements
	int last;			// Index of last element
	int max;			// HeapArr capacity
} HEAP;

HEAP* heapCreate();
void heapDestroy(HEAP* heap);

void heapSort(int* input, int* output, size_t size);
bool heapInsert(HEAP* heap, int val);
int heapDelete(HEAP* heap);
void _reheapUp(HEAP* heap, int pos);
void _reheapDown(HEAP* heap, int pos);

int heapCount(HEAP* heap);
bool heapFull(HEAP* heap);
bool heapEmpty(HEAP* heap);
