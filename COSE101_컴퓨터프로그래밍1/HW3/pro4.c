// pro4.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>

int main()
{
	int n = 1, total = 9, count = 1, blank = 0;
	int blank1 = 0, blank2 = 0;
	int t;

	while (count <= 5) {								// count가 5일때까지
		blank = (total - n) / 2;						// 공란 갯수를 계산해 blank에 대입
		
		for (blank1 = blank; blank1 > 0; blank1--) {	//blank1 에 공란갯수 대입, blank1이 1일때까지 공란 출력
			printf(" ");
		}

		t = n;											//임시변수 t에 n 대입

		for (; t > 0; t--) {
			printf("*");
		}

		for (blank2 = blank; blank2 > 0; blank2--) {
			printf(" ");
		}

		printf("\n");

		n += 2;
		count++;
	}

	/*n = 9로 마무리, count = 5*/

	while (count <= 10) {								// count가 9일때까지
		n -= 2;											// n = 7, 5, 3, 1
		blank = (total - n) / 2;						// 공란 갯수를 계산해 blank에 대입

		for (blank1 = blank; blank1 > 0; blank1--) {	//blank1 에 공란갯수 대입, blank1이 1일때까지 공란 출력
			printf(" ");
		}

		t = n;											//임시변수 t에 n 대입

		for (; t > 0; t--) {
			printf("*");
		}

		for (blank2 = blank; blank2 > 0; blank2--) {
			printf(" ");
		}

		printf("\n");
		count++;
	}
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
