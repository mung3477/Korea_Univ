#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct _treeNode {
	struct _treeNode *leftPtr;
	int data;
	struct _treeNode *rightPtr;
};

typedef struct _treeNode treeNode;
typedef treeNode* treeNodePtr;

void insertNode(treeNodePtr *treePtr, int value);
void inOrder(treeNodePtr treePtr);
void preOrder(treeNodePtr treePtr);
void postOrder(treeNodePtr treePtr);

int main(void)
{
	int i, item;
	treeNodePtr rootPtr = NULL;

	srand(time(NULL));
	printf("The numbers being placed in the tree are:\n");

	for (i = 1; i <= 10; i++) {
		item = rand() % 15;
		printf("%3d", item);
		insertNode(&rootPtr, item);
	}

	printf("\n\nThe preorder traversal is:\n");
	preOrder(rootPtr);

	printf("\n\nThe inorder traversal is:\n");
	inOrder(rootPtr);

	printf("\n\nThe postorder traversal is:\n");
	postOrder(rootPtr);

	return 0;
}

void insertNode(treeNodePtr *treePtr, int value)
{

	if (*treePtr == NULL) {								//비어있으면 
		*treePtr = malloc(sizeof(treeNode));

		if (*treePtr != NULL) {
			(*treePtr)->data = value;
			(*treePtr)->leftPtr = NULL;
			(*treePtr)->rightPtr = NULL;
		}
		else {
			printf("%d is not inserted. No memeory available.\n", value);
		}
	}
	else {
		if (value < (*treePtr)->data) {										//작으면 왼쪽 트리로
			insertNode(&(*treePtr)->leftPtr, value);
		}
		else if (value > (*treePtr)->data) {								//크면 오른쪽 트리로
			insertNode(&(*treePtr)->rightPtr, value);
		}
		else {

			printf("dup");
		}
	}
}

void inOrder(treeNodePtr treePtr)
{
	if (treePtr != NULL) {
		inOrder(treePtr->leftPtr);
		printf("%3d", treePtr->data);
		inOrder(treePtr->rightPtr);
	}
}

void preOrder(treeNodePtr treePtr)
{
	if (treePtr != NULL) {
		printf("%3d", treePtr->data);
		preOrder(treePtr->leftPtr);
		preOrder(treePtr->rightPtr);
	}
}

void postOrder(treeNodePtr treePtr)
{
	if (treePtr != NULL) {
		postOrder(treePtr->leftPtr);
		postOrder(treePtr->rightPtr);
		printf("%3d", treePtr->data);
	}
}