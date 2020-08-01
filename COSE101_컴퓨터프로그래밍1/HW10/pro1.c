#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct _stackNode {
	int data;
	struct _stackNode *nextNode;
};

typedef struct _stackNode stackNode;
typedef stackNode* stackNodePtr;

void push(stackNodePtr *topPtr, int info);
int pop(stackNodePtr *topPtr);
int isEmpty(stackNodePtr topPtr);
void printStack(stackNodePtr currentPtr);
void instructions();

void instructions() {
	printf("Enter choice : \n");
	printf("\t 1 to push a value on the stack. \n");
	printf("\t 2 to pop a value off the stack. \n");
	printf("\t 3 to end program. \n");
}

int isEmpty(stackNodePtr topPtr) {
	return topPtr == NULL;
}

void printStack(stackNodePtr currentPtr) {
	if (currentPtr == NULL) {
		printf("Stack is empty. \n\n");
	}
	else {
		printf("The stack is : \n");

		while (currentPtr != NULL) {
			printf(" %d --> ", currentPtr->data);
			currentPtr = currentPtr->nextNode;
		}
		printf("NULL \n\n");
	}
}

void push(stackNodePtr *topPtr, int info)
{
	stackNodePtr newNode;

	newNode = malloc(sizeof(stackNode));

	if (newNode != NULL) {
		newNode->data = info;
		newNode->nextNode = *topPtr;
		*topPtr = newNode;
	}
	else {
		printf("%d is not inserted. No memory available.\n", info);
	}
}

int pop(stackNodePtr *topPtr)
{
	stackNodePtr tempPtr;
	int popValue;

	tempPtr = *topPtr;
	popValue = (*topPtr)->data;
	*topPtr = (*topPtr)->nextNode;
	free(tempPtr);
	return popValue;
}

void main() {
	stackNodePtr stackPtr = NULL;
	int choice;
	int value;

	instructions();
	printf("? ");
	scanf("%d", &choice);

	while (choice != 3) {
		switch (choice) {
		case 1:
			while (!getchar());
			printf("Enter a n integer: ");
			scanf("%d", &value);
			push(&stackPtr, value);
			printStack(stackPtr);
			break;
		case 2:
			while (!getchar());
			if (!isEmpty(stackPtr)) {
				printf("The popped value is %d. \n", pop(&stackPtr));
				printStack(stackPtr);
			}
			break;
		default:
			while (!getchar());
			printf("Invalid choice. \n\n");
			instructions();
			break;
		}
		printf("? ");
		scanf("%d", &choice);
	}
	printf("End of run. \n");
	return;
}