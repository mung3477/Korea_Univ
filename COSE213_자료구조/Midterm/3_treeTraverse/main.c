#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "binaryTreeADT.h"
#include "binaryTreeADT.c"
#include "stackADT.h"
#include "stackADT.c"

void dfs(TREE_NODE* rootNode)
{
	STACK* pStack = createStack();
	pushStack(pStack, rootNode);
	while(!isEmpty(pStack)) {
		TREE_NODE* temp = (TREE_NODE*)popStack(pStack);
		printf("%s\n", temp->data);
		
		if(temp->right != NULL) pushStack(pStack, temp->right);
		if(temp->left != NULL) pushStack(pStack, temp->left);
	
	}
	return;
}

int main()
{
	TREE_NODE* bt = buildDummyTree();

	dfs(bt);

	return 0;
}
