#include <stdio.h>
#include <stdbool.h>
#include "heapADT.h"

void printArr(int* data, size_t size)
{
	for (unsigned int i = 0; i < size; i++)
	{
		printf("%d ", data[i]);
	}
	printf("\n");
}

int main()
{
	int data[] = { 42, 32, 21, 16, 20, 30, 12, 13, 10, 25, 15, 17 };
	int* orderedData = (int*)malloc(sizeof(data));

	if (orderedData == NULL)
	{
		return -1;
	}

	size_t size = sizeof(data) / sizeof(int);
	heapSort(data, orderedData, size);

	printArr(data, size);
	printArr(orderedData, size);

	free(orderedData);

	return 0;
}