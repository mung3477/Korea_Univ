#include "expressionTreeADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
	NODE *left, *right, *root;
	// -> 6 / 2
	left = createTree(NULL, "6", NULL);
	right = createTree(NULL, "2", NULL);
	root = createTree(left, "/", right);
	// -> 3 + ( )
	left = createTree(NULL, "3", NULL);
	right = root;
	root = createTree(left, "+", right);
	// -> 2 * ( )
	left = createTree(NULL, "2", NULL);
	right = root;
	root = createTree(left, "*", right);
	// -> ( ) / 4
	left = root;
	right = createTree(NULL, "4", NULL);
	root = createTree(left, "/", right);
	if (hasChild(root))
	{
		printf("Result: %f\n", evaluate(root));
	}
	destroyTree(root);
	return 0;
}