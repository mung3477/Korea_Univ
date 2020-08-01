#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define INSERT_OP      0x01
#define DELETE_OP      0x02
#define SUBSTITUTE_OP  0x04
#define MATCH_OP       0x08
#define TRANSPOSE_OP   0x10

#define INSERT_COST	1
#define DELETE_COST	1
#define SUBSTITUTE_COST	1
#define TRANSPOSE_COST	1

// 재귀적으로 연산자 행렬을 순회하며, 두 문자열이 최소편집거리를 갖는 모든 가능한 정렬(alignment) 결과를 출력한다.
// op_matrix : 이전 상태에 대한 연산자 정보(backtrace)가 저장된 행렬 (1차원 배열임에 주의!)
// col_size : op_matrix의 열의 크기
// str1 : 문자열 1
// str2 : 문자열 2
// n : 문자열 1의 길이
// m : 문자열 2의 길이
// level : 재귀호출의 레벨 (0, 1, 2, ...)
// align_str : 정렬된 문자쌍들의 정보가 저장된 문자열 배열 예) "a - a", "a - b", "* - b", "ab - ba"

////////////////////////////////////////////////////////////////////////////////
// 정렬된 문자쌍들을 출력 
void print_alignment( char align_str[][8], int level)
{
	int i;
	printf("========================\n");	
	for (i = level; i >= 0; i--)
	{
		printf( "%s\n", align_str[i]);
	}
}

void backtrace_main( int *op_matrix, int col_size, char *str1, char *str2, int n, int m, int level, char align_str[][8])
{
	static int count = 0;
    
    	//termination condition
    	if(n == 0 && m == 0) {
	    count++;
	    printf("\n[%d] ", count);
	    print_alignment(align_str, level - 1);
	    return; 
	}
    
	if(level == 0) { count = 0; }
	
	char align[8];
	char bar[4] = " - ";
	
	
	//S가 해당 칸에 있는 경우
	if(op_matrix[m * col_size + n] & SUBSTITUTE_OP) {
	    	align[0] = str2[m - 1];
		memcpy(align + 1, bar, 3);
		align[4] = str1[n - 1];
		align[5] = '\0';
		memcpy(align_str[level], align, 6);
		backtrace_main(op_matrix, col_size, str1, str2, n - 1, m - 1, level + 1, align_str);
	}

	//M이 해당 칸에 있는 경우
	if(op_matrix[m * col_size + n] & MATCH_OP) {
	    	align[0] = str2[m - 1];
		memcpy(align + 1, bar, 3);
		align[4] = str1[n - 1];
		align[5] = '\0';
		memcpy(align_str[level], align, 6);
		backtrace_main(op_matrix, col_size, str1, str2, n - 1, m - 1, level + 1, align_str);
	}

	//I가 해당 칸에 있는 경우
	if(op_matrix[m * col_size + n] & INSERT_OP) {
	    	align[0] = '*';
		memcpy(align + 1, bar, 3);
		align[4] = str1[n - 1];
		align[5] = '\0';
		memcpy(align_str[level], align, 6);
		backtrace_main(op_matrix, col_size, str1, str2, n - 1, m, level + 1, align_str);
	}
	
	//D가 해당 칸에 있는 경우
	if(op_matrix[m * col_size + n] & DELETE_OP) {
	    	align[0] = str2[m - 1];
		memcpy(align + 1, bar, 3);
		align[4] = '*';
		align[5] = '\0';
		memcpy(align_str[level], align, 6);
		backtrace_main(op_matrix, col_size, str1, str2, n, m - 1, level + 1, align_str);
	}

	//T가 해당 칸에 있는 경우
	if(op_matrix[m * col_size + n] & TRANSPOSE_OP) {
	    	align[0] = str2[m - 2];
		align[1] = str2[m - 1];
		memcpy(align + 2, bar, 3);
		align[5] = str1[n - 2];
		align[6] = str1[n - 1];
		align[7] = '\0';
		memcpy(align_str[level], align, 8);
		backtrace_main(op_matrix, col_size, str1, str2, n - 2, m - 2, level + 1, align_str);
	}
}

////////////////////////////////////////////////////////////////////////////////
// backtrace_main을 호출하는 wrapper 함수
void backtrace( int *op_matrix, int col_size, char *str1, char *str2, int n, int m)
{
	char align_str[n+m][8]; // n+m strings
	
	backtrace_main( op_matrix, col_size, str1, str2, n, m, 0, align_str);
}


////////////////////////////////////////////////////////////////////////////////
// 세 정수 중에서 가장 작은 값을 리턴한다.
int __GetMin3(int* arr)
{
	int min = arr[0];
	if (arr[1] < min)
		min = arr[1];
	if(arr[2] < min)
		min = arr[2];
	return min;
}

////////////////////////////////////////////////////////////////////////////////
// 네 정수 중에서 가장 작은 값을 리턴한다.
int __GetMin4(int* arr)
{
	int min = __GetMin3(arr);
	return (min > arr[3]) ? arr[3] : min;
}


// 강의 자료의 형식대로 op_matrix를 출력 (좌하단(1,1) -> 우상단(n, m))
// 각 연산자를  괄호 안의 기호로 표시한다. 삽입(I), 삭제(D), 교체(S), 일치(M), 전위(T)
void print_matrix( int *op_matrix, int col_size, int n, int m)
{
	for(int j = m; j >= 1; j--) {
	    for(int i = 1; i <= n; i++) {
		printf( "%s", op_matrix[j * col_size + i] & INSERT_OP ? "I" : "" );
		printf( "%s", op_matrix[j * col_size + i] & DELETE_OP ? "D" : "" );
		printf( "%s", op_matrix[j * col_size + i] & SUBSTITUTE_OP ? "S" : "" );
		printf( "%s", op_matrix[j * col_size + i] & MATCH_OP ? "M" : "" );
		printf( "%s", op_matrix[j * col_size + i] & TRANSPOSE_OP ? "T" : "" );
		printf("\t");
	    }
	    printf("\n");
	}
}

// 두 문자열 str1과 str2의 최소편집거리를 계산한다.
// return value : 최소편집거리
// 이 함수 내부에서 print_matrix 함수와 backtrace 함수를 호출함
int min_editdistance( char *str1, char *str2)
{
	int n = strlen(str1);
	int m = strlen(str2);

	int distance[n + 1][m + 1];
	distance[0][0] = 0;

	int col_size = n + 1;
	int op_matrix[col_size * (m + 1)];
	op_matrix[0] = 0;

	//initialize table
	for(int i = 1; i < n + 1; i++) { 
	    distance[i][0] = distance[i - 1][0] + 1; 
	    op_matrix[0 * col_size + i] = INSERT_OP;
	}
	for(int j = 1; j < m + 1; j++) { 
	    distance[0][j] = distance[0][j - 1] + 1; 
	    op_matrix[j * col_size + 0] = DELETE_OP;
	}
	//fill the table
	for(int i = 1; i < n + 1; i++) {
	    for(int j = 1; j < m + 1; j++) {
		
		op_matrix[j * col_size + i] = 0;


		//compare basic operators
		//costs array : "Insertion, Deletion, Substitution, Transpose" order.
		int new_dist[4];
		
		new_dist[0] = distance[i - 1][j] + INSERT_COST;
		new_dist[1] = distance[i][j - 1] + DELETE_COST;

		int sub_op = 0;

		if(str1[i - 1] == str2[j - 1]) { 
		    new_dist[2] = distance[i - 1][j - 1]; 
		    sub_op = MATCH_OP;
		}
		else { 
		    new_dist[2] = distance[i - 1][j - 1] + SUBSTITUTE_COST; 
		    sub_op = SUBSTITUTE_OP;
		}
		
		int min;

		//check if transpose is able
		if(i > 1 && j > 1 && (str1[i - 1] == str2[j - 2]) && (str1[i - 2] == str2[j - 1])) {
			new_dist[3] = distance[i - 2][j - 2] + TRANSPOSE_COST;
			min = __GetMin4(new_dist);
	    	}	
		else {
		    min = __GetMin3(new_dist);
		}

		//update tables
		distance[i][j] = min;
		
		if(min == new_dist[0]) { op_matrix[j * col_size + i] = op_matrix[j * col_size + i] | INSERT_OP; }
		if(min == new_dist[1]) { op_matrix[j * col_size + i] = op_matrix[j * col_size + i] | DELETE_OP; }
		if(min == new_dist[2]) { op_matrix[j * col_size + i] = op_matrix[j * col_size + i] | sub_op; }		
		if((i > 1 && j > 1 && (str1[i - 1] == str2[j - 2]) && (str1[i - 2] == str2[j - 1])) && min == new_dist[3]) {
		    op_matrix[j * col_size + i] = op_matrix[j * col_size + i] | TRANSPOSE_OP; 
		}
	
	    }
	}
	
	//print distance
	/*for(int j = m; j >= 0; j--) {
	    for(int i = 0; i <= n; i++) {
		printf("| ");
		printf("%5d", distance[i][j]);
	    }
	    printf("\n");
	}*/

	print_matrix(op_matrix, col_size, n, m);
	backtrace(op_matrix, col_size, str1, str2, n, m);
	return distance[n][m];
}


////////////////////////////////////////////////////////////////////////////////
int main()
{
	char str1[30];
	char str2[30];
	
	int distance;
	
	printf( "INSERT_COST = %d\n", INSERT_COST);
	printf( "DELETE_COST = %d\n", DELETE_COST);
	printf( "SUBSTITUTE_COST = %d\n", SUBSTITUTE_COST);
	printf( "TRANSPOSE_COST = %d\n", TRANSPOSE_COST);
	
	while( fscanf( stdin, "%s\t%s", str1, str2) != EOF)
	{
		printf( "\n==============================\n");
		printf( "%s vs. %s\n", str1, str2);
		printf( "==============================\n");
		
		distance = min_editdistance( str2, str1);
		
		printf( "\nMinEdit(%s, %s) = %d\n", str1, str2, distance);
	}
	return 0;
}
