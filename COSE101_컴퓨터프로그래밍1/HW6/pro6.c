#include <stdio.h>

int checkCase(char cha);
void convertCharCase(char *sPtr);

int main(void)
{
	printf("Original String 1 : \n");
	char string[] = "PoINteR is vERy ImPorTAnt in C pRoGraMMing, SO STudEnt nEEd tO pRACtiCe usING poINTer";
	printf("%s\n\n", string);
	int i = 0;

	while (*(string + i) != '\0') {
		convertCharCase(string + i);
		i++;
	}
	printf("Converted String 2 :\n");
	printf("%s", string);
}

void convertCharCase(char *sPtr)
{
	if (!(checkCase(*sPtr))) { //0이면 , 대문자이면
		*sPtr = *sPtr - 'A' + 'a';
	}

	else if (checkCase(*sPtr) == 1) { 
		*sPtr = *sPtr - 'a' + 'A';
	}
}

int checkCase(char cha) //1이면 소문자, 0이면 대문자, 2이면 특수문자
{
	if ('a' < cha && cha < 'z')
		return 1;


	else if ('A' < cha && cha < 'Z')
		return 0;

	else
		return 2;
}