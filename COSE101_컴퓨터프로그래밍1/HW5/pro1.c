#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

	srand(time(NULL));

	int i, j; //counter & iterative
	int index = 0;
	int Array2[20];
	int Array[20] = { 0 };
	int n;

	printf("Nonrepetitive array values are: \n");
	for (int i = 0; i <= 19; i++) {  //random int 20번 생성
		int result = 0;
		n = rand() % 20 + 1;
		Array2[i] = n;


		for (int j = 0; j <= i; j++) {	//Array 안에 똑같은게 있는지 확인
			if (Array[j] == n) {		//똑같은게 없으면 Array에 저장
				result = 1;
				break;
			}
		}// 똑같은게 있으면 result = 1, 똑같은게 없으면 result = 0

		if (!(result)) {
			Array[index] = n;
			printf("Array[ %d ] = %d\n", index, Array[index]);
			index++;
		}
	}
}