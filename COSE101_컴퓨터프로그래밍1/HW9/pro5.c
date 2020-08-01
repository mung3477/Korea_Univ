#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <windows.h>

struct employee {
	int employee_id;
	char *name;
};

void printMainMenu(void);
void Add(void);
void display(void);
void update(void);

int add_count = 0;

int main(void)
{
	printMainMenu();
	
	return 0;
}

void printMainMenu(void)
{
	while (1) {
		int choice = 0;

		system("cls");

		printf("===================================\n");
		printf("MENU:\n");
		printf("===================================\n");
		printf("1. Add a record\n");
		printf("2. Display the file\n");
		printf("3. Update the record\n");
		printf("4. Exit\n");
		printf("===================================\n");
		printf("Enter your choice: ");
		scanf(" %d", &choice);

		switch (choice) {
		case 1:
			Add();
			break;
		case 2:
			display();
			break;
		case 3:
			update();
			break;
		case 4:
			return;
			break;
		default:
			printf("\nError! Enter right number.");
			break;
		}
	}
}

void Add(void)
{
	int ID = 0;
	char name[25];
	FILE *fp;

	printf("\n");
	printf("ENTER THE EMPLOYEE ID :\n");
	scanf(" %d", &ID);
	printf("ENTER THE EMPLOYEE NAME :\n");
	scanf(" %[^\n]s", name);
	add_count++;

	if (add_count == 1) {
		fp = fopen("Employees.txt", "w");
		fprintf(fp, "%d %s\n", ID, name);
		fclose(fp);
	}
	else {
		fp = fopen("Employees.txt", "a");
		fprintf(fp, "%d %s\n", ID, name);
		fclose(fp);
	}
}

void display(void)
{
	int n = 0;
	int ID = 0;
	char name[25] = { 0 };
	struct employee employee;

	FILE *fp;
	fp = fopen("Employees.txt", "r");

	printf("===================================\n");
	printf("ID      NAME\n");
	printf("===================================\n");
	
	for (int i = 1; i <= add_count; i++) {
		fscanf(fp, " %d %[^\n]s", &ID, name);
		employee.employee_id = ID;
		employee.name = name;

		printf("%-8d%s\n", employee.employee_id, employee.name);
	}
	
	printf("===================================\n");
	fclose(fp);
	
	_getch();
}

void update(void)
{
	int targetID = 0, ID = 0;
	char newname[25] = { 0 }, name[25] = { 0 };

	printf("\n");
	printf("Enter THE EMPLOYEE ID FOR UPDATE :\n");
	scanf(" %d", &targetID);
	printf("ENTER THE EMPLOYEE NAME TO BE UPDATED :\n");
	scanf(" %[^\n]s", newname);

	FILE *fp, *fp2;

	if (fp = fopen("Employees.txt", "r")) {
		if (fp2 = fopen("Employees_temp.txt", "w")) {
			while (!feof(fp)) {
				ID = 0;
				fscanf(fp, " %d %[^\n]s", &ID, name);
				if (ID) {
					if (ID != targetID) {					//찾는게 아니면 그대로 temp에 복사
						fprintf(fp2, "%d %s\n", ID, name);
					}
					else if (ID == targetID) {									//찾는거면 수정해서 temp에 복사
						fprintf(fp2, "%d %s\n", ID, newname);
					}
				}
			} 
			fclose(fp);
			fclose(fp2);
		}
	}
	else
		printf("Error! Can't read the text file.\n");

	/*파일내용 복사*/
	if (fp = fopen("Employees.txt", "w")) {
		if (fp2 = fopen("Employees_temp.txt", "r")) {
			while (!feof(fp2)) {
				ID = 0;
				fscanf(fp2, " %d %[^\n]s", &ID, name);				//temp에서 한 줄 긁어옴

				if (ID)
					fprintf(fp, "%d %s\n", ID, name);				//원본에 복사
			} 
		}
		fclose(fp);
		fclose(fp2);
	}
	
}