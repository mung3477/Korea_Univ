#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main(void)
{
	int occur = 0, wordcount = 0;
	char filename[30] = { 0 }, target[30] = { 0 }, buffer[30] = { 0 };
	FILE *fp;

	printf("Enter the file name and word: ");
	scanf("%s %s", filename, target);

	if ( (fp = fopen(filename, "r")) == NULL ) {	//못 열면
		printf("Can't open the file.");
	}
	else {											//열면
		while (!feof(fp)) {							//파일 끝까지
			fscanf(fp, "%s", buffer);
			if (!(strcmp(target, strtok(buffer, " \".,\n")))) { //타겟 찾으면
				occur++;							//occur 1 증가
			}
			wordcount++;
		}

		printf("The finding ratio : %d/%d", occur, wordcount - 1); //마지막에 crtl+z 세느라 한 번 더 작동
	}
	
	fclose(fp);
	return 0;
}
