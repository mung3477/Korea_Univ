/*generic stack*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char infix[10000];
char postfix[10000];

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
	char in;
	char* t = NULL;
	char operators[6] = "+-*/()"; 
	int i = 0, j = 0;
	Stack* stack1 = CreateStack();
	
	scanf("%s", infix);
	
	/*making infix expression to postfix expression*/
	
	while(infix[i]) {
		
		t = (char*)malloc(sizeof(char));
		*t = infix[i];
		
		//If infix[i] is operator
		if (strchr(operators, infix[i]) != NULL) {
			//If stack is empty, push operator
			if(isEmpty(stack1)) {
				push(stack1, t);
			}
			//If stack is not empty, compare precedence
			else{
				switch(infix[i]) {
					case '*':
					case '/':
							//if my precedence is higher, push
							 if (strchr("+-(", *(char*)Stack_top(stack1))){
							 	push(stack1, t);
							 }
							 //if my precedence is same or lower, pop and print, then push
							 else {
							 	postfix[j++] = *(char*)pop(stack1);
							 	push(stack1 ,t);
							 }
							 break;
					case '+':
					case '-':
							//if my precedence is higher, push
							 if (strchr("(", *(char*)Stack_top(stack1))){
							 	push(stack1, t);
							 }
							 //if my precedence is same or lower, pop and print, then push
							 else {
							 	postfix[j++] = *(char*)pop(stack1);
							 	push(stack1 ,t);
							 }
							 break;
					case '(':
							push(stack1, t);
							break;
					case ')':
							while(*(char*)Stack_top(stack1) != '(') {
								postfix[j++] = *(char*)pop(stack1);
							}
							pop(stack1);
							break;			
				}
			}
		}
		//If infix[i] is operand
		else{
			postfix[j++] = infix[i];
		}
		i++;
	}
	
	while(!isEmpty(stack1)) {
		postfix[j++] = *(char*)pop(stack1);
	}
	postfix[j] = '\0';
	printf("%s\n", postfix);

	/*evaluating postfix expression*/
	i = 0;
	double operand1 = 0, operand2 = 0;
	double* dp = NULL;
	
	while(postfix[i]){
		//If postfix[i] is an operator
		if (strchr(operators, postfix[i]) != NULL) {
			
			t = (char*)malloc(sizeof(char));
			dp = (double*)malloc(sizeof(double));
			
			//Check whether there's enough operands
			if(stack1->count < 2){
				printf("INVALID_FORMULA\n");
				return 0;
			}
			
			operand2 = *(double*)pop(stack1);
			operand1 = *(double*)pop(stack1);
			
			switch(postfix[i]) {
				case '+':
					*dp = operand1 + operand2;
					push(stack1, dp);
					break;
				case '-':
					*dp = operand1 - operand2;
					push(stack1, dp);
					break;
				case '*':
					*dp = operand1 * operand2;
					push(stack1, dp);
					break;
				case '/':
					//Check if there is division by zero
					if(operand2 == 0) {
						printf("DIVIDED_BY_ZERO\n");
						return 0;
					}
					
					*dp = operand1 / operand2;
					push(stack1, dp);
					break;
			}
		}
		//If postfix[i] is an operand
		else{
			dp = (double*)malloc(sizeof(double));
			*dp = (double)(postfix[i] - '0');
			push(stack1, dp);
		}
		i++;
	}
	if(stack1->count > 1) {
		printf("INVALID_FORMULA\n");
		return 0;
	}
	printf("%.2f", *(double*)Stack_top(stack1));
	return 0;
}
