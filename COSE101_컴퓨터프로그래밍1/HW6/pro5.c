#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
	int arr[10];
	int i;
	srand(time(NULL));

	for (int i = 0; i < 10; i++) {
		arr[i] = rand() % 100 + 1;
	}

	for (i = 0; i < 10; i++) {
		printf("%d ", *(arr + i));
	}
	printf("\n");
	while(--i >= 0) {
		printf("%d ", *(arr + i));
	}
}