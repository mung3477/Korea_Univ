#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "binaryTreeADT.h"
#include "binaryTreeADT.c"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

int getTreeHeight(TREE_NODE* node)
{
	if (node == NULL) return 0;
	else return (MAX(getTreeHeight(node->left), getTreeHeight(node->right)) + 1);
}

int getTreeWeight(TREE_NODE* node)
{
	if(node == NULL) return 0;
	else return (1 + getTreeWeight(node->left) + getTreeWeight(node->right));
}

int main()
{
	TREE_NODE* rootNode = buildDummyTree();

	printf("Height: %d\n", getTreeHeight(rootNode));
	printf("Number of nodes: %d\n", getTreeWeight(rootNode));

	return 0;
}
