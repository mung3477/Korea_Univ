#include <stdio.h>

void function(int *aPtr, int *bPtr, int *cPtr );

void main(void) {
	int a, b, c;
	
	printf("Enter three numbers: ");
	scanf_s("%d %d %d", &a, &b, &c);

	printf("Before: a = %d, b = %d, c = %d\n", a, b, c);

	function(&a, &b, &c);

	printf("After: a = %d, b = %d, c = %d", a, b, c);
}

void function(int *a, int *b, int *c) {
	int t;

	*a += 1;
	*b = *b * *c;
	t = *b;
	*b = *c;
	*c = t;
}