#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct _queueNode {
	char data;
	struct _queueNode *nextNode;
};

typedef struct _queueNode queueNode;
typedef queueNode* queueNodePtr;

void printQueue(queueNodePtr currentPtr);
int isEmpty(queueNodePtr headPtr);
char dequeue(queueNodePtr *headPtr, queueNodePtr *tailPtr);
void enqueue(queueNodePtr *headPtr, queueNodePtr *tailPtr, char value);
void instructions();

void instructions()
{
	printf("Enter your choice: \n");
	printf("\t1 to add an item to the queue \n");
	printf("\t2 to remove an item from the queue \n");
	printf("\t3 to end\n");
}

int isEmpty(queueNodePtr headPtr)
{
	return headPtr == NULL;
}

void printQueue(queueNodePtr currentPtr)
{
	if (isEmpty(currentPtr)) {
		printf("Queue is empty\n\n");
	}
	else {
		printf("The queue is : \n");

		while (currentPtr != NULL) {
			printf("%c --> ", currentPtr->data);
			currentPtr = currentPtr->nextNode;
		}
		printf("NULL \n\n");
	}
}

void enqueue(queueNodePtr *headPtr, queueNodePtr *tailPtr, char value)
{
	queueNodePtr newNode;

	newNode = malloc(sizeof(queueNode));

	if (newNode != NULL) {
		newNode->data = value;
		newNode->nextNode = NULL;

		if (isEmpty(*headPtr)) {
			*headPtr = newNode;
		}
		else {
			(*tailPtr)->nextNode = newNode;
		}

		*tailPtr = newNode;
	}
	else {
		printf("%c is not inserted. No memory available.\n", value);
	}
}

char dequeue(queueNodePtr *headPtr, queueNodePtr *tailPtr)
{
	char value;
	queueNodePtr tempPtr;

	value = (*headPtr)->data;
	tempPtr = *headPtr;
	*headPtr = (*headPtr)->nextNode;
	
	if (*headPtr == NULL) {
		*tailPtr = NULL;
	}

	free(tempPtr);
	return value;
}

int main()
{
	queueNodePtr headPtr = NULL;
	queueNodePtr tailPtr = NULL;
	int choice;
	char item;

	instructions();
	printf("? ");
	scanf("%d", &choice);

	while (choice != 3) {
		switch (choice) {
		case 1:
			while (!getchar());
			printf("Enter a character: ");
			item = getchar();
			enqueue(&headPtr, &tailPtr, item);
			printQueue(headPtr);
			break;
		case 2:
			while (!getchar());
			if (!isEmpty(headPtr)) {
				item = dequeue(&headPtr, &tailPtr);
				printf("%c has been dequeued \n", item);
			}
			printQueue(headPtr);
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
	return 0;
}