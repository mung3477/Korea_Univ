#define _CRT_SECURE_NO_WARNINGS

#include "stackADT.h"
#include "stackADT.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define STR_MAX 256

bool braceCheck(const char* str)
{
	STACK *pStack = createStack();
	if(pStack == NULL) return false;
	
	int i = 0;
	char* j;
	j = strstr(str, "/*");
	if(j != NULL) {
		int t;
		for(t = 0; t < STR_MAX - 1; t++) {
			if (j[0] == str[t] && j[1] == str[t+1]) {
				break;
			}
		}
		
		char* k;
		k = strstr(str, "*/");
		if(k == NULL) return false;
		int y;
		for(y = 0; y < STR_MAX; y++) {
			if (k[0] == str[y] && k[1] == str[y+1]) {
				break;
			}
		}
		if(y - t <= 1) {
		char* s;
		s = strstr(k, "*/");
		if(s == NULL) return false;
		for(y = 0; y < STR_MAX; y++) {
			if (s[0] == str[y] && s[1] == str[y+1]) {
				break;
			}
		}
		}
		printf("%d %d\n", t, y);
		if(y > t) return false;
		int p;
		for(p = y+1; p < t; p++) {
			if(strchr("(){}[]",str[p]) != NULL) return false; 
		}
	}
	
	while(str[i]) {
		char *t = (char*)malloc(sizeof(char));
		*t = str[i];
		
		if(strchr("({[", str[i]) != NULL) {
			pushStack(pStack, t);
		}
		else if (strchr(")}]", str[i]) != NULL) {
			switch(str[i]) {
				case ')':
					if(!isEmpty(pStack)) {
						while(*(char*)stackTop(pStack) != '(') {
							if(strchr("{[", *(char*)stackTop(pStack))) {
								return false;
							}
							else popStack(pStack);
							if(isEmpty(pStack)) return false;
						}
						popStack(pStack);
					}
					break;
				
				case '}':
					if(!isEmpty(pStack)) {
						while(*(char*)stackTop(pStack) != '{') {
							if(strchr("([", *(char*)stackTop(pStack))) {
								return false;
							}
							else popStack(pStack);
							if(isEmpty(pStack)) return false;
						}
						popStack(pStack);
					}
					break;
					
				case ']':
					if(!isEmpty(pStack)) {
						while(*(char*)stackTop(pStack) != '[') {
							if(strchr("{(", *(char*)stackTop(pStack))) {
								return false;
							}
							else popStack(pStack);
							if(isEmpty(pStack)) return false;
						}
						popStack(pStack);
					}
					break;
			}
		}
		i++;
	}
	if (isEmpty(pStack)) return true;
	else return false;
}

int main(void)
{
	char str[STR_MAX];
	printf("Enter a string: \n");

	while (true)
	{
		scanf("%s", str);
		if (strcmp(str, "exit") == 0)
		{
			break;
		}

		if (braceCheck(str))
		{
			printf("Yes\n");
		}
		else
		{
			printf("No\n");
		}

	}

	return 0;
}
