#include <stdio.h>

int function(char a[], char b[]);

int main(void) {
	char string1[80], string2[80];
	int result;

	printf("Enter two strings: ");
	scanf_s("%s %s", string1,80, string2,80);

	result = function(string1, string2);

	if (result) { //°°´Ù
		printf("%s and %s are equal.", string1, string2);
	}

	else {
		printf("%s and %s are not equal.", string1, string2);
	}
}

int function(char a[], char b[]) {
	char *aPtr = a;
	char *bPtr = b;

	while (*(aPtr) != '\0' && *(bPtr)) {
		if (*(aPtr++) != *(bPtr ++)) {
			return 0;
		}
	}

	return 1;
}