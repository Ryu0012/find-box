#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

#define N 15	// ���� �迭 ũ��
#define L 3		// 1�� ���� ��ġ

void printing();
void setting(BOX, BOX, BOX);
void start_p(BOX, BOX, BOX);
bool plyerPlay();
void withPlay();
bool withPlay_select();
void bettingResult();
void gameOver();


// @ ����ִ� ���� ��ġ
int key = L;

// @�̰� ����ִ� ���ڹ�ȣ
int p_key = 1;

// playerKey
int playerKey = 0;

// ���� �迭
char arr[N] = { 0 };

// �ʱ� ����ڰ� ������ �ִ� ����
int playerCoin = 500;

// �ΰ������� ������ �ִ� ����
int selectCoin = 500;

// ���� �ӵ�, Ƚ��
int t = 10, cnt = 3;

// ����
typedef struct {
	int pol;	// ����ġ
	int det;	// �������
}BOX;



// ���� �迭 ���
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

// ���� ����
bool gameover = 0;

void gameOver() {
	printf("\n");
	printf("     ���       ��      ��  ��   ����        ���    ��    ��  ����   ���      \n");
	printf("   ��         ��  ��   �� �� ��  ��          ��    ��   ��  ��   ��       ��  ��    \n");
	printf("   ��    ��   ����   ��    ��  ����      ��    ��    ���    ����   �� ��     \n");
	printf("     ���     ��  ��   ��    ��  ����        ���       ��     ����   ��  ��    \n");
	Sleep(1500);
	gameover = 1;
}

// WIN
void win() {
	printf("\n");
	printf("   ��    ��  ��  ��   ��     \n");
	printf("   �� �� ��  ��  ��� ��     \n");
	printf("   �� �� ��  ��  �� ���     \n");
	printf("    �� ��    ��  ��   ��     \n");
	printf("\n");
}

// LOSE
void lose() {
	printf("\n");
	printf("   ��       ���   ����   ����   \n");
	printf("   ��      ��  ��  ����   ��       \n");
	printf("   ��      ��  ��      ��   ����   \n");
	printf("   ����   ���   ����   ����   \n");
	printf("\n");

}


// # ��ȯ, ���ʿ� �ִ� # : box_1, �����ʿ� �ִ� # : box_2
// ��ȯ�� ������� #�� ���� : maintain
void setting(BOX box_1, BOX box_2, BOX maintain) {

	// key �� ��ȯ�Ϸ��� #���ڿ� �ִ� ��� -> ��ġ ����
	// �ƴϸ� �״�� ����
	if (key == box_1.pol) {
		key = box_2.pol;
	}
	else if (key == box_2.pol) {
		key = box_1.pol;
	}
	else {	
		key = maintain.pol;
	}

	int size = box_2.pol - box_1.pol;	// �� ���� # �Ÿ�
	box_1.det = 1;	// ���� # �������: ������ (+1)
	box_2.det = -1;	// ������ # �������: ���� (-1)

	for (int i = 0; i < size; i++) {
		// 10 �и������� ������ ����
		Sleep(t);
		system("cls");

		// �迭���� #��ġ ����
		arr[box_1.pol] = '_';
		arr[box_2.pol] = '_';

		// ���� ��ġ ����
		box_1.pol = box_1.pol + box_1.det;
		box_2.pol = box_2.pol + box_2.det;

		// ���ο� ��ġ�� # 
		arr[box_1.pol] = '#';
		arr[box_2.pol] = '#';
		arr[maintain.pol] = '#';

		printing();
	}
}

// �ʱ� ȭ��
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

// �����ϰ� ���ڼ���
void randomMix(BOX box1, BOX box2, BOX box3) {

	// ���� ���� ��� ����
	int randNum = 0, n_randNum = 0;	// randNum: ���� ���� �� �ִ� ��츦 �����ϰ� ����, cnt: ���� Ƚ��
	srand((unsigned int)time(NULL));

	for (int i = 0; i < cnt; i++) {
		// Sleep(3000); // Ȯ�ο�
		randNum = rand() % 3 + 1;
		
		if (randNum == n_randNum) {
			i--;
			continue;
		}
		else n_randNum = randNum;

		// ���ڸ� ���� �� �ִ� ���( 1�� 2 , 2�� 3, 1�� 3�� ���ڰ� ���̴� ��� )
		switch (randNum) {
		case 1:
			setting(box1, box2, box3); continue;
		case 2:
			setting(box2, box3, box1); continue;
		case 3:
			setting(box1, box3, box2); continue;
		}
	}
	cnt++;	// 1 ���� �������� ���� ���ڸ� ���� Ƚ�� ����
	t--;	// 1 ���� ������ ���� �ӵ� ����
}

void playerResult(bool bettingResult, int bettingCoin, int turn) {
	// player ���� ���
	printf("  @�� _%d_���ڿ� �־����ϴ�.\n\n", p_key);

	if (bettingResult) {
		// betting�� �����ϼ̽��ϴ�.
		playerCoin = playerCoin + (bettingCoin * turn);
		printf("\n");
		printf("  b"); Sleep(100); printf("e"); Sleep(100); printf("t"); Sleep(100); printf("t"); Sleep(100);
		printf("i"); Sleep(100); printf("n"); Sleep(100); printf("g"); Sleep(100);
		printf("��"); Sleep(100); printf(" ��"); Sleep(100); printf("��"); Sleep(100); printf("��"); Sleep(100);
		printf("��"); Sleep(100); printf("��"); Sleep(100); printf("��"); Sleep(100); printf("��"); Sleep(100); printf("��.\n"); Sleep(100);
		printf("  %d * %d = %d ������ ������ϴ�.\n", bettingCoin, turn, bettingCoin * turn);
	}
	else {
		playerCoin -= bettingCoin;
		// betting�� �����ϼ̽��ϴ�.
		printf("\n");
		printf("  b"); Sleep(100); printf("e"); Sleep(100); printf("t"); Sleep(100); printf("t"); Sleep(100);
		printf("i"); Sleep(100); printf("n"); Sleep(100); printf("g"); Sleep(100);
		printf("��"); Sleep(100); printf(" ��"); Sleep(100); printf("��"); Sleep(100); printf("��"); Sleep(100);
		printf("��"); Sleep(100); printf("��"); Sleep(100); printf("��"); Sleep(100); printf("��"); Sleep(100); printf("��.\n"); Sleep(100);
		printf("  %d ������ �Ҿ����ϴ�.\n", bettingCoin);
	}

	int t = 0;

	printf("\n\n");
	printf("  ��"); Sleep(100); printf("��"); Sleep(100); printf(" ��"); Sleep(100); printf("��"); Sleep(100); printf("��"); Sleep(100);
	printf(" ��"); Sleep(100); printf("��"); Sleep(100);
	printf(" ��"); Sleep(100); printf("��"); Sleep(100); printf("��"); Sleep(100); printf(" %d", playerCoin); Sleep(100);
	printf(" ��"); Sleep(100); printf("��"); Sleep(100); printf("��.\n"); Sleep(100);
	printf("  ��ٸ��� �������� �Ѿ�ϴ�.\n");

	Sleep(3500);
	system("cls");
}


bool playerPlay(int* bettingCoin) {

	// playerKey = 0
	printf("\n");
	printf("	�� ��° ���ڸ� ���ðڽ��ϱ�?\n");
	printf("	[ 1������ = 1, 2������ = 2, 3������ = 3 ]\n");
	printf("  => ");
	while (1) {
		scanf_s("%d", &playerKey);
		if(playerKey == 1 || playerKey == 2 || playerKey == 3){
			break;
		}
		else {
			printf("\n");
			printf("	1, 2, 3 �߿� ����ּ���.\n");
		}
	}
	printf("\n");

	printf("	���� ������ �ִ� ������ %d�Դϴ�.\n", playerCoin);
	printf("	�� ������ betting �Ͻðڽ��ϱ�? (��������� �Է����ּ���)\n");
	printf("  => ");
	while (1) {
		scanf_s("%d", &*bettingCoin);
		if (1 <= *bettingCoin && *bettingCoin <= playerCoin) {
			break;
		}
		else {
			printf("\n");
			printf("	1�����̻�, ������ �ִ� �������Ϸ� ���ּ���.\n");
		}
	}
	printf("\n");

	// ���� �迭�� 1������, 2������, 3�����ڷ� �ٲ�
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

// �Բ� ���� _ �ΰ����� ����
bool withPlay_select(int* select_bettingCoin, int size) {
	int select_key = 0;	// �ΰ������� �� ����
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

	printf("	�ΰ������� [ %d ]��° ���ڸ� ������ϴ�.\n", select_key);
	printf("	�ΰ������� [ %d ]������ betting �߽��ϴ�.\n", *select_bettingCoin);
	printf("\n");
	
	if (p_key == select_key) return true;
	else return false;
}

void withPlay(BOX box1, BOX box2, BOX box3) {

	bool select_p = 0, player_p = 0;

	for (int turn = 1; turn <= 5; turn++) {

		if (playerCoin <= 0){
			// �÷��̾� ���� 0 ����
			printf("  player ������ 0���ϰ� �Ǿ����ϴ�.\n\n");
			gameOver(); break;
		}
		else if (selectCoin <= 0) {
			// �ΰ����� ������ 0 ����
			printf("  player�� �̰���ϴ�.\n\n");
			win();
			break;
		}
		else {
			int select_bettingCoin = 0;
			int bettingCoin = 0;
			printf("\n");
			printf("	%d �� �Դϴ�.\n\n", turn);
			printf("	[ @��ġ�� _%d_���ڿ� �ֽ��ϴ�.]\n", p_key);
			Sleep(2500);
			system("cls");

			// �ʱ� ȭ��
			start_p(box1, box2, box3);

			// ���� ����
			randomMix(box1, box2, box3);
			printf("\n");

			// �ΰ����� ���� ���
			player_p = playerPlay(&bettingCoin);
			select_p = withPlay_select(&select_bettingCoin, turn);

			printf("  [ @�� _%d_���ڿ� �־����ϴ�.]\n\n", p_key);

			// �Ѵ� ����, ���� �ϳ� ����
			if (select_p == player_p) {
				// �Ѵ� �����ϴ� ���
				playerCoin = playerCoin + (bettingCoin * turn);
				selectCoin = selectCoin + (select_bettingCoin * turn);

				printf("\n");
				printf("  ��� betting�� �����ϼ̽��ϴ�.\n");
				printf("  betting�� �ݾ��� ����ϴ�.\n\n");
				printf("  �ΰ������� %d * %d = %d������ ������ϴ�.\n", select_bettingCoin, turn, select_bettingCoin * turn);
				printf("  player�� %d * %d = %d ������ ������ϴ�.\n", bettingCoin, turn, bettingCoin * turn);
			}
			else if (player_p) {
				playerCoin = playerCoin + (select_bettingCoin * turn);
				selectCoin -= (select_bettingCoin * turn);
				printf("  ��"); Sleep(150); printf("��"); Sleep(150); printf("��"); Sleep(150); printf("��"); Sleep(150); printf("��.\n"); Sleep(300);
				printf("  player�� %d * %d = %d ������ ������ϴ�.\n", select_bettingCoin, turn, select_bettingCoin);
			}
			else if (select_p) {
				selectCoin = selectCoin + (bettingCoin * turn);
				playerCoin -= (bettingCoin * turn);
				printf("  ��"); Sleep(150); printf("��"); Sleep(150); printf("��"); Sleep(150); printf("��.\n"); Sleep(300);
				printf("  player�� %d * %d = %d ������ �Ҿ����ϴ�.\n", bettingCoin, turn, bettingCoin * turn);
			}

			printf("\n");
			// �ΰ������� ������ �ִ� ���� ���
			printf("  ��"); Sleep(100); printf("��"); Sleep(100); printf("��"); Sleep(100); printf("��"); Sleep(100); printf("��"); Sleep(100);
			printf(" ��"); Sleep(100); printf("��"); Sleep(100); printf("��"); Sleep(100); printf(" ��"); Sleep(100); printf("��"); Sleep(100);
			printf(" ��"); Sleep(100); printf("��"); Sleep(100); printf("��"); Sleep(100); printf(" %d", selectCoin); Sleep(100);
			printf(" ��"); Sleep(100); printf("��"); Sleep(100); printf("��.\n"); Sleep(100);

			printf("\n");
			// ���簡���� �ִ� ���� ���
			printf("  ��"); Sleep(100); printf("��"); Sleep(100); printf(" ��"); Sleep(100); printf("��"); Sleep(100); printf("��"); Sleep(100);
			printf(" ��"); Sleep(100); printf("��"); Sleep(100); 
			printf(" ��"); Sleep(100); printf("��"); Sleep(100); printf("��"); Sleep(100); printf(" %d", playerCoin); Sleep(100);
			printf(" ��"); Sleep(100); printf("��"); Sleep(100); printf("��.\n"); Sleep(100);

			printf("\n");
			printf("  ��ٸ��� �������� �Ѿ�ϴ�.\n");

			Sleep(8000);
			system("cls");

			if (turn == 5) {
				// 5���� ��� ��������
				if (playerCoin > selectCoin) {
					printf("  player�� �̰���ϴ�.\n");
					win();
				}
				else if (playerCoin < selectCoin) {
					printf("  player�� �����ϴ�.\n");
					lose();
				}
			}
		}		
	}
}

void Start() {

	printf("[ @�̸� ã�ƶ�! ]\n");


}

int main(void) {
	// ȥ�ڰ��� / �ΰ����ɰ� �Բ����� / ������ => ȥ�� ���� �ϴ� ��� 1, �ΰ����ɰ� ���� 2, ������ 0

	int startGame = 0;
	// @ ��ġ
	// �� ( �� 5�� )

	// player bettingCoin
	int bettingCoin = 0, bettingResult = 0;

	BOX box1 = { L };		// L = 3
	BOX box2 = { 2 * L + 1 };	// 7
	BOX box3 = { 3 * L + 2 };	// 11

	while (1) {		

		cnt = 3;	// ���� Ƚ�� 3���� �ʱ�ȭ

		printf("\n");
		printf("  playerCoin = %d\n\n", playerCoin);
		printf("	ȥ�ڰ����� ���Ͻø� 1 \n\n");
		printf("	�ΰ����ɰ� �Բ������� ���Ͻø� 2\n\n");
		printf("	������ 0\n\n");
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
					printf("	%d �� �Դϴ�.\n", turn);
					printf("	@��ġ�� _%d_���ڿ� �ֽ��ϴ�.\n", p_key);
					Sleep(2000);
					system("cls");

					// �ʱ� ȭ��
					start_p(box1, box2, box3);

					// ���� ����
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
			printf("  ������ �����մϴ�.\n");
			printf(  "player coin = %d\n", playerCoin);
			break;
		}
	}
	
	return 0;
}