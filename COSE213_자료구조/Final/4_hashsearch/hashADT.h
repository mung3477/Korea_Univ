#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct hashBucket
{
	int* values;	// Value list
	int size;		// Number of elements
	int max;		// Bucket capacity
	struct hashBucket* next;
}HASH_BUCKET;

typedef struct hash
{
	HASH_BUCKET** buckets;	// Bucket list
	size_t hashSize;		// Number of buckets
	size_t bucketSize;		// Number of elements in each bucket

	int(*getMyAddr)(int);	// return hashkey
}HASH;

HASH_BUCKET* bucketCreate(size_t bucketSize);
HASH* hashCreate(size_t hashSize, size_t bucketSize, int(*hashKey)(int));
void hashInsert(HASH* pHash, int* pList, size_t listSize);
void hashDelete(HASH* pHash);
bool hashSearch(HASH* pHash, const int target);
