#include <stdio.h>

void tower(int c, int start, int end, int temp);

void main() {

	int disk;

	printf("Enter the starting number of disks : ");
	scanf_s("%d", &disk);

	tower(disk, 1, 3, 2);

}

void tower(int c, int start, int end, int temp) {
	
	if (c == 2) {
		printf("%d --> %d\n", start, temp);
		printf("%d --> %d\n", start, end);
		printf("%d --> %d\n", temp, end);
		return;
	}

	if (c == 1) {
		printf("%d --> %d\n", start, end);
		return;
	}

	else {
		tower(c - 1, start, temp, end);
		tower(1, start, end, temp);
		tower(c - 1, temp, end, start);
		return;
	}

}