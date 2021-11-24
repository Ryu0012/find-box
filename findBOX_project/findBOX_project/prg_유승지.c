#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

#define N 15	// 상자 배열 크기
#define L 3		// 1번 상자 위치

void printing();
void setting(BOX, BOX, BOX);
void start_p(BOX, BOX, BOX);
bool plyerPlay();
void withPlay();
bool withPlay_select();
void bettingResult();
void gameOver();


// @ 들어있는 상자 위치
int key = L;

// @이가 들어있는 상자번호
int p_key = 1;

// playerKey
int playerKey = 0;

// 상자 배열
char arr[N] = { 0 };

// 초기 사용자가 가지고 있는 코인
int playerCoin = 500;

// 인공지능이 가지고 있는 코인
int selectCoin = 500;

// 섞는 속도, 횟수
int t = 10, cnt = 3;

// 상자
typedef struct {
	int pol;	// 현위치
	int det;	// 진행방향
}BOX;



// 상자 배열 출력
void printing() {
	printf("\n");
	for (int i = 0; i < 4; i++) {
		printf(" ");
	}
	for (int i = 0; i < N; i++) {
		printf("%c", arr[i]);
	}
	printf("\n");
}

// 게임 종료
bool gameover = 0;

void gameOver() {
	printf("\n");
	printf("     ■■       ■      ■  ■   ■■■        ■■    ■    ■  ■■■   ■■      \n");
	printf("   ■         ■  ■   ■ ■ ■  ■          ■    ■   ■  ■   ■       ■  ■    \n");
	printf("   ■    ■   ■■■   ■    ■  ■■■      ■    ■    ■■    ■■■   ■ ■     \n");
	printf("     ■■     ■  ■   ■    ■  ■■■        ■■       ■     ■■■   ■  ■    \n");
	Sleep(1500);
	gameover = 1;
}

// WIN
void win() {
	printf("\n");
	printf("   ■    ■  ■  ■   ■     \n");
	printf("   ■ ■ ■  ■  ■■ ■     \n");
	printf("   ■ ■ ■  ■  ■ ■■     \n");
	printf("    ■ ■    ■  ■   ■     \n");
	printf("\n");
}

// LOSE
void lose() {
	printf("\n");
	printf("   ■       ■■   ■■■   ■■■   \n");
	printf("   ■      ■  ■  ■■■   ■       \n");
	printf("   ■      ■  ■      ■   ■■■   \n");
	printf("   ■■■   ■■   ■■■   ■■■   \n");
	printf("\n");

}


// # 교환, 왼쪽에 있는 # : box_1, 오른쪽에 있는 # : box_2
// 교환과 상관없는 #은 유지 : maintain
void setting(BOX box_1, BOX box_2, BOX maintain) {

	// key 가 교환하려는 #상자에 있는 경우 -> 위치 변경
	// 아니면 그대로 유지
	if (key == box_1.pol) {
		key = box_2.pol;
	}
	else if (key == box_2.pol) {
		key = box_1.pol;
	}
	else {	
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

	// 전에 섞은 경우 제외
	int randNum = 0, n_randNum = 0;	// randNum: 상자 섞을 수 있는 경우를 랜덤하게 뽑음, cnt: 섞는 횟수
	srand((unsigned int)time(NULL));

	for (int i = 0; i < cnt; i++) {
		// Sleep(3000); // 확인용
		randNum = rand() % 3 + 1;
		
		if (randNum == n_randNum) {
			i--;
			continue;
		}
		else n_randNum = randNum;

		// 상자를 섞을 수 있는 경우( 1과 2 , 2와 3, 1과 3의 상자가 섞이는 경우 )
		switch (randNum) {
		case 1:
			setting(box1, box2, box3); continue;
		case 2:
			setting(box2, box3, box1); continue;
		case 3:
			setting(box1, box3, box2); continue;
		}
	}
	cnt++;	// 1 턴이 지나갈때 마다 상자를 섞는 횟수 증가
	t--;	// 1 턴이 지나고 섞는 속도 증가
}

void playerResult(bool bettingResult, int bettingCoin, int turn) {
	// player 배팅 결과
	printf("  @는 _%d_상자에 있었습니다.\n\n", p_key);

	if (bettingResult) {
		// betting에 성공하셨습니다.
		playerCoin = playerCoin + (bettingCoin * turn);
		printf("\n");
		printf("  b"); Sleep(100); printf("e"); Sleep(100); printf("t"); Sleep(100); printf("t"); Sleep(100);
		printf("i"); Sleep(100); printf("n"); Sleep(100); printf("g"); Sleep(100);
		printf("에"); Sleep(100); printf(" 성"); Sleep(100); printf("공"); Sleep(100); printf("하"); Sleep(100);
		printf("하"); Sleep(100); printf("셨"); Sleep(100); printf("습"); Sleep(100); printf("니"); Sleep(100); printf("다.\n"); Sleep(100);
		printf("  %d * %d = %d 코인을 얻었습니다.\n", bettingCoin, turn, bettingCoin * turn);
	}
	else {
		playerCoin -= bettingCoin;
		// betting에 실패하셨습니다.
		printf("\n");
		printf("  b"); Sleep(100); printf("e"); Sleep(100); printf("t"); Sleep(100); printf("t"); Sleep(100);
		printf("i"); Sleep(100); printf("n"); Sleep(100); printf("g"); Sleep(100);
		printf("에"); Sleep(100); printf(" 실"); Sleep(100); printf("패"); Sleep(100); printf("하"); Sleep(100);
		printf("하"); Sleep(100); printf("셨"); Sleep(100); printf("습"); Sleep(100); printf("니"); Sleep(100); printf("다.\n"); Sleep(100);
		printf("  %d 코인을 잃었습니다.\n", bettingCoin);
	}

	int t = 0;

	printf("\n\n");
	printf("  현"); Sleep(100); printf("재"); Sleep(100); printf(" 가"); Sleep(100); printf("지"); Sleep(100); printf("고"); Sleep(100);
	printf(" 있"); Sleep(100); printf("는"); Sleep(100);
	printf(" 코"); Sleep(100); printf("인"); Sleep(100); printf("은"); Sleep(100); printf(" %d", playerCoin); Sleep(100);
	printf(" 입"); Sleep(100); printf("니"); Sleep(100); printf("다.\n"); Sleep(100);
	printf("  기다리면 다음으로 넘어갑니다.\n");

	Sleep(3500);
	system("cls");
}


bool playerPlay(int* bettingCoin) {

	// playerKey = 0
	printf("\n");
	printf("	몇 번째 상자를 고르시겠습니까?\n");
	printf("	[ 1번상자 = 1, 2번상자 = 2, 3번상자 = 3 ]\n");
	printf("  => ");
	while (1) {
		scanf_s("%d", &playerKey);
		if(playerKey == 1 || playerKey == 2 || playerKey == 3){
			break;
		}
		else {
			printf("\n");
			printf("	1, 2, 3 중에 골라주세요.\n");
		}
	}
	printf("\n");

	printf("	현재 가지고 있는 코인은 %d입니다.\n", playerCoin);
	printf("	몇 코인을 betting 하시겠습니까? (양수값으로 입력해주세요)\n");
	printf("  => ");
	while (1) {
		scanf_s("%d", &*bettingCoin);
		if (1 <= *bettingCoin && *bettingCoin <= playerCoin) {
			break;
		}
		else {
			printf("\n");
			printf("	1코인이상, 가지고 있는 코인이하로 해주세요.\n");
		}
	}
	printf("\n");

	// 상자 배열을 1번상자, 2번상자, 3번상자로 바꿈
	switch (key) {
	case 3:
		p_key = 1; break;
	case 7:
		p_key = 2; break;
	case 11:
		p_key = 3; break;
	}

	if (playerKey == p_key) return true;
	else return false;
}

// 함께 게임 _ 인공지능 선택
bool withPlay_select(int* select_bettingCoin, int size) {
	int select_key = 0;	// 인공지능이 고른 상자
	srand((unsigned int)time(NULL));

	if (size == 5 || playerKey != p_key) {
		select_key = p_key;
		*select_bettingCoin = selectCoin;
	}
	else {
		while (1) {
			select_key = rand() % 3 + 1;
			if (select_key == playerKey) continue;
			else *select_bettingCoin = rand() % selectCoin + 1; break;
		}
	}	

	printf("	인공지능은 [ %d ]번째 상자를 골랐습니다.\n", select_key);
	printf("	인공지능은 [ %d ]코인을 betting 했습니다.\n", *select_bettingCoin);
	printf("\n");
	
	if (p_key == select_key) return true;
	else return false;
}

void withPlay(BOX box1, BOX box2, BOX box3) {

	bool select_p = 0, player_p = 0;

	for (int turn = 1; turn <= 5; turn++) {

		if (playerCoin <= 0){
			// 플레이어 코인 0 이하
			printf("  player 코인이 0이하가 되었습니다.\n\n");
			gameOver(); break;
		}
		else if (selectCoin <= 0) {
			// 인공지능 코인이 0 이하
			printf("  player가 이겼습니다.\n\n");
			win();
			break;
		}
		else {
			int select_bettingCoin = 0;
			int bettingCoin = 0;
			printf("\n");
			printf("	%d 턴 입니다.\n\n", turn);
			printf("	[ @위치는 _%d_상자에 있습니다.]\n", p_key);
			Sleep(2500);
			system("cls");

			// 초기 화면
			start_p(box1, box2, box3);

			// 상자 섞기
			randomMix(box1, box2, box3);
			printf("\n");

			// 인공지능 선택 결과
			player_p = playerPlay(&bettingCoin);
			select_p = withPlay_select(&select_bettingCoin, turn);

			printf("  [ @는 _%d_상자에 있었습니다.]\n\n", p_key);

			// 둘다 성공, 둘중 하나 실패
			if (select_p == player_p) {
				// 둘다 성공하는 경우
				playerCoin = playerCoin + (bettingCoin * turn);
				selectCoin = selectCoin + (select_bettingCoin * turn);

				printf("\n");
				printf("  모두 betting에 성공하셨습니다.\n");
				printf("  betting한 금액을 얻습니다.\n\n");
				printf("  인공지능은 %d * %d = %d코인을 얻었습니다.\n", select_bettingCoin, turn, select_bettingCoin * turn);
				printf("  player는 %d * %d = %d 코인을 얻었습니다.\n", bettingCoin, turn, bettingCoin * turn);
			}
			else if (player_p) {
				playerCoin = playerCoin + (select_bettingCoin * turn);
				selectCoin -= (select_bettingCoin * turn);
				printf("  이"); Sleep(150); printf("겼"); Sleep(150); printf("습"); Sleep(150); printf("니"); Sleep(150); printf("다.\n"); Sleep(300);
				printf("  player는 %d * %d = %d 코인을 얻었습니다.\n", select_bettingCoin, turn, select_bettingCoin);
			}
			else if (select_p) {
				selectCoin = selectCoin + (bettingCoin * turn);
				playerCoin -= (bettingCoin * turn);
				printf("  졌"); Sleep(150); printf("습"); Sleep(150); printf("니"); Sleep(150); printf("다.\n"); Sleep(300);
				printf("  player는 %d * %d = %d 코인을 잃었습니다.\n", bettingCoin, turn, bettingCoin * turn);
			}

			printf("\n");
			// 인공지능이 가지고 있는 코인 출력
			printf("  인"); Sleep(100); printf("공"); Sleep(100); printf("지"); Sleep(100); printf("능"); Sleep(100); printf("이"); Sleep(100);
			printf(" 가"); Sleep(100); printf("지"); Sleep(100); printf("고"); Sleep(100); printf(" 있"); Sleep(100); printf("는"); Sleep(100);
			printf(" 코"); Sleep(100); printf("인"); Sleep(100); printf("은"); Sleep(100); printf(" %d", selectCoin); Sleep(100);
			printf(" 입"); Sleep(100); printf("니"); Sleep(100); printf("다.\n"); Sleep(100);

			printf("\n");
			// 현재가지고 있는 코인 출력
			printf("  현"); Sleep(100); printf("재"); Sleep(100); printf(" 가"); Sleep(100); printf("지"); Sleep(100); printf("고"); Sleep(100);
			printf(" 있"); Sleep(100); printf("는"); Sleep(100); 
			printf(" 코"); Sleep(100); printf("인"); Sleep(100); printf("은"); Sleep(100); printf(" %d", playerCoin); Sleep(100);
			printf(" 입"); Sleep(100); printf("니"); Sleep(100); printf("다.\n"); Sleep(100);

			printf("\n");
			printf("  기다리면 다음으로 넘어갑니다.\n");

			Sleep(8000);
			system("cls");

			if (turn == 5) {
				// 5턴이 모두 끝났을때
				if (playerCoin > selectCoin) {
					printf("  player가 이겼습니다.\n");
					win();
				}
				else if (playerCoin < selectCoin) {
					printf("  player가 졌습니다.\n");
					lose();
				}
			}
		}		
	}
}

void Start() {

	printf("[ @이를 찾아라! ]\n");


}

int main(void) {
	// 혼자게임 / 인공지능과 함께게임 / 나가기 => 혼자 게임 하는 경우 1, 인공지능과 게임 2, 나가기 0

	int startGame = 0;
	// @ 위치
	// 턴 ( 총 5턴 )

	// player bettingCoin
	int bettingCoin = 0, bettingResult = 0;

	BOX box1 = { L };		// L = 3
	BOX box2 = { 2 * L + 1 };	// 7
	BOX box3 = { 3 * L + 2 };	// 11

	while (1) {		

		cnt = 3;	// 섞는 횟수 3으로 초기화

		printf("\n");
		printf("  playerCoin = %d\n\n", playerCoin);
		printf("	혼자게임을 원하시면 1 \n\n");
		printf("	인공지능과 함께게임을 원하시면 2\n\n");
		printf("	나가기 0\n\n");
		printf("  => ");

		if (gameover) {
			startGame = 0;
		}
		else {
			scanf_s("%d", &startGame);
		}

		system("cls");

		if (startGame == 1) {
			// alonePlay
			for (int turn = 1; turn <= 5; turn++) {

				if (playerCoin <= 0) {
					gameOver(); break;
				}

				else {
					printf("\n");
					printf("	%d 턴 입니다.\n", turn);
					printf("	@위치는 _%d_상자에 있습니다.\n", p_key);
					Sleep(2000);
					system("cls");

					// 초기 화면
					start_p(box1, box2, box3);

					// 상자 섞기
					randomMix(box1, box2, box3);
					printf("\n");

					bettingResult = playerPlay(&bettingCoin);
					playerResult(bettingResult, bettingCoin, turn);
				}
			}
		}
		else if (startGame == 2) {
			// withPlay
			withPlay(box1, box2, box3);
		}

		else if (startGame == 0) {
			printf("\n");
			printf("  게임을 종료합니다.\n");
			printf(  "player coin = %d\n", playerCoin);
			break;
		}
	}
	
	return 0;
}