#define _CRT_SECURE_NO_WARNINGS

#include "queueADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_SIZE 5

int main()
{
	QUEUE* queue = createQueue(QUEUE_SIZE);

	dequeue(queue);

	for (int i = 0; i < 10; i++)
	{
		char* str = (char*)malloc(sizeof(char) * 10);
		sprintf(str, "%d", i);
		enqueue(queue, (void*)str);
	}

	printQueueStatus(queue);

	dequeue(queue);
	dequeue(queue);

	printQueueStatus(queue);

	for (int i = 10; i < 20; i++)
	{
		char* str = (char*)malloc(sizeof(char) * 10);
		sprintf(str, "%d", i);
		enqueue(queue, (void*)str);
	}

	printQueueStatus(queue);

	destroyQueue(queue);

	return 0;
}
