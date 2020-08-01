#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifdef _MSC_VER
// Windows
#include <Windows.h>
#else
// Linux
#include <time.h>
#endif

#define N 100000
#define MAX_VALUE 10000

typedef struct Node {
	int data;
	struct Node* prevNode;
	struct Node* collided_next;
} Node;

typedef struct hashHeader {
	int size;
	Node* hashTable[67567];
} hashHeader;

void runSearch(void* pList, const size_t size, const int target, int* pLoc, bool(*searchFunc)(void*, const size_t, const int, int*))
{
	LARGE_INTEGER freq;
	LARGE_INTEGER beginTime;
	LARGE_INTEGER endTime;

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&beginTime);
	bool result = searchFunc(pList, size, target, pLoc);
	QueryPerformanceCounter(&endTime);

	double duringTime = (double)(endTime.QuadPart - beginTime.QuadPart) / (double)freq.QuadPart;

	printf("Execution time: %.10lf ms\n", duringTime * 10e3);
	if (result)
		printf("Found %d at %d\n", target, *pLoc);
	else
		printf("Cannot found %d\n", target);
}

bool seqSearch(void* pList, const size_t size, const int target, int* pLoc)
{
	unsigned int i = 0;
	int* arr = (int*)pList;
	while (i < size && arr[i] != target)
	{
		i++;
	}
	*pLoc = i;

	return (arr[i] == target);
}

int getRand()
{
	return rand() % MAX_VALUE;
}

int hashFunc(int data)
{
	return data % 67567;
}

hashHeader* createHash()
{
	hashHeader* newHash = (hashHeader*)malloc(sizeof(hashHeader));
	if (newHash == NULL) return NULL;
	newHash->size = 0;
	return newHash;
}

Node* traverse_to_end(Node* curNode, int data) {
	while (curNode->collided_next != NULL) {
		if (curNode->data == data) {
			curNode = NULL;
			break;
		}
		curNode = curNode->collided_next;
	}
	return curNode;
}

void buildHash(void* pList, size_t listSize, void* pHash, size_t* hashSize)
{
	for (int i = 0; i < 67567; i++) {
		((hashHeader*)pHash)->hashTable[i] = NULL;
	}

	//fill hashTable
	for (int i = 0; i < listSize; i++) {
		int data = ((int*)pList)[i];
		int index = hashFunc(data);

		//1st used index
		if (((hashHeader*)pHash)->hashTable[index] == NULL) {
			Node* newNode = (Node*)malloc(sizeof(Node));
			newNode->data = data;
			newNode->prevNode = NULL;
			newNode->collided_next = NULL;
			((hashHeader*)pHash)->hashTable[index] = newNode;
			(((hashHeader*)pHash)->size)++;
		}

		//collision
		else {
			Node* newNode = (Node*)malloc(sizeof(Node));
			newNode->data = data;
			newNode->collided_next = NULL;

			Node* curNode = traverse_to_end(((hashHeader*)pHash)->hashTable[index], data);
			if (curNode) {
				curNode->collided_next = newNode;
				newNode->prevNode = curNode;
			}
		}
	}

	*hashSize = (((hashHeader*)pHash)->size);
}

bool hashSearch(void* pHash, const size_t size, const int target, int* pLoc)
{
	int index = hashFunc(target);
	Node* curNode = (((hashHeader*)pHash)->hashTable)[index];
	bool found = false;

	if (curNode == NULL) return found;

	while (1) {
		if (curNode->data == target) {
			found = true;
			break;
		}
		else {
			if (curNode->collided_next != NULL) {
				curNode = curNode->collided_next;
			}
			else { break; }
		}
	}

	return found;
}

void deleteHash(void* pHash, const size_t size)
{
	for (int i = 0; i < 67567; i++) {
		Node* curNode = ((hashHeader*)pHash)->hashTable[i];
		if (curNode) {
			while (curNode->collided_next != NULL) {
				Node* tempNode;
				tempNode = traverse_to_end(curNode, -1);
				tempNode->prevNode->collided_next = NULL;
				free(tempNode);
			}
			free(curNode);
		}
	}
	
	free(pHash);
}

int main()
{
	static int arr[N] = { 0 };

	srand(2019);
	for (int i = 0; i < N; i++)
	{
		arr[i] = getRand();
	}

	int target = getRand();
	int loc = -1;

	size_t hashSize = 0;
	hashHeader* pHash = createHash();

	buildHash(arr, N, (void*)pHash, &hashSize);

	runSearch(arr, N, target, &loc, seqSearch);

	runSearch(pHash, hashSize, target, &loc, hashSearch);

	deleteHash(pHash, hashSize);
	return 0;
}