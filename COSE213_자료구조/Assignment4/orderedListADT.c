#include "orderedListADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


LIST* createList(int(*compare)(void* pArg1, void* pArg2))
{
	LIST* pList = (LIST*)malloc(sizeof(LIST));
	if(pList == NULL) {
		printf("There isn't enouth memeory.\n");
		return NULL;
	}
	pList->size = 0;
	pList->head = pList->pos = pList->rear = NULL;
	pList->compare = cmpStudentId;
	
	return pList;
}

void destroyList(LIST* pList)
{
	if(pList == NULL) {
		printf("There's no list'.\n");
		return;
	}
	else if (isEmpty(pList)) {
		free(pList);
		return;
	}
	
	NODE* curNode = pList->head;
	NODE* tempNode = NULL;
	
	while(curNode != pList->rear) {
		tempNode = curNode;
		curNode = curNode->next;
		free(tempNode);
	}
	
	free(curNode);
	free(pList);
}

bool insert(LIST* pList, void* pDataIn)
{
	NODE* pPre;
	NODE* pLoc;
	if(_search(pList, &pPre, &pLoc, pDataIn)) {
		printf("Already there's that data.\n");
		return false;
	}
	else {
		if(!_insert(pList, pPre, pDataIn)) {
			return false;
		}
		else {
			return true;
		}
	}
}

bool myremove(LIST* pList, void* pKey)
{
	NODE* pPre;
	NODE* pLoc;
	if(!_search(pList, &pPre, &pLoc, pKey)) {
		//Erase failed.
		return false;
	}
	else {
		_delete(pList, pPre, pLoc);
		return true;
	}
}

bool retrieve(LIST* pList, void* pKey, void** pDataOut)
{
	NODE* pPre;
	NODE* pCur;

	if (_search(pList, &pPre, &pCur, pKey))
	{
		*pDataOut = pCur->pData;
		return true;
	} else
	{
		*pDataOut = NULL;
		return false;
	}
}

int size(LIST* pList) 
{
	return pList->size;
}


bool isEmpty(LIST* pList)
{
	if(pList->size == 0)
		return true;
	else
		return false;
}

bool iterate(LIST* pList, void** pDataOut)
{
	if (pList == NULL) {
		printf("There's no list.\n");
		return false;
	}
	
	if(isEmpty(pList)) {
		//printf("List is empty.\n");
		return false;
	}
	
	if(pList->pos == NULL) {
		return false;
	}
	else {
		*pDataOut = pList->pos->pData;
		pList->pos = pList->pos->next;
		return true;
	}

}

void initIterator(LIST* pList)
{
	pList->pos = pList->head;
}

void printList(LIST* pList, void(*print)(void* pArg))
{
	STUDENT* curStudent;
	NODE* t = pList->pos;
	initIterator(pList);
	
	while(iterate(pList, (void**)&curStudent))
		printStudent(curStudent);
	pList->pos = t;
	
	printf("================\n");
}

void printStudent(void* pArg)
{
	printf("STUDENT ID: %d\n", ((STUDENT*)pArg)->id);
	printf("NAME: %s\n", ((STUDENT*)pArg)->name);
	printf("EMAIL: %s\n", ((STUDENT*)pArg)->email);
	printf("----------------\n");
}

int cmpStudentId(void* pStudent1, void* pStudent2)
{
	if (((STUDENT*)pStudent1)->id > ((STUDENT*)pStudent2)->id)
		return 1;
		
	else if (((STUDENT*)pStudent1)->id == ((STUDENT*)pStudent2)->id)
		return 0;
		
	else
		return -1;
}

static bool _insert(LIST* pList, NODE* pPre, void* pDataIn)
{
	STUDENT* newStudent = (STUDENT*)pDataIn;
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	if(newNode == NULL) {
		printf("There isn't enough memeory.\n");
		return false;
	}
	
	newNode->pData = newStudent;
	
	if(pPre == NULL) {
		pList->head = pList->pos = pList->rear = newNode;
		newNode->next = NULL;
		pList->size++;
	}
	else {
		newNode->next = pPre->next;
		pPre->next = newNode;
		pList->size++;
	}
	while(pList->rear->next != NULL) {
		pList->rear = pList->rear->next;
	}
	return true;
}

static void _delete(LIST* pList, NODE* pPre, NODE* pCur)
{
	//printf("Deletion start\n");
	
	//remove first elelemt
	if(pPre == NULL) {
		pList->head = pList->head->next;
		free(pCur);	
	}
	
	//remove last element
	else if(pCur->next == NULL){
		pList->rear = pPre;
		pPre->next = NULL;
		free(pCur);
	}
	
	//general case
	else{
		pPre->next = pCur->next;
		free(pCur);
	}
	
	pList->size--;
}

static bool _search(LIST* pList, NODE** pPre, NODE** pLoc, void* pKey)
{
#define COMPARE (((*pList->compare)(pKey, (*pLoc)->pData)))
#define COMPARE_LAST ((*pList->compare) (pKey, pList->rear->pData))
	//if return == false : insert the key. Else, don't insert the key.
	//printf("search start\n");
	int result;
	*pPre = NULL;
	*pLoc = pList->head;
	if (pList->size == 0) {
		return false;
	}
	
	if (COMPARE_LAST > 0)
	{
		*pPre = pList->rear;
		*pLoc = NULL;
		return false;
		//pLoc == NULL : insert the key at the rear of list
	}

	while ((result = COMPARE) > 0)
	{
		*pPre = *pLoc;
		*pLoc = (*pLoc)->next;
	}
	//pPre will point the position to insert the key

	if (result == 0)				//true : key is already at pLoc
		return true;
	else
		return false;				//false : insert the key at pPre
}


