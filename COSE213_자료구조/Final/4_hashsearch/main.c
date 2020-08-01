#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hashADT.h"

#define N				100000
#define HASH_SIZE		997
#define BUCKET_SIZE		10
#define MAX_VALUE		100000

int getRand()
{
	return rand() % MAX_VALUE;
}

int getMyAddr(int value)
{
	return value % HASH_SIZE;
}

int main()
{
	// Ramdom value generating
	static int arr[N] = { 0 };

	srand(2019);
	for (int i = 0; i < N; i++)
	{
		arr[i] = getRand();
	}

	// Create Hash
	HASH* pHash = hashCreate(HASH_SIZE, BUCKET_SIZE, getMyAddr);
	hashInsert(pHash, arr, N);

	// Search
	for (int i = 0; i < 5; i++)
	{
		int target = getRand();
		hashSearch(pHash, target);
	}
	
	hashDelete(pHash);
	
	return 0;
}
