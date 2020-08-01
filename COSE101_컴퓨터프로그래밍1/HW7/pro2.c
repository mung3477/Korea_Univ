#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
	printf("Enter three lines of text:\n");
	char string[3][81];
	int alphabet[26] = { 0 };
	char* searchPtr;

	for (int i = 0; i < 3; i++) {
		gets(&string[i][0]);
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; string[i][j]; j++) {
			string[i][j] = tolower(string[i][j]);
		}
	}
	
	for (int i = 0; i < 3; i++) {
		
		for (int alpha = 'a'; alpha <= 'z'; alpha++) {
			searchPtr = &string[i][0];
			int count = 0;
			do{
				searchPtr = strchr(searchPtr, alpha);
				if (searchPtr!= NULL) {
					count++;
					searchPtr++;
				}
			} while (searchPtr!= NULL);
			alphabet[alpha - 'a'] += count;
		}
	}

	printf("The total occurrences of each character:\n");
	for (int i = 0; i < 26; i++) {
		printf("%c : %d\n", 'a' + i, alphabet[i]);
	}
}