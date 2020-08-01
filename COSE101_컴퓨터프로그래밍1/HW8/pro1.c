#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <string.h>

typedef struct class_grade {
	char name[30];
	long long int student_id;
	int attendance;
	int midterm_exam;
	int final_exam;
	int assignment;
	int term_project;
	int total_score;
} Grade;

Grade students[79] = { 0, };

int count = 0;
int attendance_arr[79];
int assignment_arr[79];
int midterm_arr[79];
int final_arr[79];
int termproj_arr[79];
int total_arr[79];

void mainmenu(void);
void Registered_student(void);
void Add_student(void);
void Class_report(void);
void Final_grade(void);
int average(int arr[]);
void sort(int arr[]);
int median(int arr[]);

int main(void)
{
	mainmenu();
	return 0;
}

void mainmenu(void)
{

	int menu;

	do {
		system("cls");
		printf("  COSE101 Grade Management System \n");
		printf("==================================\n");
		printf("1. View Registered Student\n");
		printf("2. Add Student\n");
		printf("3. Class Report\n");
		printf("4. View Final Grade\n");
		printf("5. Exit\n\n");
		printf("==================================\n");
		printf("Select Menu  : ");

		scanf_s(" %d", &menu);

		switch (menu) {
		case 1: 
			Registered_student();
			break;
		case 2:
			Add_student();
			break;
		case 3:
			Class_report();
			break;
		case 4:
			Final_grade();
			break;
		case 5:
			break;
		}
	} while (menu != 5);
}

void Registered_student(void)
{
	int input;

	system("cls");
	printf("==================================\n");
	printf("\t Registered Student\t\n");
	printf("==================================\n");

	if (!(students[0].name[0])) {
		printf("There are no registered students\n");
	}

	else {
		for (int i = 0; i < count; i++) {
			printf("%lld\t%s\n", students[i].student_id, students[i].name);
		}
	}

	printf("==================================\n");
	printf("Enter 1 to Go Back : ");
	scanf_s("%d", &input);

	if (input == 1) {

	}
	else {
		Registered_student();
	}
}

void Add_student(void)
{
	system("cls");

	printf("==================================\n");
	printf("Student Name : ");
	scanf(" %s", students[count].name);

	printf("Student ID : ");
	scanf("%lld", &students[count].student_id);
	printf("Attendence (0 ~ 10) : ");
	scanf(" %d", &students[count].attendance);
	printf("Assignment (0 ~ 10) : ");
	scanf(" %d", &students[count].assignment);
	printf("Midterm Exam (0 ~ 30) : ");
	scanf(" %d", &students[count].midterm_exam);
	printf("Final Exam (0 ~ 30) : ");
	scanf_s(" %d", &students[count].final_exam);
	printf("Term Project (0 ~ 20) : ");
	scanf_s(" %d", &students[count].term_project);

	students[count].total_score = students[count].attendance +
		students[count].assignment + students[count].midterm_exam +
		students[count].final_exam + students[count].term_project;

	count++;

	attendance_arr[count-1] = students[count-1].attendance;
	assignment_arr[count - 1] = students[count - 1].assignment;
	midterm_arr[count - 1] = students[count - 1].midterm_exam;
	final_arr[count - 1] = students[count - 1].final_exam;
	termproj_arr[count - 1] = students[count - 1].term_project;
	total_arr[count - 1] = students[count - 1].total_score;
	
	sort(attendance_arr);
	sort(assignment_arr);
	sort(midterm_arr);
	sort(final_arr);
	sort(termproj_arr);
	sort(total_arr);

}

void Class_report(void)
{
	int input;

	system("cls");
	printf("\t     Class report\n");
	printf("==================================\n");
	printf(" Field         Average | Median\n");
	printf("==================================\n");
	printf("Attendance  :    %2d    |     %2d\n", average(attendance_arr), median(attendance_arr));
	printf("Assignment  :    %2d    |     %2d\n", average(assignment_arr), median(assignment_arr));
	printf("Midterm     :    %2d    |     %2d\n", average(midterm_arr), median(midterm_arr));
	printf("Final       :    %2d    |     %2d\n", average(final_arr), median(final_arr));
	printf("Term Project:    %2d    |     %2d\n", average(termproj_arr), median(termproj_arr));
	printf("Total       :   %3d    |    %3d\n", average(total_arr), median(total_arr));
	printf("\n");
	printf("==================================\n");

	printf("Enter 1 to Go Back : ");
	scanf_s("%d", &input);

	if (input == 1) {

	}
	else {
		Class_report();
	}
}

void Final_grade(void)
{
	int input;

	system("cls");
	printf("==========================================\n");
	printf("             Final Grade\n");
	printf("==========================================\n");
	printf("StudentID       Total Score     Grade\n");
	for (int i = 0; i < count; i++) {
		char grade;
		if (students[i].total_score >= 90)
			grade = 'A';
		else if (80 <= students[i].total_score && students[i].total_score < 90)
			grade = 'B';
		else if (70 <= students[i].total_score && students[i].total_score < 80)
			grade = 'C';
		else
			grade = 'D';
		printf("%-9lld      %-3d             %c\n", students[i].student_id, students[i].total_score, grade);
	}
	printf("==========================================\n");
	printf("Enter 1 to Go Back : ");
	scanf_s("%d", &input);

	if (input == 1) {

	}
	else {
		Final_grade();
	}
}

int average(int arr[])
{
	int result = 0;
	for (int i = 0; i < count; i++) {
		result += arr[i];
	}
	result /= count;

	return result;
}

void sort(int arr[])
{
	for (int i = count - 1; i > 0; i--) {
		if (arr[i-1] < arr[i]) {
			int temp;
			temp = arr[i-1];
			arr[i-1] = arr[i];
			arr[i] = temp;
		}
	}
}

int median(int arr[])
{
	int result = 0;
	if (count % 2 == 0) {
		result = (arr[count / 2 - 1] + arr[count / 2]) / 2;
	}
	else {
		result = arr[count / 2];
	}
	return result;
}
