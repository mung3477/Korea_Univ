/*generic stack*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct StackNode {
	void* data;
	struct StackNode* next;
} StackNode;

typedef struct Stack{
	int count;
	StackNode* top;
} Stack;

Stack* CreateStack(void)
{
	Stack* pStack = (Stack*)malloc(sizeof(Stack));
	if (pStack == NULL) {
		printf("Memory is full.\n");
		return pStack;
	}
	pStack->count = 0;
	pStack->top = NULL;
	return pStack;
}

void push(Stack* pStack, void* data)
{
	if(pStack == NULL) {
		printf("There's no stack.\n");
		return;
	}
	
	StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
	if (newNode == NULL) {
		printf("Memory is full.\n");
		return;
	}
	
	pStack->count++;
	newNode->data = data;
	newNode->next = NULL;
	
	if(pStack->top == NULL) {
		pStack->top = newNode;
		return;
	}
	else{
		newNode->next = pStack->top;
		pStack->top = newNode;
		return;
	}
}

void* pop(Stack* pStack) 
{
	if(pStack == NULL) {
		printf("There is no stack.\n");
		return NULL;
	}
	if(pStack->top == NULL) {
		printf("Stack is empty.\n");
		return NULL;
	}
	
	StackNode* delNode = pStack->top;
	void* data = delNode->data;
	pStack->top = delNode->next;
	free(delNode);
	pStack->count--;
	return data;
}

void* Stack_top(Stack* pStack) 
{
	if(pStack == NULL) {
		printf("There is no stack.\n");
		return NULL;
	}
	if(pStack->top == NULL) {
		printf("The stack is empty.\n");
		return NULL;
	}
	return pStack->top->data;
}

void DestroyStack(Stack *pStack)
{
	StackNode* currentNode = NULL;
	while(pStack->top != NULL) {
		currentNode = pStack->top;
		pStack->top = currentNode->next;
		free(currentNode);
	}
	free(pStack);
	printf("Done!\n");
}

void CatStack(Stack *pStack, Stack *p2Stack)
{
	pStack->count += p2Stack->count;
	StackNode* currentNode = p2Stack->top;
	while(currentNode->next != NULL) {
		currentNode = currentNode->next;
	}
	currentNode->next = pStack->top;
	pStack->top = p2Stack->top;
	free(p2Stack);
}

void showStack(Stack *pStack)
{
	StackNode* currentNode = pStack->top;
	printf("Top-");
	while(currentNode != NULL){
		printf("%c->", *(char*)currentNode->data);
		currentNode = currentNode->next;
	}
	printf("Bottom\n");
}


int isEmpty(Stack *pStack)
{
	if(pStack->top == NULL) return 1;
	else return 0;
}

int main(void)
{
	char a;
	char *b = NULL;
	
	Stack* stack1 = CreateStack();
	
	do{
		scanf("%c", &a);
		if(strchr("(){}[]", a) != NULL) {
			char *t = (char*)malloc(sizeof(char));
			*t = a;
			switch(*t) {
				case '(':
				case '{':
				case '[':
					push(stack1, t);
					break;
				case ')':
					if (isEmpty(stack1) || *(char*)pop(stack1) != '(') {
 						printf("no");
						return 0;
					}
					break;
				case '}':
					if (isEmpty(stack1) || *(char*)pop(stack1) != '{') {
						printf("no");
						return 0;
					}
					break;
				case ']':
					if (isEmpty(stack1) || *(char*)pop(stack1) != '[') {
						printf("no");
						return 0;
					}
					break;
			}
		}
	}while(a != '.');
	
	if(!isEmpty(stack1)){
		printf("no");
		return 0;
	}
	
	printf("yes");
	return 0;
}
