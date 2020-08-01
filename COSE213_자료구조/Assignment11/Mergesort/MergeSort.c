#include <stdio.h>
#include <stdlib.h>
#define	N	10

void printArr(int arr[], const size_t size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void merge(int arr[], int low, int mid, int high)
{
	//i : overlapping index, j : array1 traverse index, k : array2 traverse index
	int i = 0, j = low, k = mid + 1;
	int tempArr[10];

	while (j <= mid && k <= high) {
		if (arr[j] <= arr[k]) {
			tempArr[i++] = arr[j++];
		}
		else {
			tempArr[i++] = arr[k++];
		}
	}
	for (j; j <= mid; j++) {
		tempArr[i++] = arr[j];
	}
	for (k; k <= high; k++) {
		tempArr[i++] = arr[k];
	}

	for (int i = low, j = 0; i <= high; i++) {
		arr[i] = tempArr[j++];
	}
}

void mergeSort(int arr[], int low, int high)
{
	if (low != high) {
		int mid = (low + high) / 2;
		mergeSort(arr, low, mid);
		mergeSort(arr, mid + 1, high);
		merge(arr, low, mid, high);
	}
}

int main()
{
	int values[N] = { 1,0,6,7,3, 9,6,6,2,8 };

	printArr(values, N);

	mergeSort(values, 0, N - 1);

	printArr(values, N);

	return 0;
}
