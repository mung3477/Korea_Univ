#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main(void)
{
	char file_read[15], file_write[15], buffer[50];

	printf("Enter the name of file to read: ");
	scanf("%s", &file_read);
	printf("Enter the name of file to write: ");
	scanf("%s", &file_write);

	FILE *fp = fopen(file_read, "r");
	FILE *fp2 = fopen(file_write, "w");

	while (!(feof(fp))) { //파일 끝날 때까지
		fgets(buffer, 50, fp); //\n까지 입력받기 위해 fgets
		if (buffer[0] != '\n') {// buffer가 비어있지 않다면
			fputs(buffer, fp2);
		}
	}

	printf("Copy txt complete!");

	fclose(fp);
	fclose(fp2);
	return 0;
}
