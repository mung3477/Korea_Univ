#include <stdio.h>

void add(int, int);
void sub(int, int);
void mul(int, int);

int main(void) {
	int(*func[3])(int, int) = { add, sub, mul };
	int op, a, b;

	printf("0. Addition\n");
	printf("1. Substraction\n");
	printf("2. Multiplication\n");
	printf("3. End\n");
	printf("select the operation: ");
	scanf_s("%d", &op);
	printf("Enter the two numbers: ");
	scanf_s("%d %d", &a, &b);

	if (op == 3) {
		printf("Exit");
		return 0;
	}

	(*func[op])(a, b);
}

void add(int x, int y)
{
	printf("\n");
	printf("\t%d + %d = %d", x, y, x + y);
	printf("\n");
}

void sub(int x, int y)
{
	printf("\n");
	printf("\t%d - %d  = %d", x, y, x - y);
	printf("\n");
}

void mul(int x, int y)
{
	printf("\n");
	printf("\t%d * %d = %d", x, y, x * y);
	printf("\n");
}