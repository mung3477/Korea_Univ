#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hashADT.h"

HASH_BUCKET* bucketCreate(size_t bucketSize)
{
	HASH_BUCKET* bucket = (HASH_BUCKET*)malloc(sizeof(HASH_BUCKET));
	if (!bucket) return NULL;

	bucket->max = bucketSize;
	bucket->size = 0;
	bucket->next = NULL;
	bucket->values = (int*)calloc(bucketSize, sizeof(int));

	return bucket;
}

HASH* hashCreate(size_t hashSize, size_t bucketSize, int(*hashKey)(int))
{
	HASH* pHash = (HASH*)malloc(sizeof(HASH));
	if (pHash) {
		pHash->bucketSize = bucketSize;
		pHash->hashSize = hashSize;
		pHash->getMyAddr = hashKey;
		pHash->buckets = (HASH_BUCKET**)malloc(sizeof(HASH_BUCKET*) * hashSize);
		//fill pointer array
		for (int i = 0; i < pHash->hashSize; i++) {
			pHash->buckets[i] = bucketCreate(pHash->bucketSize);
		}
	}
	
	return pHash;
}

void hashInsert(HASH* pHash, int* pList, size_t listSize)
{	
	for (int i = 0; i < listSize; i++) {
		int key = pHash->getMyAddr(pList[i]);
		HASH_BUCKET* curBuck = pHash->buckets[key];
		while (curBuck->size >= curBuck->max) {
			if (curBuck->next != NULL) {
				curBuck = curBuck->next;
			}
			else {
				curBuck->next = bucketCreate(pHash->bucketSize);
			}
		}
		curBuck->values[curBuck->size] = pList[i];
		(curBuck->size)++;
	}
}

void hashDelete(HASH* pHash)
{
	for (int i = 0; i < pHash->hashSize; i++) {
		HASH_BUCKET* p = pHash->buckets[i];
		HASH_BUCKET* q = NULL;
		while (p->next) {
			q = p;
			p = p->next;
			free(p);
		}
		free(p);
	}

	free(pHash->buckets);
	free(pHash);
}

bool hashSearch(HASH* pHash, const int target)
{
	bool found = false;
	int key = pHash->getMyAddr(target);
	HASH_BUCKET* curBuck = pHash->buckets[key];
	int buckInd = 0;
	int index = 0;
	if (found) {
		printf("FOUND %d at (Key: %d, Bucket: %d, Index: %d)\n", target, key, buckInd, index);
	}
	else {
		printf("Could not find %d", key);
	}
	return found;
}
