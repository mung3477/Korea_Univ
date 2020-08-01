/*recursion의 마지막에 아무 행위도 하지 않음.*/
#include <stdio.h>
//use int64

long long fibtail(int n, long long prev, long long prevprev) 
{
	if (n == 1) return prevprev;
	else {
	return fibtail(n-1, prevprev + prev, prev);	
	}
}
 
int main(void)
{
	int i;
	scanf("%d", &i);
	printf("%d : %lld", i, fibtail(i, 1, 0));
	return 0;
}
