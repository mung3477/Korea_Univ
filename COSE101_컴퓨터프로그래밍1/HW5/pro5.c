#include <stdio.h>

void Sorting(int average[5]);

void main(void) {
	int score[5][5] = {0};
	int average[5] = {0};

	for (int i = 0; i < 5; i++) {
		printf("INDEX %d\n", i);
		printf("Enter 5 Quiz scores :\n");

		for (int j = 0; j < 5; j++) {
			scanf_s("%d", &score[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			average[i] += score[i][j];
		}
		average[i] /= 5;
	}

	Sorting(average);

	printf("From Highest Scores to Lowest :\n");
	for (int i = 0; i < 5; i++)
		printf("%d ", average[i]);
}

void Sorting(int average[]) {
	int t;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			if (average[j] < average[j + 1]) {
				t = average[j];
				average[j] = average[j + 1];
				average[j + 1] = t;
			}
		}
	}
}