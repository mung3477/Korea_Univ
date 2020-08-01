#pragma once
#include <stdio.h>
#include <stdbool.h>
#define STR_MAX 16

typedef struct treeNode
{
	char data[STR_MAX];
	struct treeNode* left;
	struct treeNode* right;
} TREE_NODE;

TREE_NODE* createTree(TREE_NODE* left, const char* dataPtr, TREE_NODE* right);
void destroyTree(TREE_NODE *node);
char* treeData(TREE_NODE* node);
bool hasChild(TREE_NODE* node);

TREE_NODE* buildDummyTree();