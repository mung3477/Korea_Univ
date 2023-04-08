#include <unistd.h>
#include <stdio.h>
#define os2023_push 335
#define os2023_pop 336

void _push(int data)
{
	syscall(os2023_push, data);
	printf("Push %d\n", data);
}

void _pop(void)
{
	printf("Pop %d\n", syscall(os2023_pop));
}

int main(void)
{
	_push(1);
	_push(1);
	_push(2);
	_push(3);
	_pop();
	_pop();
	_pop();
	return (0);
}
