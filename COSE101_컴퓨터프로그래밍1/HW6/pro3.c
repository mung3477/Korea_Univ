#include <stdio.h>

void concatenate(char *str, char *str2);

void main(void) 
{
	char string1[80] = {NULL}, string2[80] = {NULL};
	int len = 0;

	printf("Enter two strings: ");
	scanf_s("%s %s", string1, 80, string2, 80);
	concatenate(string1, string2);
	
	printf("%s", string1);
}

void concatenate(char *str, char *str2) 
{
	int i = 0;
	char* Ptrstr2 = str2;

	while (*(str + i) != '\0'){
		i++;
	}

	while (*(Ptrstr2) != '\0') {
		*(str + i) = *Ptrstr2;
		i++;
		Ptrstr2++;
	}

	*(str + i) = '\0';
}