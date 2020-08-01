#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <math.h>
#include <utility>
#include <queue>

#define BOARD_X 3
#define BOARD_Y 4
#define INF 100000000
#define THRESHOLD 1000301
#define OCCUPIED -7979187
#define CUTOFF 414 //시간 초과로 짤리는 경우. depth CUTOFF는 필요한 정보이므로 무시하지 않음.

using namespace std;


/*variables*/
int Player, Agent;			//각 플레이어의 색깔을 저장. 1이 흑돌, 2가 백돌
int timeLimit;				//시간 제한
								

typedef struct action {		//action
	pair<int, int> loc;
	int value;
} action;

struct cmp {	//struct for overloading less operator of Priority queue. 절댓값 내림차순
	bool operator()(action t, action u) {
		return abs(t.value) < abs(u.value);
	}
};

typedef struct around {		//8방향 개수 세기 용
	pair<int, int> loc;
	int up;
	int down;
	int right;
	int left;
	int diag_rightUp;
	int diag_rightDown;
	int diag_leftUp;
	int diag_leftDown;
	bool Open_up;
	bool Open_down;
	bool Open_right;
	bool Open_left;
	bool Open_diag_RU;
	bool Open_diag_RD;
	bool Open_diag_LU;
	bool Open_diag_LD;
} around;

typedef struct state {	//state
	int board[20][20];	/*오목판의 현재 상태. [row][column]
						index 1~19만 사용.
						0:아무것도 없음 1:흰돌 2:흑돌*/

	int weight[20][20];
	int score;
	priority_queue<action, vector<action>, cmp> Actions[2]; //index 0은 백돌, 1은 흑돌용
	pair<int, int> prevLoc;
	around A;
} state;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*Function definition*/

void setCoordinate(int x, int y);
void draw_board();			//오목판 그리기
void draw_stone(state s);			//판에 돌 그리기
void draw_playScreen(state s);		//게임 진행 화면 그리기
void goMainMenuScreen();
void printEndScreen(int Winner);	//승리문구 출력
void gameStart();			//게임 진행시키는 caller함수

bool terminalTest(state s); //오목 체크 caller함수
around countStone(int board[20][20], pair<int, int> loc);	//8방향 돌 세는 함수
bool check_33(state cur, pair<int, int> loc, int color);	//33 체크함수

action blackTurn(state cur);			//흑돌 턴에 실행되는 함수
action whiteTurn(state cur);			//백돌 턴에 실행되는 함수
pair<int, int> getLocation_Player(clock_t curTime, state cur); //플레이어에게 착수위치 입력받음
action PlayerTurn(state cur);//플레이어가 착수
action AgentTurn(state cur);	//AI가 착수

action Iterative_Deepening_ABS(state cur, clock_t endtime);
action Depth_Limited_ABS(state cur, clock_t endtime, int d);
action Alpha_Beta_Search(state cur, clock_t endtime, int d, long long a, long long b);
action Max_Value(state cur, clock_t endtime, int d, long long a, long long b);
action Min_Value(state cur, clock_t endtime, int d, long long a, long long b);

state ply(int color, state cur, action best);	//착수 함수
void weightUpdate_B(state&); //흑돌 가중치 갱신
void weightUpdate_W(state&); //백돌 가중치 갱신

void printweight(state s);

////////////////////////////////////////////////////////////////////////////////////////////////////

/*main function*/
int main(void)
{
	srand(time(NULL));
	goMainMenuScreen();
	
	gameStart();
	Sleep(1000);
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

/*function declaration*/

void setCoordinate(int x, int y) { //cmd에서 커서 위치를 x, y로 세팅   Setting curser to (x,y).
	COORD pos = { 2 * x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void draw_board()
{
	int x = 3, y = 4;
	
	int i, j;

	//Index
	setCoordinate(x, y); printf(" ");
	for (i = 1; i <= 9; i++)
		printf("%d ", i);
	for (i = 10; i <= 19; i++)
		printf("%d", i);
	printf("\n");

	//맨 윗줄
	setCoordinate(x, y + 1); printf("A┌");
	for (i = 0; i < 17; i++) 
		printf("-┬");
	printf("-┐\n");

	//중단
	for (i = 0; i < 17; i++) {
		setCoordinate(x, y + 2 + i); printf("%c", 'B' + i);
		printf("├");
		for (j = 0; j < 17; j++)
			printf("-┼");
		printf("-┤\n");
	}

	//맨 아랫줄
	setCoordinate(x, y + 19); printf("S└");
	for (i = 0; i < 17; i++)
		printf("-┴");
	printf("-┘");
}

void draw_stone(state s)
{
	int x = 3, y = 4;
	setCoordinate(x, y);
	int i, j;
	for (i = 1; i < 20; i++) {
		for (j = 1; j < 20; j++) {
			if (s.board[i][j] == 1) { setCoordinate(j + x, i + y);  printf("\b○"); }
			if (s.board[i][j] == 2) { setCoordinate(j + x, i + y);  printf("\b●"); }
		}
	}
}

void draw_playScreen(state s) {
	draw_board();
	//printweight(s);
	draw_stone(s);
}

void printweight(state s) {
	int x = 3, y = 4;
	setCoordinate(x, y);

	for (int i = 1; i <= 19; i++) {
		for (int j = 1; j <= 19; j++) {
			if (!s.board[i][j]) {
				setCoordinate(x + j, y + i);
				printf("\b%d", s.weight[i][j]);
			}
		}
		printf("\n");
	}
}

void goMainMenuScreen(void) { //메인 메뉴 화면 출력
	int x = 19;
	int y = 9;
	int t = 0;

	do {
		setCoordinate(x, y + 1); printf("(*￣▽￣)/");
		setCoordinate(x, y + 2); printf("신나고 재밌는 알파오와의 대결! 오목 게임입니다!");
		Sleep(30);
		setCoordinate(x, y + 4); printf("어느 색 돌을 플레이 하실 건가요?");
		Sleep(30);
		setCoordinate(x, y + 5); printf("검은색은 1, 흰색은 2를 입력해주세요 : ");
		
		scanf("%d", &t);
		switch (t) {
		case 1:
			setCoordinate(x, y + 6); printf("검은색으로 플레이 하시게 됩니다!");
			Player = 1;
			Agent = 2;
			break;
		case 2:
			setCoordinate(x, y + 6);  printf("흰색으로 플레이 하시게 됩니다!");
			Player = 2;
			Agent = 1;
			break;
		default:
			setCoordinate(x, y + 6); printf("잘못된 입력입니다. 올바르게 입력해 주세요.");
			system("cls");
			Sleep(1000);
		}
		while (_kbhit()) _getch(); //키버퍼를 비움. 
	} while (t != 1 && t != 2);

	setCoordinate(x, y + 8); printf("시간 제한을 몇 초로 하시겠습니까? : ");
	scanf(" %d", &timeLimit);
	setCoordinate(x, y + 9); printf("%d초로 설정하셨습니다.", timeLimit);
	Sleep(500);
	setCoordinate(x, y + 11); printf("3초 후 게임이 시작됩니다! ");
	Sleep(500);
	setCoordinate(x, y + 12); printf("플레이어님의 승리를 기원합니다! (/￣∇￣)/＼(￣∇￣＼)");
	Sleep(2000);
	system("cls");
	while (_kbhit()) _getch(); //키버퍼를 비움. 
}

void printEndScreen(int Winner) {
	int x = BOARD_X + 5;
	
	setCoordinate(x, BOARD_Y + 5);  printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
	setCoordinate(x, BOARD_Y + 6);  printf("▤                                      ▤");
	setCoordinate(x, BOARD_Y + 7);  printf("▤  +-------------------------------+   ▤");
	if (Winner == 1) {
		setCoordinate(x, BOARD_Y + 8);  printf("▤  |      흑 돌이 이겼습니다!      |   ▤");
	}
	else {
		setCoordinate(x, BOARD_Y + 8);  printf("▤  |      백 돌이 이겼습니다!      |   ▤");
	}
	setCoordinate(x, BOARD_Y + 9);  printf("▤  +-------------------------------+   ▤");
	setCoordinate(x, BOARD_Y + 10); printf("▤                                      ▤");
	if (Winner == Player) {
		setCoordinate(x, BOARD_Y + 11); printf("▤           플레이어의 승리!           ▤");
	}
	else {
		setCoordinate(x, BOARD_Y + 11); printf("▤           인공지능의 승리!           ▤");
	}
	setCoordinate(x, BOARD_Y + 12); printf("▤                                      ▤");
	setCoordinate(x, BOARD_Y + 13); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");

}

void gameStart(void) {
	
	//setting
	state cur;
	for(int i = 0; i <= 19; i++){
		for (int j = 0; j <= 19; j++) {
			cur.board[i][j] = 0;
			cur.weight[i][j] = 0;
		}
	}
	
	cur.score = 0;
	cur.prevLoc = { 0, 0 };

	draw_playScreen(cur);
	int Winner = 0;
	
	//Play
	while (1) {
		action best = blackTurn(cur);
		system("cls");

		cur = ply(1, cur, best);
		draw_playScreen(cur);

		if (terminalTest(cur)) {
			Winner = 1;
			break;
		}

		best = whiteTurn(cur);
		system("cls");

		cur = ply(2, cur, best);
		draw_playScreen(cur);

		if (terminalTest(cur)) {
			Winner = 2;
			break;
		}

		
	}
	printEndScreen(Winner);
}

bool terminalTest(state s) {	//오목 체크
	around A = s.A;
	return ((A.up + A.down == 4) || (A.right + A.left == 4) || (A.diag_leftDown + A.diag_rightUp == 4) || (A.diag_leftUp + A.diag_rightDown == 4));
}

around countStone(int board[20][20], pair<int, int> loc) {	// 그 위치 주위로 같은 색 돌이 몇 개 있는지 셈
	around A;
	A.loc = loc;
	int r = loc.first, c = loc.second, i;
	for (i = 0; r - i > 0 && board[r][c] == board[r - i][c]; i++); 
	A.up = i - 1; 
	if (board[r - i][c]) A.Open_up = false;
	else A.Open_up = true;

	for (i = 0; r + i <= 19 && board[r][c] == board[r + i][c]; i++); 
	A.down = i - 1;	
	if (board[r + i][c]) A.Open_down = false;

	for (i = 0; c - i > 0 && board[r][c] == board[r][c - i]; i++); 
	A.left = i - 1;
	if (board[r][c - i]) A.Open_left = false;
	else A.Open_left = true;

	for (i = 0; c + i <= 19 && board[r][c] == board[r][c + i]; i++); 
	A.right = i - 1;
	if (board[r][c + i]) A.Open_right = false;
	else A.Open_right = true;

	for (i = 0; r + i <= 19 && c - i > 0 && board[r][c] == board[r + i][c - i]; i++); 
	A.diag_leftDown = i - 1;
	if (board[r + i][c - i]) A.Open_diag_LD = false;
	else A.Open_diag_LD = true;

	for (i = 0; r - i > 0 && c - i > 0  && board[r][c] == board[r - i][c - i]; i++); 
	A.diag_leftUp = i - 1;
	if (board[r - i][c - i]) A.Open_diag_LU = false;
	else A.Open_diag_LU = true;

	for (i = 0; r - i > 0 && c + i <= 19 && board[r][c] == board[r - i][c + i]; i++); 
	A.diag_rightUp = i - 1;
	if (board[r - i][c + i]) A.Open_diag_RU = false;
	else A.Open_diag_RU = true;

	for (i = 0; r + i <= 19 && c + i <= 19 && board[r][c] == board[r + i][c + i]; i++); 
	A.diag_rightDown = i - 1;
	if (board[r + i][c + i]) A.Open_diag_RD = false;
	else A.Open_diag_RD = true;
	return A;
}

bool check_33(state cur, pair<int, int> loc, int color) {	//33체크
	/*이 자리에 두면 열린 3이 두 개 이상 생기면 33*/
	int count = 0;

	cur.board[loc.first][loc.second] = color;
	around here = countStone(cur.board, loc);

	cur.board[loc.first][loc.second] = 0;

	//가로
	if ((here.left + here.right + 1 == 3) && here.Open_left && here.Open_right) count++;
	//세로
	if ((here.up + here.down + 1 == 3) && here.Open_up && here.Open_down) count++;
	//우상향 대각선
	if ((here.diag_leftDown + here.diag_rightUp + 1 == 3) && here.Open_diag_LD && here.Open_diag_RU) count++;
	//우하향 대각선
	if ((here.diag_leftUp + here.diag_rightDown + 1 == 3) && here.Open_diag_LU && here.Open_diag_RD) count++;

	if (count >= 2) return true;
	else return false;
}

action blackTurn(state cur) {	//흑돌 턴에 실행되는 함수
	action K;
	int x = 30, y = 4;
	setCoordinate(x, y);
	printf("흑돌의 차례입니다.");

	if (Player == 1) {
		K = PlayerTurn(cur);
	}
	else {
		K = AgentTurn(cur);
	}
	return K;
}

action whiteTurn(state cur) {	//백돌 턴에 실행되는 함수
	action K;
	int x = 30, y = 4;
	setCoordinate(x, y);
	printf("백돌의 차례입니다.");

	if (Player == 2) {
		K = PlayerTurn(cur);
	}
	else {
		K = AgentTurn(cur);
	}
	return K;
}

pair<int, int> getLocation_Player(clock_t curTime, state cur) {	//플레이어에게 착수 위치 입력받기
	pair<int, int> loc = { 0, 1 };
	char tr; int c;
	bool done = false;
	clock_t endwait = curTime + timeLimit * CLOCKS_PER_SEC;
	do {
		int x = 30, y = 7;
		setCoordinate(x, y); printf("시간제한은 %d초 입니다!", timeLimit);
		setCoordinate(x, y + 2); printf("돌의 위치는 행-열 순으로 표기합니다. (Ex. J 10)");
		setCoordinate(x, y + 3); printf("어디에 착수하실 건지 입력해주세요. : ");
		
		
		scanf(" %c %d", &tr, &c);
		if (endwait < clock()) break;

		int r = tr - 'A' + 1;
		if (tr < 'A' || tr > 'S' || c < 1 || c > 19) {
			setCoordinate(x, y + 3);  printf("좌표가 잘못되었습니다. 올바르게 다시 입력해주세요.");
			Sleep(1000);
			setCoordinate(x, y + 3);  printf("                                                   ");
		}
		else if (cur.board[r][c]) {
			setCoordinate(x, y + 3); printf("이미 돌이 착수되어있는 위치입니다. 다른 위치를 입력해주세요.");
			Sleep(1000);
			setCoordinate(x, y + 3); printf("                                                                ");
		}
		else if (check_33(cur, make_pair(r, c), Player)) {
			setCoordinate(x, y + 3); printf("33에는 돌을 둘 수 없습니다. 다른 위치를 입력해주세요.");
			Sleep(1000);
			setCoordinate(x, y + 3); printf("                                                      ");
		}
		else {
			loc = { r, c };
			done = true;
		}
		while (_kbhit()) _getch(); //키버퍼를 비움. 
		Sleep(50);
	} while (!done);
	return loc;
}

action PlayerTurn(state cur) {	//플레이어가 착수
	pair<int, int> loc = { 0, 1 };
	int x = 30, y = 7;
	clock_t curTime = clock();
	
	loc = getLocation_Player(curTime, cur);
	
	if (loc == make_pair(0, 1)) {
		setCoordinate(x, y + 5);  printf("시간초과! 상대에게 턴이 넘어갑니다.");
		Sleep(1000);
	}
	
	action K;
	K.loc = loc;
	K.value = cur.weight[loc.first][loc.second];

	return K;
}

action AgentTurn(state cur) {	//AI가 착수
	//return { {0,0}, 0 };

	clock_t curTime = clock();
	clock_t endwait = curTime + timeLimit * CLOCKS_PER_SEC;
	
	//1턴이면
	if (cur.prevLoc == make_pair(0, 0)) {
		action sol = { {10, 10}, 0 };
		return sol;
	}

	return Iterative_Deepening_ABS(cur, endwait);
}

action Iterative_Deepening_ABS(state cur, clock_t endwait) {
	action sol = { {0, 0}, 0 };

	for (int d = 0; 1; d++) {
		action t = Depth_Limited_ABS(cur, endwait, d);
		if (t.value != CUTOFF) {
			sol = t;
			//if (sol.value == THRESHOLD * 20 || sol.value == -INF) return sol;
		}
		else return sol;
	}
	return sol;
}

action Depth_Limited_ABS(state cur, clock_t endwait, int d) {
	action sol = Alpha_Beta_Search(cur, endwait, d, -(INF), INF);
	return sol;
}

action Alpha_Beta_Search(state cur, clock_t endwait, int d, long long a, long long b) {
	action sol;
	if (Agent == 1) {	//흑돌이면 Max_Value
		sol = Max_Value(cur, endwait, d, a, b);
	}
	else {	//백돌이면 Min_Value
		sol = Min_Value(cur, endwait, d, a, b);
	}
	return sol;
}

action Max_Value(state cur, clock_t endwait, int d, long long a, long long b) {	//흑돌 턴에서
	
	//sol의 value는 여태 찾은 가장 좋은 최종 결과
	action sol;
	sol.value = -INF;

	//시간초과 체크
	if (clock() > endwait) {
		sol.loc = { 0, 0 };
		sol.value = CUTOFF;
		return sol;
	}

	//depth limit 체크
	if (d == 0) {
		sol.loc = cur.prevLoc;
		sol.value = cur.score;
		return sol;
	}

	//오목 체크
	if (terminalTest(cur)) {
		sol.loc = cur.prevLoc;
		sol.value = cur.score;
		return sol;
	}


	while (cur.Actions[1].size() + cur.Actions[0].size()) {
		//sol 로 이끈 action을 저장하기 위한 temporary variable
		action t;

		//현재 상황에서 흑돌이 취할 수 있는 가장 좋아보이는 action 찾기
	
			if (cur.Actions[1].empty() && cur.Actions[0].empty()) {
				break;
			}

			if (cur.Actions[1].empty()) { //흑돌에게 좋은 action이 없으면
				t = cur.Actions[0].top();
				cur.Actions[0].pop();
			}

			else if (cur.Actions[0].empty()) {	//백돌에게 좋은 action이 없으면
				t = cur.Actions[1].top();
				cur.Actions[1].pop();
			}

			else {	//둘 다 나름 좋은게 있으면 두 action중 높은 걸 행함. 동률인 경우 열린 3을 만드는 수를 제외하고는 상대방 것을 행함.
				if (abs(cur.Actions[1].top().value) > abs(cur.Actions[0].top().value)) {	//흑 > 백
					t = cur.Actions[1].top();
					cur.Actions[1].pop();
				}
				else if (abs(cur.Actions[1].top().value) == abs(cur.Actions[0].top().value)) { //흑 == 백
					if (cur.Actions[1].top().value >= THRESHOLD) {
						t = cur.Actions[1].top();
						cur.Actions[1].pop();
					}
					else {
						t = cur.Actions[0].top();
						cur.Actions[0].pop();
					}
				}
				else {	//흑 < 백
					t = cur.Actions[0].top();
					cur.Actions[0].pop();
				}

			}
		

		if (cur.board[t.loc.first][t.loc.second] || check_33(cur, t.loc, 1)) continue;
		
		//탐색
		action result = Min_Value(ply(1, cur, t), endwait, d - 1, a, b);

		//시간 초과되었으면 탐색 종료
		if (result.value == CUTOFF) {
			sol.loc = { 0, 0 };
			sol.value = CUTOFF;
			return sol;
		}

		//탐색한 게 더 좋으면 sol 갱신
		if (sol.value < result.value) {
			sol.loc = t.loc;
			sol.value = result.value;
		}

		//Alpha beta pruning
		if (sol.value > b) {
			return sol;
		}

		//alpha 갱신
		a = max(a, sol.value);
	}
	
	return sol;
}

action Min_Value(state cur, clock_t endwait, int d, long long a, long long b) {	//백돌 턴에서
	//sol의 value는 여태 찾은 가장 좋은 최종 결과
	action sol;
	sol.value = INF;

	//시간초과 체크
	if (clock() > endwait) {
		sol.loc = { 0, 0 };
		sol.value = CUTOFF;
		return sol;
	}

	//depth limit 체크
	if (d == 0) {
		sol.loc = cur.prevLoc;
		sol.value = cur.score;
		return sol;
	}

	//오목 체크
	if (terminalTest(cur)) {
		sol.loc = cur.prevLoc;
		sol.value = cur.score;
		return sol;
	}


	while (cur.Actions[1].size() + cur.Actions[0].size()) {
		//sol 로 이끈 action을 저장하기 위한 temporary variable
		action t;

		//현재 상황에서 백돌이 취할 수 있는 가장 좋아보이는 action 찾기
			if (cur.Actions[1].empty() && cur.Actions[0].empty()) {
				break;
			}

			if (cur.Actions[1].empty()) { //흑돌에게 좋은 action이 없으면
				t = cur.Actions[0].top();
				cur.Actions[0].pop();
			}

			else if (cur.Actions[0].empty()) {	//백돌에게 좋은 action이 없으면
				t = cur.Actions[1].top();
				cur.Actions[1].pop();
			}

			else {	//둘 다 나름 좋은게 있으면 두 action중 높은 걸 행함. 동률인 경우 열린 3을 만드는 수를 제외하고는 상대방 것을 행함.
				if (abs(cur.Actions[1].top().value) > abs(cur.Actions[0].top().value)) {	//흑 > 백
					t = cur.Actions[1].top();
					cur.Actions[1].pop();
				}
				else if (abs(cur.Actions[1].top().value) == abs(cur.Actions[0].top().value)) {	//흑 == 백
					if (cur.Actions[0].top().value >= THRESHOLD) {
						t = cur.Actions[0].top();
						cur.Actions[0].pop();
					}
					else {
						t = cur.Actions[1].top();
						cur.Actions[1].pop();
					}
				}
				else {	//흑 < 백
					t = cur.Actions[0].top();
					cur.Actions[0].pop();
				}
			}
		

		if (cur.board[t.loc.first][t.loc.second] || check_33(cur, t.loc, 2)) continue;

		//탐색
		action result = Max_Value(ply(2, cur, t), endwait, d - 1, a, b);

		//시간 초과되었으면 탐색 종료
		if (result.value == CUTOFF) {
			sol.loc = { 0, 0 };
			sol.value = CUTOFF;
			return sol;
		}

		//탐색한 게 더 좋으면 sol 갱신
		if (sol.value > result.value) {
			sol.loc = t.loc;
			sol.value = result.value;
		}

		//Alpha beta pruning
		if (sol.value < a) {
			return sol;
		}

		//beta 갱신
		b = min(b, sol.value);
	}

	return sol;
}

state ply(int color, state cur, action best) {	//착수 함수
	state s;
	for (int i = 0; i <= 19; i++) {
		for (int j = 0; j <= 19; j++) {
			s.board[i][j] = cur.board[i][j];
			s.weight[i][j] = cur.weight[i][j];
		}
	}

	//착수
	s.board[best.loc.first][best.loc.second] = color;
	s.prevLoc = best.loc;
	s.Actions[0] = cur.Actions[0];
	s.Actions[1] = cur.Actions[1];
	s.score = 0;

	//내 돌에게 좋은 착수였으면 점수 획득. 방어는 조금 획득
	if ((color == 1 && best.value > 0) || (color == 2 && best.value < 0))
		s.score = cur.score + cur.weight[best.loc.first][best.loc.second];
	else if (color == 1 && best.value < 0)
		if (best.value < -THRESHOLD * 10)
			s.score = cur.score;
		else
			s.score = cur.score - best.value - 10;
	else if (color == 2 && best.value > 0)
		if (best.value > THRESHOLD * 10)
			s.score = cur.score;
		else
		s.score = cur.score - best.value + 10;
	
	s.weight[best.loc.first][best.loc.second] = OCCUPIED;

	s.A = countStone(s.board, best.loc);
	
	if(color == 1)	weightUpdate_B(s);
	else weightUpdate_W(s);

	return s;
}

void weightUpdate_B(state& s) {	//흑돌 가중치 갱신 (양수)
	int horizontal = s.A.right + s.A.left + 1; horizontal = horizontal > 4 ? 0 : horizontal;
	int vertical = s.A.up + s.A.down + 1; vertical = vertical > 4 ? 0 : vertical;
	int diagonal_RU = s.A.diag_leftDown + s.A.diag_rightUp + 1; diagonal_RU > 4 ? 0 : diagonal_RU;
	int diagonal_RD = s.A.diag_leftUp + s.A.diag_rightDown + 1; diagonal_RD > 4 ? 0 : diagonal_RD;

	int r = s.prevLoc.first, c = s.prevLoc.second;
	int newWeight;
	action P;

	//오른쪽
	int t = s.prevLoc.second + s.A.right + 1;
	if (horizontal == 4) newWeight = THRESHOLD * 20;
	else newWeight = (int)pow(10, horizontal - 1);
	if (s.A.Open_right && s.A.Open_left) {
		newWeight *= 10;
		if (horizontal == 3) newWeight = THRESHOLD;
	}


	if (t <= 19 && s.weight[s.prevLoc.first][t] != OCCUPIED) {
		s.weight[s.prevLoc.first][t] += newWeight;
		P = { {r, t}, s.weight[r][t] };
		s.Actions[1].push(P);
	}

	//왼쪽
	t = s.prevLoc.second - s.A.left - 1;
	if (horizontal == 4) newWeight = THRESHOLD * 20;
	else newWeight = (int)pow(10, horizontal - 1);
	if (s.A.Open_right && s.A.Open_left) {
		newWeight *= 10;
		if (horizontal == 3) newWeight = THRESHOLD;
	}

	if (t > 0 && s.weight[s.prevLoc.first][t] != OCCUPIED) {
		s.weight[s.prevLoc.first][t] += newWeight;
		P = { {r, t}, s.weight[r][t] };
		s.Actions[1].push(P);
	}

	//위
	t = s.prevLoc.first - s.A.up - 1;
	if (vertical == 4) newWeight = THRESHOLD * 20;
	else newWeight = (int)pow(10, vertical - 1);
	if (s.A.Open_up && s.A.Open_down) {
		newWeight *= 10;
		if (vertical == 3) newWeight = THRESHOLD;
	}


	if (t > 0 && s.weight[t][s.prevLoc.second] != OCCUPIED) {
		s.weight[t][s.prevLoc.second] += newWeight;
		P = { {t, c}, s.weight[t][c] };
		s.Actions[1].push(P);
	}


	//아래
	t = s.prevLoc.first + s.A.down + 1;
	if (vertical == 4) newWeight = THRESHOLD * 20;
	else newWeight = (int)pow(10, vertical - 1);
	if (s.A.Open_up && s.A.Open_down){
		newWeight *= 10;
		if (vertical == 3) newWeight = THRESHOLD;
	}	


	if (t <= 19 && s.weight[t][s.prevLoc.second] != OCCUPIED) {
		s.weight[t][s.prevLoc.second] += newWeight;
		P = { {t, c}, s.weight[t][c] };
		s.Actions[1].push(P);
	}

	//대각선 RU
	t = r - s.A.diag_rightUp - 1;
	int t2 = c + s.A.diag_rightUp + 1;
	if (diagonal_RU == 4) newWeight = THRESHOLD * 20;
	else newWeight = (int)pow(10, diagonal_RU - 1);
	if (s.A.Open_diag_RU && s.A.Open_diag_LD){
		newWeight *= 10;
		if (diagonal_RU == 3) newWeight = THRESHOLD;
	}

	if (t > 0 && t2 <= 19 && s.weight[t][t2] != OCCUPIED) {
		s.weight[t][t2] += newWeight;
		P = { {t, t2}, s.weight[t][t2] };
		s.Actions[1].push(P);
	}

	//대각선 LD
	t = r + s.A.diag_leftDown + 1;
	t2 = c - s.A.diag_leftDown - 1;
	if (diagonal_RU == 4) newWeight = THRESHOLD * 20;
	else newWeight = (int)pow(10, diagonal_RU - 1);
	if (s.A.Open_diag_RU && s.A.Open_diag_LD) {
		newWeight *= 10;
		if (diagonal_RU == 3) newWeight = THRESHOLD;
	}

	if (t <= 19 && t2 > 0 && s.weight[t][t2] != OCCUPIED) {
		s.weight[t][t2] += newWeight;
		P = { {t, t2}, s.weight[t][t2] };
		s.Actions[1].push(P);
	}

	//대각선 RD
	t = r + s.A.diag_rightDown + 1;
	t2 = c + s.A.diag_rightDown + 1;
	if (diagonal_RD == 4) newWeight = THRESHOLD * 20;
	else newWeight = (int)pow(10, diagonal_RD - 1);
	if (s.A.Open_diag_RD && s.A.Open_diag_LU) {
		newWeight *= 10;
		if (diagonal_RD == 3) newWeight = THRESHOLD;
	}

	if (t <= 19 && t2 <= 19 && s.weight[t][t2] != OCCUPIED) {
		s.weight[t][t2] += newWeight;
		P = { {t, t2}, s.weight[t][t2] };
		s.Actions[1].push(P);
	}

	//대각선 LU
	t = r - s.A.diag_leftUp - 1;
	t2 = c - s.A.diag_leftUp - 1;
	if (diagonal_RD == 4) newWeight = THRESHOLD * 20;
	else newWeight = (int)pow(10, diagonal_RD - 1);
	if (s.A.Open_diag_RD && s.A.Open_diag_LU) {
		newWeight *= 10;
		if (diagonal_RD == 3) newWeight = THRESHOLD;
	}

	if (t > 0 && t2 > 0 && s.weight[t][t2] != OCCUPIED) {
		s.weight[t][t2] += newWeight;
		P = { {t, t2}, s.weight[t][t2] };
		s.Actions[1].push(P);
	}
}

void weightUpdate_W(state& s) { //백돌 가중치 갱신 (음수)
	int horizontal = s.A.right + s.A.left + 1; horizontal = horizontal > 4 ? 0 : horizontal;
	int vertical = s.A.up + s.A.down + 1; vertical = vertical > 4 ? 0 : vertical;
	int diagonal_RU = s.A.diag_leftDown + s.A.diag_rightUp + 1; diagonal_RU > 4 ? 0 : diagonal_RU;
	int diagonal_RD = s.A.diag_leftUp + s.A.diag_rightDown + 1; diagonal_RD > 4 ? 0 : diagonal_RD;

	int r = s.prevLoc.first, c = s.prevLoc.second;
	int newWeight;
	action P;

	//오른쪽
	int t = s.prevLoc.second + s.A.right + 1;
	if (horizontal == 4) newWeight = THRESHOLD * 20;
	else newWeight = (int)pow(10, horizontal - 1);
	if (s.A.Open_right && s.A.Open_left) {
		newWeight *= 10;
		if (horizontal == 3) newWeight = THRESHOLD;
	}
	

	if (t <= 19 && s.weight[s.prevLoc.first][t] != OCCUPIED) {
		s.weight[s.prevLoc.first][t] -= newWeight;
		P = { {r, t}, s.weight[r][t] };
		s.Actions[0].push(P);
	}

	//왼쪽
	t = s.prevLoc.second - s.A.left - 1;
	if (horizontal == 4) newWeight = THRESHOLD * 20;
	else newWeight = (int)pow(10, horizontal - 1);
	if (s.A.Open_right && s.A.Open_left) {
		newWeight *= 10;
		if (horizontal == 3) newWeight = THRESHOLD;
	}

	if (t > 0 && s.weight[s.prevLoc.first][t] != OCCUPIED) {
		s.weight[s.prevLoc.first][t] -= newWeight;
		P = { {r, t}, s.weight[r][t] };
		s.Actions[0].push(P);
	}

	//위
	t = s.prevLoc.first - s.A.up - 1;
	if (vertical == 4) newWeight = THRESHOLD * 20;
	else newWeight = (int)pow(10, vertical - 1);
	if (s.A.Open_up && s.A.Open_down) {
		newWeight *= 10;
		if (vertical == 3) newWeight = THRESHOLD;
	}

	if (t > 0 && s.weight[t][s.prevLoc.second] != OCCUPIED) {
		s.weight[t][s.prevLoc.second] -= newWeight;
		P = { {t, c}, s.weight[t][c] };
		s.Actions[0].push(P);
	}


	//아래
	t = s.prevLoc.first + s.A.down + 1;
	if (vertical == 4) newWeight = THRESHOLD * 20;
	else newWeight = (int)pow(10, vertical - 1);
	if (s.A.Open_up && s.A.Open_down) {
		newWeight *= 10;
		if (vertical == 3) newWeight = THRESHOLD;
	}

	if (t <= 19 && s.weight[t][s.prevLoc.second] != OCCUPIED) {
		s.weight[t][s.prevLoc.second] -= newWeight;
		P = { {t, c}, s.weight[t][c] };
		s.Actions[0].push(P);
	}

	//대각선 RU
	t = r - s.A.diag_rightUp - 1;
	int t2 = c + s.A.diag_rightUp + 1;
	if (diagonal_RU == 4) newWeight = THRESHOLD * 20;
	else newWeight = (int)pow(10, diagonal_RU - 1);
	if (s.A.Open_diag_RU && s.A.Open_diag_LD) {
		newWeight *= 10;
		if (diagonal_RU == 3) newWeight = THRESHOLD;
	}

	if (t > 0 && t2 <= 19 && s.weight[t][t2] != OCCUPIED) {
		s.weight[t][t2] -= newWeight;
		P = { {t, t2}, s.weight[t][t2] };
		s.Actions[0].push(P);
	}

	//대각선 LD
	t = r + s.A.diag_leftDown + 1;
	t2 = c - s.A.diag_leftDown - 1;
	if (diagonal_RU == 4) newWeight = THRESHOLD * 20;
	else newWeight = (int)pow(10, diagonal_RU - 1);
	if (s.A.Open_diag_RU && s.A.Open_diag_LD) {
		newWeight *= 10;
		if (diagonal_RU == 3) newWeight = THRESHOLD;
	}

	if (t <= 19 && t2 > 0 && s.weight[t][t2] != OCCUPIED) {
		s.weight[t][t2] -= newWeight;
		P = { {t, t2}, s.weight[t][t2] };
		s.Actions[0].push(P);
	}

	//대각선 RD
	t = r + s.A.diag_rightDown + 1;
	t2 = c + s.A.diag_rightDown + 1;
	if (diagonal_RD == 4) newWeight = THRESHOLD * 20;
	else newWeight = (int)pow(10, diagonal_RD - 1);
	if (s.A.Open_diag_RD && s.A.Open_diag_LU) {
		newWeight *= 10;
		if (diagonal_RD == 3) newWeight = THRESHOLD;
	}

	if (t <= 19 && t2 <= 19 && s.weight[t][t2] != OCCUPIED) {
		s.weight[t][t2] -= newWeight;
		P = { {t, t2}, s.weight[t][t2] };
		s.Actions[0].push(P);
	}

	//대각선 LU
	t = r - s.A.diag_leftUp - 1;
	t2 = c - s.A.diag_leftUp - 1;
	if (diagonal_RD == 4) newWeight = THRESHOLD * 20;
	else newWeight = (int)pow(10, diagonal_RD - 1);
	if (s.A.Open_diag_RD && s.A.Open_diag_LU) {
		newWeight *= 10;
		if (diagonal_RD == 3) newWeight = THRESHOLD;
	}

	if (t > 0 && t2 > 0 && s.weight[t][t2] != OCCUPIED) {
		s.weight[t][t2] -= newWeight;
		P = { {t, t2}, s.weight[t][t2] };
		s.Actions[0].push(P);
	}
}