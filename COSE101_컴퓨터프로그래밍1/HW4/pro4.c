#include <stdio.h>

long long factorial(int m);
long long combination(int n, int r);

int main()
{
	int n, r;

	while (1) {
		printf("Enter the inputs : ");
		scanf_s("%d %d", &n, &r);

		if (5 <= n && n <= 20 && 5 <= r && r <= 20 && n >= r)
			break;
		else
			printf("Input Error!\n\n");
	}
	printf("nCr: %lld", combination(n, r));

	return 0;

}

long long factorial(int m) {
	if (m == 0)
		return 1;
	else
	{
		return m * factorial(m - 1);
	}
}

long long combination(int n, int r) {
	if (r == 0)
		return 1;
	else
	{
		return factorial(n) / (factorial(r) * factorial(n - r));
	}
}