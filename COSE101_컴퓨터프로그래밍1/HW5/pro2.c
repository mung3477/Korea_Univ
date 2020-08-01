#include <stdio.h>
#define SIZE 15

int binarySearch(const int b[], int searchKey, int low, int high);
void printHeader( void );
void printRow(const int b[], int low, int mid, int high);

int main(void) {
	int a[SIZE];
	int i; //counter for initializing elements 0-14 of array a
	int key; //value to locate in array a
	int result; //variable to hold location of key or -1

	//create data in a 
	for (i = 0; i < SIZE; i++) {
		a[i] = 2 * i; 
	} //end for

	printf("Enter a number between 0 and 28: ");
	scanf_s("%d", &key);

	printHeader();

	//search for key in array a
	result = binarySearch(a, key, 0, SIZE - 1);

	/*display results
		if result = -1 , not found.
		if result is not -1, found. */

	if (result != -1) { 
		printf("\n%d found in array element %d\n", key, result);
	}
	else {
		printf("\n%d not found\n", key);
	} //end if&else

	return 0;
} //end main

int binarySearch(const int b[], int searchKey, int low, int high) {
	
	printRow(b, low, (low+high)/2, high);
	int middle;
	middle = b[(low + high) / 2];

	if (middle == searchKey)
			return (low + high) / 2;

	if (low != high) {

		if (middle > searchKey) {
			binarySearch(b, searchKey, low, (low+high)/2 - 1);
		}

		else {
			binarySearch(b, searchKey, (low+high)/2 + 1, high);
		}
	}

	else
		return -1;
}

void printHeader(void)
{
	int i;

	printf("\nSubscripts:\n");

	for (i = 0; i < SIZE; i++) {
		printf("%3d ", i);
	}

	printf("\n");

	for (i = 1; i <= 4 * SIZE; i++) {
		printf("-");
	}

	printf("\n");
}

void printRow(const int b[], int low, int mid, int high) {
	int i;

	for (i = 0; i < SIZE; i++) {

		if (i < low || i > high) {
			printf("   ");
		}
		else if (i == mid) {
			printf("%3d*", b[i]);
		}
		else {
			printf("%3d ", b[i]);
		}

		
	}
	printf("\n");
}
