#include <stdio.h>

void fibLoop(void)
{
	int i;
	int fib_Arr[10] = {-1, 0, 1};
	printf("Loop:\n");
	printf("  1 : %d\n", fib_Arr[1]);
	printf("  2 : %d\n", fib_Arr[2]);
	for(i = 3; i <= 9; i++) {
		fib_Arr[i] = fib_Arr[i-2] + fib_Arr[i-1];
		printf("  %d : %d\n", i, fib_Arr[i]);
	}
}

int fib(int n)
{		
		int ans = 0;
		
		if (n == 1) return 0;
		else if (n == 2) return 1;
		else {
			return (fib(n - 1) + fib(n - 2));
		} 
}

int main(void) 
{
	int i;
	fibLoop();
	printf("-----------------------\n");
	printf("Recursion:\n");
	for(i = 1; i <= 9; i++) {
		printf("  %d : %d\n", i, fib(i));
	}
	return 0;
}

