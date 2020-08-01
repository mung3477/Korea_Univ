#include <stdio.h>

/*functino prototype*/
void stringReverse(char strArray[]);


int main(void) {
	
	int i; //counter for for

	char strArray[30] = "Print this string backward.";

	/*print original string*/
	printf("%s\n", strArray);
	

	/*function call*/
	stringReverse(strArray);

	return 0;
} //end main

/*function definition*/
void stringReverse(char strArray[]) {
	
	if (strArray[0] != '\0') {
		stringReverse(&strArray[1]);
		printf("%c", strArray[0]);
	}

} //end function definition
