#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main(void)
{	//구조체
	char name[10];
	char student_number[9];
	int grade;
	char major[20];
	int count = 0;
	char search_number[9];

	FILE *fPtr;
	char buffer[20];

	if((fPtr = fopen("student_file.txt", "w")) == NULL) {
		printf("Can't open that file\n");
	}
	else {
		while (count < 5) {
			printf("Name Student_number Grade Major: ");
			scanf("%s %s %d %s", name, student_number, &grade, major);
			fprintf(fPtr, "%s %s %d %s\n", name, student_number, grade, major);
			count++;
		}
	}
	fclose(fPtr);

	printf("Insert the student number to find: ");
	scanf("%s", search_number);

	//다시열고 다 데이터 받아서 찾으면 출력
	if ((fPtr = fopen("student_file.txt", "r")) == NULL) {
		printf("Can't read that file\n");
	}
	else { //문자열 비교
		do {
			fscanf(fPtr, "%s", buffer);
			if (!strcmp(buffer, search_number)) { //찾는 곳으로 fPtr이 갔으면 루프해제
				break;
			}
		} while (1);

		fscanf(fPtr, "%s", buffer);
		fscanf(fPtr, "%s", buffer);
		printf("The major of student with ID %s is %s", search_number, buffer);
	}
	
	fclose(fPtr);
	return 0;
}
