#define _CRT_SECURE_NO_WARNINGS
#include "expressionTreeADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

NODE* createTree(NODE* left, const char* dataPtr, NODE* right)
{
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	if(newNode == NULL) { return NULL; }
	
	strcpy(newNode->dataPtr, dataPtr);
	newNode->left = left;
	newNode->right = right;
	
	return newNode;
}

bool hasChild(NODE* node)
{
	if(node->left || node->right) { return true; }
	else return false;
}

void destroyTree(NODE* node)
{
	if(hasChild(node)) {
		destroyTree(node->left);
		destroyTree(node->right);
		free(node);
	}
	else {
		free(node);
	}
}

char* treeData(NODE* node)
{
	return node->dataPtr;
}

double evaluate(NODE* node)
{
	if (hasChild(node)) {
		if (!strcmp(node->dataPtr, "+")) return evaluate(node->left) + evaluate(node->right);
		else if (!strcmp(node->dataPtr, "-")) return evaluate(node->left) - evaluate(node->right);
		else if (!strcmp(node->dataPtr, "*")) return evaluate(node->left) * evaluate(node->right);
		else if (!strcmp(node->dataPtr, "/")) return evaluate(node->left) / evaluate(node->right);
	}
	else {
		return atof(node->dataPtr);
	}
}
