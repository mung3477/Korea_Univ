#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

/*
0x01 좌상단
0x02 우상단
0x03 좌하단
0x04 우하단
0x05 |
0x06 -
0x17 ㅓ
0x19 ㅏ
*/

void printup(void) {
	for (int i = 1; i <= 50; i++) {
		if (i == 1)
			printf("%c", 0x01);
		else if (i == 50)
			printf("%c\n", 0x02);
		else
			printf("%c", 0x06);
	}
}

void printmid(void) {
	for (int i = 1; i <= 50; i++) {
		if (i == 1)
			printf("%c", 0x19);
		else if (i == 50)
			printf("%c\n", 0x17);
		else
			printf("%c", 0x06);
	}
}

void printbot(void) {
	for (int i = 1; i <= 50; i++) {
		if (i == 1)
			printf("%c", 0x03);
		else if (i == 50)
			printf("%c\n ", 0x04);
		else
			printf("%c", 0x06);
	}
}


void plans(void) {
	system("cls");

	do {

		char c;

		printup();
		printf("%c                   Basic Plan                   %c\n", 0x05, 0x05);
		printmid();
		printf("%c   Included in plan    |    Additional usages\   %c\n", 0x05, 0x05);
		printmid();
		printf("%cVoice        | 500m free      | \ 50 / 1m        %c\n", 0x05, 0x05);
		printf("%cText         | 100t free      | \ 10 / 1t        %c\n", 0x05, 0x05);
		printf("%cData         | 2.00GB free    | \ 1000 / 0.1GB   %c\n", 0x05, 0x05);
		printmid();
		printf("%cBasic fee    | \ 20000                           %c\n", 0x05, 0x05);
		printbot();
		printf("\n");
		printup();
		printf("%c                 More Data Plan                 %c\n", 0x05, 0x05);
		printmid();
		printf("%c   Included in plan    |    Additional usages\   %c\n", 0x05, 0x05);
		printmid();
		printf("%cVoice        | 300m free      | \ 10 / 1m        %c\n", 0x05, 0x05);
		printf("%cText         | 100t free      | \ 30 / 1t        %c\n", 0x05, 0x05);
		printf("%cData         | 30.00GB free   | \ 500 / 0.1GB    %c\n", 0x05, 0x05);
		printmid();
		printf("%cBasic fee    | \ 45000                           %c\n", 0x05, 0x05);
		printbot();
		printf(" Back to main menu Y/N : ");

		scanf_s(" %c", &c);

		if (c == 'Y') {
			system("cls");
			break;
		}

		else if (c == 'N') {
			system("cls");
		}
	} while (1);
}

void PastTwoMonths(int plan, int febvoice, int marvoice, int febtext, int martext, float febdata, float mardata) {
	system("cls");
	char c;

	do {
		printup();
		printf("%c             Last two months usage              %c\n", 0x05, 0x05);
		printmid();
		if (plan)
			printf("%c My Plan : Basic Plan                           %c\n", 0x05, 0x05);
		else
			printf("%c My Plan : More Data Plan                       %c\n", 0x05, 0x05);
		printmid();
		printf("%c           |  February       |     March        %c\n", 0x05, 0x05);
		printmid();
		printf("%c Voice     |    %3d min      |     %3d min      %c\n", 0x05, febvoice, marvoice, 0x05);
		printf("%c Text      |    %3d text     |     %3d text     %c\n", 0x05, febtext, martext, 0x05);
		printf("%c Data      | %6.02f GB       |   %6.02f GB      %c\n", 0x05, febdata, mardata, 0x05);
		printbot();
		printf(" Back to main menu Y/N : ");

		scanf_s(" %c", &c);

		if (c == 'Y') {
			system("cls");
			break;
		}

		else if (c == 'N') {
			system("cls");
		}
	} while (1);

}

void ThisMonthUsage(float april[]) {

	int count = 0;

	while (1) {
		system("cls");

		if (!(count)) {
			printf("=================================\n");
			printf("Input your usages of voice : ");
			scanf_s(" %f", &april[0]);
			printf("Input your usages of text : ");
			scanf_s(" %f", &april[1]);
			printf("Input your usages of data : ");
			scanf_s(" %f", &april[2]);
			count++;
		}
		else {
			printf("=================================\n");
			printf("Input your usages of voice : %d\n", (int)april[0]);
			printf("Input your usages of text : %d\n", (int)april[1]);
			printf("Input your usages of data : %.02f\n", april[2]);
			count++;
		}

		char c;
		printf("\n");
		printf(" Back to main menu Y/N : ");
		scanf_s(" %c", &c);

		if (c == 'Y') {
			system("cls");
			break;
		}

		else if (c == 'N') {
			system("cls");
		}

	}
}


void PastThreeMonths(int plan, int febvoice, int marvoice, int febtext, int martext, float febdata, float mardata, float april[]) {

	int febfee, marfee, aprfee;
	float febextra, marextra;

	system("cls");

	while (1) {
		for (int i = 1; i <= 70; i++) {
			if (i == 1)
				printf("%c", 0x01);
			else if (i == 70)
				printf("%c\n", 0x02);
			else
				printf("%c", 0x06);
		}
		printf("%c                       My three months usage                        %c\n", 0x05, 0x05);
		for (int i = 1; i <= 70; i++) {
			if (i == 1)
				printf("%c", 0x19);
			else if (i == 70)
				printf("%c\n", 0x17);
			else
				printf("%c", 0x06);
		}
		if (plan)
			printf("%c My Plan : Basic Plan                                               %c\n", 0x05, 0x05);
		else
			printf("%c My Plan : More Data Plan                                           %c\n", 0x05, 0x05);
		for (int i = 1; i <= 70; i++) {
			if (i == 1)
				printf("%c", 0x19);
			else if (i == 70)
				printf("%c\n", 0x17);
			else
				printf("%c", 0x06);
		}
		printf("%c             |    February      |     March        |    April       %c\n", 0x05, 0x05);
		for (int i = 1; i <= 70; i++) {
			if (i == 1)
				printf("%c", 0x19);
			else if (i == 70)
				printf("%c\n", 0x17);
			else
				printf("%c", 0x06);
		}
		printf("%c Voice       |    %3d min       |     %3d min      |    %3d min     %c\n", 0x05, febvoice, marvoice, (int)april[0], 0x05);
		printf("%c Text        |    %3d text      |     %3d text     |    %3d text    %c\n", 0x05, febtext, martext, (int)april[1], 0x05);
		printf("%c Data        | %6.02f GB        |  %6.02f GB       | %6.02f GB      %c\n", 0x05, febdata, mardata, april[2], 0x05);
		for (int i = 1; i <= 70; i++) {
			if (i == 1)
				printf("%c", 0x19);
			else if (i == 70)
				printf("%c\n", 0x17);
			else
				printf("%c", 0x06);
		}
		if (plan) { // basic
			if (2.00 - febdata > 0)
				if (2.00 - febdata + 2.00 - mardata > 0)
					if (6.00 - febdata - mardata - april[2] > 0) {
						printf("%c Extra Data  | %6.02f GB        |  %6.02f GB       | %6.02f GB      %c\n", 0x05, (2.0 - febdata > 0.2 ? 0.2 : 2.0 - febdata), (4.0 - febdata - mardata > 0.2 ? 0.2 : 4.0 - febdata - mardata), (6.0 - febdata - mardata - april[3] > 0.2 ? 0.2 : 6.0 - febdata - mardata - april[3]), 0x05);
						febextra = (2.0 - febdata > 0.2 ? 0.2 : 2.0 - febdata);
						marextra = (4.0 - febdata - mardata > 0.2 ? 0.2 : 4.0 - febdata - mardata);
					}
					else { // april = 0 
						printf("%c Extra Data  | %6.02f GB        |  %6.02f GB       | %6.02f GB      %c\n", 0x05, (2.0 - febdata > 0.2 ? 0.2 : 2.0 - febdata), (4.0 - febdata - mardata > 0.2 ? 0.2 : 4.0 - febdata - mardata), 0.00, 0x05);
						febextra = (2.0 - febdata > 0.2 ? 0.2 : 2.0 - febdata);
						marextra = (4.0 - febdata - mardata > 0.2 ? 0.2 : 4.0 - febdata - mardata);
					}
				else // march = 0
					if (2.0 - april[2] > 0) {
						printf("%c Extra Data  | %6.02f GB        |  %6.02f GB       | %6.02f GB      %c\n", 0x05, (2.0 - febdata > 0.2 ? 0.2 : 2.0 - febdata), 0.00, (3.0 - april[3] > 0.2 ? 0.2 : 3.0 - april[3]), 0x05);
						febextra = (2.0 - febdata > 0.2 ? 0.2 : 2.0 - febdata);
						marextra = 0.0;
					}
					else { // april = 0
						printf("%c Extra Data  | %6.02f GB        |  %6.02f GB       | %6.02f GB      %c\n", 0x05, (2.0 - febdata > 0.2 ? 0.2 : 2.0 - febdata), 0.00, 0.00, 0x05);
						febextra = (2.0 - febdata > 0.2 ? 0.2 : 2.0 - febdata);
						marextra = 0.0;
					}
			else // feb  = 0
				if (2.0 - mardata > 0)
					if (4.0 - mardata - april[2] > 0) {
						printf("%c Extra Data  | %6.02f GB        |  %6.02f GB       | %6.02f GB      %c\n", 0x05, 0.00, (2.0 - mardata > 0.2 ? 0.2 : 2.0 - mardata), (4.0 - mardata - april[3] > 0.2 ? 0.2 : 4.0 - mardata - april[3]), 0x05);
						febextra = 0;
						marextra = (2.0 - mardata > 0.2 ? 0.2 : 2.0 - mardata);
					}
					else { //april = 0
						printf("%c Extra Data  | %6.02f GB        |  %6.02f GB       | %6.02f GB      %c\n", 0x05, 0.00, (2.0 - mardata > 0.2 ? 0.2 : 2.0 - mardata), 0.00, 0x05);
						febextra = 0;
						marextra = (2.0 - mardata > 0.2 ? 0.2 : 2.0 - mardata);
					}
				else // march = 0
					if (2.0 - april[2] > 0) {
						printf("%c Extra Data  | %6.02f GB        |  %6.02f GB       | %6.02f GB      %c\n", 0x05, 0.00, 0.00, (2.0 - april[3] > 0.2 ? 0.2 : 2.0 - april[3]), 0x05);
						febextra = 0.0;
						marextra = 0.0;
					}
					else { //april = 0
						printf("%c Extra Data  | %6.02f GB        |  %6.02f GB       | %6.02f GB      %c\n", 0x05, 0.00, 0.00, 0.00, 0x05);
						febextra = 0.0;
						marextra = 0.0;
					}

		}

		else { //More data 
			if (30.00 - febdata > 0)
				if (30.0 - febdata + 30.0 - mardata > 0)
					if (90.0 - febdata - mardata - april[2] > 0) {
						printf("%c Extra Data  | %6.02f GB        |  %6.02f GB       | %6.02f GB      %c\n", 0x05, (30.0 - febdata > 3.0 ? 3.0 : 30.0 - febdata), (60.0 - febdata - mardata > 3.0 ? 3.0 : 60.0 - febdata - mardata), (90.0 - febdata - mardata - april[3] > 3.0 ? 3.0 : 90.0 - febdata - mardata - april[3]), 0x05);
						febextra = (30.0 - febdata > 3.0 ? 3.0 : 30.0 - febdata);
						marextra = (60.0 - febdata - mardata > 3.0 ? 3.0 : 60.0 - febdata - mardata);
					}
					else { // april = 0
						printf("%c Extra Data  | %6.02f GB        |  %6.02f GB       | %6.02f GB      %c\n", 0x05, (30.0 - febdata > 3.0 ? 3.0 : 30.0 - febdata), (60.0 - febdata - mardata > 3.0 ? 3.0 : 60.0 - febdata - mardata), 0.00, 0x05);
						febextra = (30.0 - febdata > 3.0 ? 3.0 : 30.0 - febdata);
						marextra = (60.0 - febdata - mardata > 3.0 ? 3.0 : 60.0 - febdata - mardata);
					}
				else // march = 0
					if (30.0 - april[2] > 0) {
						printf("%c Extra Data  | %6.02f GB        |  %6.02f GB       | %6.02f GB      %c\n", 0x05, (30.0 - febdata > 3.0 ? 3.0 : 30.0 - febdata), 0.00, (30.0 - april[3] > 3.0 ? 3.0 : 30.0 - april[3]), 0x05);
						febextra = (30.0 - febdata > 3.0 ? 3.0 : 30.0 - febdata);
						marextra = 0.0;
					}
					else { // april = 0
						printf("%c Extra Data  | %6.02f GB        |  %6.02f GB       | %6.02f GB      %c\n", 0x05, (30.0 - febdata > 3.0 ? 3.0 : 30.0 - febdata), 0.00, 0.00, 0x05);
						febextra = (30.0 - febdata > 3.0 ? 3.0 : 30.0 - febdata);
						marextra = 0.0;
					}
			else // feb  = 0
				if (30.0 - mardata > 0)
					if (60.0 - mardata - april[2] > 0) {
						printf("%c Extra Data  | %6.02f GB        |  %6.02f GB       | %6.02f GB      %c\n", 0x05, 0.00, (30.0 - mardata > 3.0 ? 3.0 : 30.0 - mardata), (60.0 - mardata - april[3] > 3.0 ? 3.0 : 60.0 - mardata - april[3]), 0x05);
						febextra = 0.0;
						marextra = (30.0 - mardata > 3.0 ? 3.0 : 30.0 - mardata);
					}
					else { //april = 0
						printf("%c Extra Data  | %6.02f GB        |  %6.02f GB       | %6.02f GB      %c\n", 0x05, 0.00, (30.0 - mardata > 3.0 ? 3.0 : 30.0 - mardata), 0.00, 0x05);
						febextra = 0.0;
						marextra = (30.0 - mardata > 3.0 ? 3.0 : 30.0 - mardata);
					}
				else // march = 0
					if (30.0 - april[2] > 0) {
						printf("%c Extra Data  | %6.02f GB        |  %6.02f GB       | %6.02f GB      %c\n", 0x05, 0.00, 0.00, (30.0 - april[3] > 3.0 ? 3.0 : 30.0 - april[3]), 0x05);
						febextra = 0.00;
						marextra = 0.00;
					}
					else { //april = 0
						printf("%c Extra Data  | %6.02f GB        |  %6.02f GB       | %6.02f GB      %c\n", 0x05, 0.00, 0.00, 0.00, 0x05);
						febextra = 0.00;
						marextra = 0.00;
					}
		}
		for (int i = 1; i <= 70; i++) {
			if (i == 1)
				printf("%c", 0x19);
			else if (i == 70)
				printf("%c\n", 0x17);
			else
				printf("%c", 0x06);
		}

		if (plan) { //basic
			febfee = 20000 + (febvoice > 500 ? (febvoice - 500) * 50 : 0) + (febtext > 100 ? (febtext - 100) * 10 : 0) + (febdata > 2.00 ? (febdata - 2.00) / 0.1 * 1000 : 0);
			marfee = 20000 + (marvoice > 500 ? (marvoice - 500) * 50 : 0) + (martext > 100 ? (martext - 100) * 10 : 0) + (mardata - febextra > 2.00 ? (mardata - febextra - 2.00) / 0.1 * 1000 : 0);
			aprfee = 20000 + (april[0] > 500 ? (april[0] - 500) * 50 : 0) + (april[1] > 100 ? (april[1] - 100) * 10 : 0) + (april[2] - marextra > 2.00 ? (april[2] - marextra - 2.00) / 0.1 * 1000 : 0);
		}

		else { // More data
			febfee = 45000 + (febvoice > 300 ? (febvoice - 300) * 10 : 0) + (febtext > 100 ? (febtext - 100) * 30 : 0) + (febdata > 30.00 ? (febdata - 30.0) / 0.1 * 500 : 0);
			marfee = 45000 + (marvoice > 300 ? (marvoice - 300) * 10 : 0) + (martext > 100 ? (martext - 100) * 30 : 0) + (mardata - febextra > 30.00 ? (mardata - febextra - 30.0) / 0.1 * 500 : 0);
			aprfee = 45000 + (april[0] > 300 ? (april[0] - 300) * 10 : 0) + (april[1] > 100 ? (april[1] - 100) * 30 : 0) + (april[2] - marextra > 30.00 ? (april[2] - marextra - 30.0) / 0.1 * 500 : 0);
		}

		printf("%c Total Fee   | \\  %7d       |  \\  %7d      | \\  %7d     %c\n", 0x05, febfee, marfee, aprfee, 0x05);

		for (int i = 1; i <= 70; i++) {
			if (i == 1)
				printf("%c", 0x03);
			else if (i == 70)
				printf("%c\n ", 0x04);
			else
				printf("%c", 0x06);
		}

		char c;
		printf(" Back to main menu Y/N : ");
		scanf_s(" %c", &c);

		if (c == 'Y') {
			system("cls");
			break;
		}

		else if (c == 'N') {
			system("cls");
		}
	}
}

void Recommendation(int plan, int febvoice, int marvoice, int febtext, int martext, float febdata, float mardata, float april[]) {

	int avervoice = (int)((float)(febvoice + marvoice + (int)april[0]) / 3.0 + 0.5);
	int avertext = (int)((float)(febtext + martext + (int)april[1]) / 3.0 + 0.5);
	float averdata = roundf((float)(febdata + mardata + april[2]) / 3.0 * 100) / 100 ;
	int basicfee = 20000 + (avervoice > 500 ? (avervoice - 500) * 50 : 0) + (avertext > 100 ? (avertext - 100) * 10 : 0) + (averdata > 2.00 ? (averdata - 2.00) / 0.1 * 1000 : 0);
	int Morefee = 45000 + (avervoice > 300 ? (avervoice - 300) * 10 : 0) + (avertext > 100 ? (avertext - 100) * 30 : 0) + (averdata > 30.00 ? (averdata - 30.0) / 0.1 * 500 : 0);

	system("cls");

	while (1) {
		printup();
		printf("%c            Average usage of 3-month            %c\n", 0x05, 0x05);
		printmid();
		if (plan)
			printf("%c My Plan : Basic Plan                           %c\n", 0x05, 0x05);
		else
			printf("%c My Plan : More Data Plan                       %c\n", 0x05, 0x05);
		printmid();
		printf("%c Average usage of voice : %3d                   %c\n", 0x05, avervoice, 0x05);
		printf("%c Average usage of text :  %3d                   %c\n", 0x05, avertext, 0x05);
		printf("%c Average usage of data :  %5.02f                 %c\n", 0x05, averdata, 0x05);
		printmid();
		printf("%c Basic Plan Fee :      \\%7d                 %c\n", 0x05, basicfee, 0x05);
		printf("%c More Data Plan Fee  : \\%7d                 %c\n", 0x05, Morefee, 0x05);
		printmid();
		if (Morefee > basicfee)
			printf("%c We recommend to use Basic Plan                 %c\n", 0x05, 0x05);
		else
			printf("%c We recommend to use More Data Plan             %c\n", 0x05, 0x05);
		printbot();

		char c;
		printf(" Back to main menu Y/N : ");
		scanf_s(" %c", &c);

		if (c == 'Y') {
			system("cls");
			break;
		}

		else if (c == 'N') {
			system("cls");
		}
	}
}

int mainmenu(void) {

	int input;
	int febvoice = rand() % 700 + 1;
	int marvoice = rand() % 700 + 1;
	int febtext = rand() % 300;
	int martext = rand() % 300;
	float febdata = (float)(rand() % 14950 + 50) / 100;
	float mardata = (float)(rand() % 14950 + 50) / 100;
	int plan = rand() % 2;

	float april[3] = { 0 };

	while (1) {

		printup();
		printf("%c       KU Mobile Phone Bill Calculator          %c\n", 0x05, 0x05);
		printmid();
		printf("%c     1 : Display plans                          %c\n", 0x05, 0x05);
		printf("%c     2 : Usage information for past two months  %c\n", 0x05, 0x05);
		printf("%c     3 : Input this month usage                 %c\n", 0x05, 0x05);
		printf("%c     4 : Total fee for past 3 months            %c\n", 0x05, 0x05);
		printf("%c     5 : Best plan recommendation               %c\n", 0x05, 0x05);
		printf("%c     6 : Exit                                   %c\n", 0x05, 0x05);
		printbot();
		scanf_s("%d", &input);

		switch (input) {
		case 1:
			plans();
			break;
		case 2:
			PastTwoMonths(plan, febvoice, marvoice, febtext, martext, febdata, mardata);
			break;
		case 3:
			ThisMonthUsage(april);
			break;
		case 4:
			PastThreeMonths(plan, febvoice, marvoice, febtext, martext, febdata, mardata, april);
			break;
		case 5:
			Recommendation(plan, febvoice, marvoice, febtext, martext, febdata, mardata, april);
			break;
		case 6:
			return 6;
		}
	}
}

void main(void) {
	srand(time(NULL));

	while (mainmenu() != 6);
}