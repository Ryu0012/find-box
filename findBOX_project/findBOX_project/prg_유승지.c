// [�̱���]
// 1�ϸ� ���� -> 5�ϱ��� �̱���
// �ΰ����ɰ� ��� �̱��� > @ �� �ִ� ���� ����, �������� ���� 
// ������ �������� ȥ�ڰ��� / �ΰ����ɰ� ���� / ������ �� �����ϴ� �κ� 
// 3 /10 = 30%

#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

#define N 15	// ���� �迭 ũ��
#define L 3		// 1�� ���� ��ġ, �ʱ� ���� Ƚ�� 

void printing();
void setting(BOX, BOX, BOX);
void start_p(BOX, BOX, BOX);
int betting();		// �̱���

// @ ����ִ� ���� ��ġ
int key = L;

// @�̰� ����ִ� ���ڹ�ȣ
int p_key = 1;

// ���� �迭
char arr[N] = { 0 };

// �ʱ� ����ڰ� ������ �ִ� ����
int playerCoin = 500;

// ���� �ӵ�, Ƚ��
int t = 10, cnt = L;

// ����
typedef struct {
	int pol;	// ����ġ
	int det;	// �������
}BOX;

// ����_�ݾ�
int betting() {
	// ����

	// ����

}

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
	else {	// ���� �Ƚ��൵ ��
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

	int randNum = 0;	// randNum: ���� ���� �� �ִ� ��츦 �����ϰ� ����, cnt: ���� Ƚ��
	srand((unsigned int)time(NULL));

	for (int i = 0; i < cnt; i++) {
		// Sleep(3000); // Ȯ�ο�
		randNum = rand() % 3 + 1;

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



int main(void) {
	// ȥ�ڰ��� / �ΰ����ɰ� �Բ����� / ������

	// @ ��ġ
	// �� ( �� 5�� )

	BOX box1 = { L };		// L = 3
	BOX box2 = { 2 * L + 1 };	// 7
	BOX box3 = { 3 * L + 2 };	// 11

	for (int turn = 1; turn <= N; turn++) {
		printf("%d �� �Դϴ�.\n", turn);
		printf("@��ġ�� [%d]���ڿ� �ֽ��ϴ�.\n", p_key);
		Sleep(1000);
		system("cls");

		// �ʱ� ȭ��
		start_p(box1, box2, box3);

		// ���� ����
		randomMix(box1, box2, box3);
		printf("\n");

		// @�� ��� ���ڿ� ����ִ��� Ȯ�ο�
		int playerKey = 0, bettingCoin = 0;	// player�� �� ����
		printf("�� ��° ���ڸ� ���ðڽ��ϱ�?\n");
		printf("[ 1������ = 1, 2������ = 2, 3������ = 3 ]\n");
		printf("=> ");
		scanf_s("%d", &playerKey);
		printf("\n");

		printf("�� ������ betting �Ͻðڽ��ϱ�? (��������� �Է����ּ���)\n");
		printf("=> ");
		scanf_s("%d", &bettingCoin);
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


		// player ���� ���
		if (playerKey == p_key) {
			playerCoin = playerCoin + (bettingCoin * turn);
			printf("betting�� �����ϼ̽��ϴ�.\n");
			printf("%d * %d = %d ������ ������ϴ�.\n", bettingCoin, turn, bettingCoin * turn);			
		}
		else {
			playerCoin -= bettingCoin;
			printf("betting�� �����ϼ̽��ϴ�.\n");
			printf("%d ������ �Ҿ����ϴ�.\n", bettingCoin);
		}

		printf("\n");
		printf("���� ������ �ִ� ������ %d �Դϴ�.\n", playerCoin);
		printf("��ٸ��� ���� ������ �Ѿ�ϴ�.\n");

		Sleep(3000);
		system("cls");
	} 
	
	return 0;
}