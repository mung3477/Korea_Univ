#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int flip();

void main()
{
	srand(time(NULL)); //이 타이밍부터 시드한다!

	int count = 1;
	int Head = 0, Tail = 0;
	while (count <= 100) {

		if (count % 10 == 0) {
			if (flip()) {			// rand에서 홀수가 나오면
				printf("Heads \n");
				Head++;
			}
			else {
				printf("Tails \n"); // rand에서 짝수가 나오면
				Tail++;
			}
		}

		else {
			if (flip()) {			// rand에서 홀수가 나오면
				printf("Heads ");
				Head++;
			}
			else {
				printf("Tails "); // rand에서 짝수가 나오면
				Tail++;
			}
		}
		count++;
	}

	printf("\n");
	printf("The total number of Heads was %d\n", Head);
	printf("The total number of Tails was %d", Tail);
}

int flip() {


	int i = rand();


	if (i % 2 == 0)
		return 0;
	else
		return 1;
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
