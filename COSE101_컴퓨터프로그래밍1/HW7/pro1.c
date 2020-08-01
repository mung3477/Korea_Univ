#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char string[6];
	int result = 0, count  = 0;

	for (; count < 4; count++) {
		printf("Enter an integer string: ");
		scanf_s("%s", string, 6);
		result += atoi(string);
	}
	
	printf("\nThe total of the values is %d", result);

}