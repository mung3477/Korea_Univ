#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "heapADT.h"

HEAP* heapCreate()
{
	HEAP* heap = (HEAP*)malloc(sizeof(HEAP));
	if (!heap) return NULL;

	heap->size = 0;
	heap->last = -1;
	heap->max = HEAP_ARR_SIZE;
	heap->heapArr = (int*)malloc(HEAP_ARR_SIZE * sizeof(int));

	return heap;
}

void heapDestroy(HEAP* heap)
{
	free(heap->heapArr);
	free(heap);
}

void heapSort(int* input, int* output, size_t size)
{
	HEAP* pHeap = heapCreate();
	for (int i = 0; i < size; i++) {
		heapInsert(pHeap, input[i]);
		/*for(int j = 0; j <= i; j++)
		printf("%d ", pHeap->heapArr[j]);*/
	}
	for (int i = 0; i < size; i++) {
		output[i] = heapDelete(pHeap);
	}
	return;
}

bool heapInsert(HEAP* heap, int input)
{
	//if heap is full
	if (heap->last + 1 == heap->max) return false;

	//insert data
	(heap->last)++;
	(heap->size)++;
	heap->heapArr[heap->last] = input;

	//maintain heap property
	_reheapUp(heap, heap->last);
	return true;
}

int heapDelete(HEAP* heap)
{
	int deleted = heap->heapArr[0];

	//Exchange root and last node
	heap->heapArr[0] = heap->heapArr[heap->last];
	heap->heapArr[(heap->last)--] = deleted;
	(heap->size)--;

	//Maintain heap property
	_reheapDown(heap, 0);
	return deleted;
}

void _reheapUp(HEAP* heap, int pos)
{
	//if current node is root, terminate
	if (pos == 0) return;

	//check heap property | Maxheap
	if (heap->heapArr[pos] < heap->heapArr[(pos - 1) / 2]) {
		//heap property was broken. Exchange them
		int t = heap->heapArr[(pos - 1) / 2];
		heap->heapArr[(pos - 1) / 2] = heap->heapArr[pos];
		heap->heapArr[pos] = t;

		//reheapUp again
		_reheapUp(heap, (pos - 1) / 2);
	}	
}

void _reheapDown(HEAP* heap, int pos)
{
	int leftData = 0;
	int rightData = 0;
	//if index has a child
	if (2 * pos + 1 <= heap->last) {
		leftData = heap->heapArr[2 * pos + 1];

		//if index has a right child
		if (2 * pos + 2 <= heap->last) {
			rightData = heap->heapArr[2 * pos + 2];
		}

		//Determine which child is larger
		int larger = leftData;
		int largerChild = 2 * pos + 1;
		if (rightData && rightData < leftData) {
			larger = rightData;
			largerChild++;
		}

		//check if parent is larger than children
		if (heap->heapArr[pos] > larger) {
			//maxheap broken. Exchange them
			int t = heap->heapArr[pos];
			heap->heapArr[pos] = larger;
			heap->heapArr[largerChild] = t;

			//reheapDown again
			_reheapDown(heap, largerChild);
		}
	}
}

int heapCount(HEAP* heap)
{
	return heap->size;
}

bool heapFull(HEAP* heap)
{
	return heap->size >= heap->max;
}

bool heapEmpty(HEAP* heap)
{
	return heap->size == 0;
}
