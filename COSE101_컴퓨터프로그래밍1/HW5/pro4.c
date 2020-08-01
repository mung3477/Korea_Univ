#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void matrixAdd(int matrix1[][6], int matrix2[][6], int result[][6]);

void main(void) {

	//prepare
	srand(time(NULL));

	printf("matrix1:\n");

	int matrix1[5][6];
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			matrix1[i][j] = rand() % 100 + 1;
			printf("%4d ", matrix1[i][j]);
		}
		printf("\n");
	}

	printf("\nmatrix2:\n");

	int matrix2[5][6];
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			matrix2[i][j] = rand() % 100 + 1;
			printf("%4d ", matrix2[i][j]);
		}
		printf("\n");
	}

	int result[5][6] = { 0 };

	matrixAdd(matrix1, matrix2, result);

	printf("\nresult:\n");

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			printf("%4d ", result[i][j]);
		}
		printf("\n");
	}
}

void matrixAdd(int matrix1[][6], int matrix2[][6], int result[][6]) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			result[i][j] = matrix1[i][j] + matrix2[i][j];
		}
	}
}