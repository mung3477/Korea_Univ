#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queueADT.h"

QUEUE* createQueue(int queueSize)
{
	QUEUE* queue = (QUEUE*)malloc(sizeof(QUEUE));

	if (queue == NULL) return NULL;

	queue->front = 0;
	queue->rear = -1;
	queue->count = 0;
	queue->queueSize = queueSize;
	queue->nodes = (void**)malloc(sizeof(void*) * queueSize);

	return queue;
}

void destroyQueue(QUEUE* queue)
{
	// Write your code here.
}

bool enqueue(QUEUE* queue, void* dataPtr)
{
	if(isFull(queue)) {
		printf("%s cannot be enqueued (Queue is full)\n", *(char*)dataPtr)
	}
	else {
		queue->nodes[++(queue->rear)] = dataPtr;
	}
}

bool dequeue(QUEUE* queue)
{
	if(isEmpty(queue)) return false;
	
}

bool isFull(QUEUE* queue)
{
	if(queue->rear + 1 == queue->front) return true;
	else return false;
}

bool queueFront(QUEUE* queue, void** dataPtr)
{
	if (isEmpty(queue))
	{
		dataPtr = NULL;
		return false;
	}

	*dataPtr = queue->nodes[queue->front];
	return true;
}

bool queueRear(QUEUE* queue, void** dataPtr)
{
	if (isEmpty(queue))
	{
		dataPtr = NULL;
		return false;
	}

	*dataPtr = queue->nodes[queue->rear];
	return true;
}

int queueCount(QUEUE* queue)
{
	return queue->count;
}

bool isEmpty(QUEUE* queue)
{
	return (queue->count == 0);
}

int getNextIndex(QUEUE* queue, int cur)
{
	return ++cur % queue->queueSize;
}

int getPrevIndex(QUEUE* queue, int cur)
{
	return (--cur + queue->queueSize) % queue->queueSize;
}

void printQueueStatus(QUEUE* queue)
{
	char* str = NULL;
	printf("##############################\n# Queue Status\n");
	printf("- Queue size: %d\n", queue->queueSize);
	printf("- Num of elements: %d\n", queue->count);
	if (queueFront(queue, (void**)&str))
	{
		printf("- Queue front(%d): %s\n", queue->front, str);
	}
	if (queueRear(queue, (void**)&str))
	{
		printf("- Queue rear(%d): %s\n", queue->rear, str);
	}
	printf("\n");
}
