#include <stdio.h>
#include <stdlib.h>
#include "Heap.h"

int main(void)
{
    pHeap* tHeap = heapCreate(5);
    heapInsert(tHeap, 4);
    heapInsert(tHeap, 3);
    heapInsert(tHeap, 1);
    printHeap(tHeap);

    heapDelete(tHeap);
    printHeap(tHeap);
    heapInsert(tHeap, 5);
    printHeap(tHeap);
    return 0;
}