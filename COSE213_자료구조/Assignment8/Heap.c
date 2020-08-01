#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct pHeap {
    int* Heap;
    int maxSize;
    int size;
} pHeap;

void printHeap(pHeap* tHeap) {
    printf("Current Heap : ");
    for(int i = 0; i < tHeap->size; i++) {
        printf(" %d", tHeap->Heap[i]);
    }
    printf("\n");
}

pHeap* heapCreate(int maxSize)
{
    pHeap* tHeap = (pHeap*)malloc(sizeof(pHeap));
    if(tHeap == NULL){
        printf("Not enough memeory.\n");
        return NULL;
    }

    tHeap->maxSize = maxSize;
    tHeap->size = 0;
    tHeap->Heap = (int*)malloc(sizeof(int) * tHeap->maxSize);
    if(tHeap->Heap == NULL) {
        printf("Not enough memeory.\n");
        return NULL;
    }

    return tHeap;
}

bool heapFull(pHeap* tHeap)
{
    if(tHeap->size == tHeap->maxSize) return true;
    else return false;
}

bool heapEmpty(pHeap* tHeap)
{
    if(tHeap->size == 0) return true;
    else return false;
}

void _reheapUp(pHeap* tHeap, int i)
{
    //base case
    if(i == 0 || tHeap->Heap[i] < tHeap->Heap[(i - 1) / 2]) return;

    //general case (child is larger than parent)
    int t = tHeap->Heap[i];
    tHeap->Heap[i] = tHeap->Heap[(i - 1) / 2];
    tHeap->Heap[(i - 1) / 2] = t;

    _reheapUp(tHeap, (i - 1) / 2);
}

void _reheapDown(pHeap* tHeap, int i)
{
    int maxChild = 2 * i + 1;
    
    //if right child exists, and right is larger than left
    if(tHeap->size - 1 >= 2 * i + 2 && tHeap->Heap[maxChild] <= tHeap->Heap[maxChild + 1]) {
        maxChild++;
    }
    //printf("%d %d\n",tHeap->size, maxChild);

    //base case : i is leaf OR heap property was maintained
    if(tHeap->size - 1 < 2 * i + 1) return;
    //printHeap(tHeap);

    //general case : parent is smaller than children
    if(tHeap->Heap[i] < tHeap->Heap[maxChild]) {
        int t = tHeap->Heap[i];
        tHeap->Heap[i] = tHeap->Heap[maxChild];
        tHeap->Heap[maxChild] = t;

        //printHeap(tHeap);
        _reheapDown(tHeap, maxChild);
    }

}

void heapInsert(pHeap* tHeap, int data)
{
    if(tHeap == NULL) {
        printf("There's no heap. Create heap first.\n");
        return;
    }

    if(heapFull(tHeap)) {
        printf("The heap is full. Can't insert another data.\n");
        return;
    }

    tHeap->Heap[(tHeap->size)++] = data;
    _reheapUp(tHeap, (tHeap->size) - 1);
}

int heapDelete(pHeap* tHeap)
{
    if(tHeap == NULL) {
        printf("There's no heap. Create heap first.\n");
        return -1;
    }

    if(heapEmpty(tHeap)) {
        printf("The heap is empty. Can't delete data.\n");
        return -1;
    }

    //swap largest one and tail of array
    int t = tHeap->Heap[0];
    tHeap->Heap[0] = tHeap->Heap[(tHeap->size) - 1];
    tHeap->Heap[(tHeap->size) - 1] = t;
    
    //printHeap(tHeap);

    //delete logically
    int deleted = tHeap->Heap[--(tHeap->size)];

    _reheapDown(tHeap, 0);
    return deleted;
}

int heapCount(pHeap* tHeap)
{
    return tHeap->size;
}

void heapDestroy(pHeap* tHeap)
{
    //check if Heap exists
    if(tHeap == NULL) return;

    free(tHeap->Heap);
    free(tHeap);
    return;
}


