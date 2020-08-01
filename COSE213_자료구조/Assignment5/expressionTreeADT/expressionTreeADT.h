#pragma once
#include <stdbool.h>
#define STR_MAX 16

typedef struct node
{
	char dataPtr[STR_MAX];
	struct node* left;
	struct node* right;
} NODE;

NODE* createTree(NODE* left, const char* dataPtr, NODE* right);
void destroyTree(NODE* node);
char* treeData(NODE* node);

bool hasChild(NODE* node);
double evaluate(NODE* node);
