// [미구현]
// 1턴만 구현 -> 5턴까지 미구현
// 인공지능과 대결 미구현 > @ 가 있는 상자 선택, 배팅코인 선택 
// 끝나는 지점에서 혼자게임 / 인공지능과 게임 / 끝내기 를 선택하는 부분 
// 3 /10 = 30%

#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

#define N 15	// 상자 배열 크기
#define L 3		// 1번 상자 위치, 초기 섞는 횟수 

void printing();
void setting(BOX, BOX, BOX);
void start_p(BOX, BOX, BOX);
bool bet_result();	// 미구현
int betting();		// 미구현

// 배팅 결과 (성공, 실패)
bool bet_result() {

}

// 배팅_금액
int betting() {
	// 성공

	// 실패

}

// 상자
typedef struct {
	int pol;	// 현위치
	int det;	// 진행방향
}BOX;

// @ 들어있는 상자 위치
int key = L;

// player의 key 값 ( 상자 번호 )
int p_key = 1;

// 상자 배열
char arr[N] = { 0 };

// 초기 사용자가 가지고 있는 코인
int coin = 500;

// 상자 배열 출력
void printing() {
	printf("\n");
	for (int i = 0; i < N; i++) {
		printf("%c", arr[i]);
	}
	printf("\n");
}

// # 교환, 왼쪽에 있는 # : box_1, 오른쪽에 있는 # : box_2
// 교환과 상관없는 #은 유지 : maintain
void setting(BOX box_1, BOX box_2, BOX maintain) {

	int t = 10;

	// key 가 교환하려는 #상자에 있는 경우 -> 위치 변경
	// 아니면 그대로 유지
	if (key == box_1.pol) {
		key = box_2.pol;
	}
	else if (key == box_2.pol) {
		key = box_1.pol;
	}
	else {	// 굳이 안써줘도 됌
		key = maintain.pol;
	}

	int size = box_2.pol - box_1.pol;	// 두 개의 # 거리
	box_1.det = 1;	// 왼쪽 # 진행방향: 오른쪽 (+1)
	box_2.det = -1;	// 오른쪽 # 진행방향: 왼쪽 (-1)

	for (int i = 0; i < size; i++) {
		// 10 밀리세컨즈 지나고 지움
		Sleep(t);
		system("cls");

		// 배열에서 #위치 지움
		arr[box_1.pol] = '_';
		arr[box_2.pol] = '_';

		// 다음 위치 저장
		box_1.pol = box_1.pol + box_1.det;
		box_2.pol = box_2.pol + box_2.det;

		// 새로운 위치에 # 
		arr[box_1.pol] = '#';
		arr[box_2.pol] = '#';
		arr[maintain.pol] = '#';

		printing();
	}
	t--; // 턴이 증가할때마다 속도 점점 빠르게
}

// 초기 화면
void start_p(BOX box1, BOX box2, BOX box3) {

	for (int i = 0; i < N; i++) {
		arr[i] = '_';
	}

	// ___#___#___#___
	arr[box1.pol] = '#';
	arr[box2.pol] = '#';
	arr[box3.pol] = '#';


	printing();
}

// 랜덤하게 상자섞기
void randomMix(BOX box1, BOX box2, BOX box3) {

	int randNum = 0, cnt = L;	// randNum: 상자 섞을 수 있는 경우를 랜덤하게 뽑음, cnt: 섞는 횟수
	srand((unsigned int)time(NULL));

	for (int i = 0; i < cnt; i++) {
		// Sleep(3000); // 확인용
		randNum = rand() % 4 + 1;

		// 상자를 섞을 수 있는 경우( 1과 2 , 2와 3, 1과 3의 상자가 섞이는 경우 )
		switch (randNum) {
		case 1:
			setting(box1, box2, box3); continue;
		case 2:
			setting(box2, box3, box1); continue;
		case 3:
			setting(box1, box3, box2); continue;
		}
		cnt++;	// 1 턴이 지나갈때 마다 상자를 섞는 횟수 증가
	}
}

int main(void) {
	// @ 위치
	printf("@위치는 [%d]상자에 있습니다.\n", p_key);
	Sleep(1000);
	system("cls");

	BOX box1 = { L };		// L = 3
	BOX box2 = { 2 * L + 1 };	// 7
	BOX box3 = { 3 * L + 2 };	// 11

	// 초기 화면
	start_p(box1, box2, box3);

	// 상자 섞기
	randomMix(box1, box2, box3);

	// @가 어느 상자에 들어있는지 확인용
	int k = 0;
	printf("k = ");
	scanf_s("%d", &k);

	// 상자 배열을 1번상자, 2번상자, 3번상자로 바꿈
	switch (key) {
	case 3:
		p_key = 1; break;
	case 7:
		p_key = 2; break;
	case 11:
		p_key = 3; break;
	}

	// key 의 위치 확인용
	if (k == p_key) {
		printf("맞음\n");	// 코인 얻음
	}
	else
		printf("@이 없음\n");	// 코인 잃음


	return 0;
}