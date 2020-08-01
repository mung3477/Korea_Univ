#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct QUEUE
{
	void** nodes;
	int front;
	int rear;
	int count;
	int queueSize;
} QUEUE;

QUEUE* createQueue(int queueSize);
void destroyQueue(QUEUE* queue);

bool dequeue(QUEUE* queue);
bool enqueue(QUEUE* queue, void* dataPtr);
bool queueFront(QUEUE* queue, void** dataPtr);
bool queueRear(QUEUE* queue, void** dataPtr);
int queueCount(QUEUE* queue);

bool isEmpty(QUEUE* queue);
bool isFull(QUEUE* queue);

int getNextIndex(QUEUE* queue, int cur);
int getPrevIndex(QUEUE* queue, int cur);

void printQueueStatus(QUEUE* queue);
