#include <stdio.h>

int stringLength(char* strptr)
{
	static int i = 0;
	if (*strptr  == NULL) return i;
	else{
		i++;
		strptr += 1;
		return stringLength(strptr);
	}
}

int palindrome(char word[], int len, int i)
{	
	if (i >= len - 1 - i) return 1;
	if (word[i] != word[len - 1 - i]) return 0;
	else return palindrome(word, len, ++i);
}

int main(void)
{
	char word[100];
	scanf("%s", word);
	char* strptr = word;
	int len = stringLength(strptr);
	
	if (palindrome(word, len, 0)) printf("The string is palindrome\n");
	else printf("The string is not palindrome\n");
	return 0;
}
