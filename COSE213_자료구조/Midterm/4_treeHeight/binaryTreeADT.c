#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "binaryTreeADT.h"

TREE_NODE* createTree(TREE_NODE* left, const char* dataPtr, TREE_NODE* right)
{
	TREE_NODE* node = (TREE_NODE*)malloc(sizeof(TREE_NODE));
	strcpy(node->data, dataPtr);
	node->left = left;
	node->right = right;

	return node;
}

void destroyTree(TREE_NODE *node)
{
	if (node != NULL)
	{
		destroyTree(node->left);
		destroyTree(node->right);
	}
	free(node);
}

char* treeData(TREE_NODE* node)
{
	return node->data;
}

bool hasChild(TREE_NODE* node)
{
	if (node != NULL || node->left != NULL || node->right != NULL)
	{
		return true;
	}

	return false;
}

TREE_NODE* buildDummyTree()
{
	TREE_NODE* left, *right, *root;

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

	return root;
}