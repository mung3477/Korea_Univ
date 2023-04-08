#define	STACK_MAX 100

#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/linkage.h>

int	stack[STACK_MAX];		
int	top_idx = -1;	// -1 indicates stack is empty

unsigned char _chk_no_dup(int data) {
	int	i;

	i = -1;
	while (++i <= top_idx)
	{
		if (stack[i] == data)
			return (0);
	}
	return (1);
}

void	_print_stack(void) {
	int i;

	i = top_idx;
	printk("Stack Top ------------------------\n");
	while (0 <= i)
		printk("%d\n", stack[i--]);
	printk("Stack Bottom ---------------------\n");
}

SYSCALL_DEFINE1(os2023_push, int, a) {
	if (top_idx < STACK_MAX - 1 && _chk_no_dup(a)) {
		top_idx += 1;
		stack[top_idx] = a;
	}
	printk("[System Call] os2023_push :\n");
	_print_stack();
}

SYSCALL_DEFINE0(os2023_pop) {
	int	ret;
	
	ret = -1;		// when pop fails, it still returns -1. Didn't handle the error
	if (-1 < top_idx) {
		ret = stack[top_idx];
		stack[top_idx] = 0;
		top_idx -= 1;
	}
	printk("[System Call] os2023_pop :\n");
	_print_stack();
	return (ret);
}
