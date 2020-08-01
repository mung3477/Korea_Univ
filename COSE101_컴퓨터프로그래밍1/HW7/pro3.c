#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main(void)
{
	char text[3][81];
	int length[20] = { 3 };
	char *tokenPtr;

	printf("Enter three lines of text:\n");
	for (int i = 0; i < 3; i++) {
		gets(&text[i][0]);
	}

	for (int i = 0; i < 3; i++) {
		tokenPtr = strtok(&text[i][0], " .");
		while (tokenPtr != NULL) {
			length[strlen(tokenPtr)]++;
			tokenPtr = strtok(NULL, "  .");
		}
	}
	printf("\n");

	for (int i = 1; i < 20; i++) {
		if (length[i] != 0) {
			if (length[i] == 1)
				printf("%d word of length %d\n", length[i], i);
			else
				printf("%d words of length %d\n", length[i], i);
		}
	}

	return 0;
}