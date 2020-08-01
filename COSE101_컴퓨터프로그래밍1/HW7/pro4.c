#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)

int main(void)
{
	char words[10][50];

	for (int i = 0; i < 10; i++) {
		printf("Enter a string: ");
		scanf("%s", &words[i][0]);
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (strcmp(&words[j][0], &words[j + 1][0]) == 1) { //왼쪽이 더 크면
				char temp[50];
				strcpy(temp, &words[j][0]);
				strcpy(&words[j][0], &words[j + 1][0]);
				strcpy(&words[j + 1][0], temp);
			}
		}
	}

	printf("\nThe strings in sorted order are:\n");
	for (int i = 0; i < 10; i++) {
		printf("%s\n", words[i]);
	}
}