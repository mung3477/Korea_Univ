#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct pHeap {
    int* Heap;
    int maxSize;
    int size;
} pHeap;

pHeap* heapCreate(int maxSize);
void heapInsert(pHeap* tHeap, int data);
int heapDelete(pHeap* tHeap);
int heapCount(pHeap* tHeap);
bool heapFull(pHeap* tHeap);
bool heapEmpty(pHeap* tHeap);
void heapDestroy(pHeap* tHeap);
void _reheapUp(pHeap* tHeap, int i);
void _reheapDown(pHeap* tHeap, int i);
void printHeap(pHeap* tHeap);