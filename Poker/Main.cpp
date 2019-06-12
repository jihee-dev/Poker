#include<iostream>
#include"GameController.h"
#include"User.h"
#include"Board.h"


using namespace std;

int main() {
	Board* board = new Board();

	int select;
	cout << "======= Poker with C++ =======" << endl;
	cout << "1. ���ӽ���" << endl;
	cout << "2. ��ŷ" << endl;
	cout << "3. ������" << endl;

	cin >> select;

	switch (select) {

	case 1: //���� ����
		void playingGame();
		break;

	case 2: // ��ŷ
		board->rankSort();
		break;

	case 3: // ����
		return 0;

	default:
		break;
	}
}

void playingGame() {
	GameController* controller = new GameController();
	Dealer* dealer = new Dealer();
	int playerNum = 3;
	User user[3];
	int live[3] = {1, 1, 1};
	int* livePtr;
	int tempPlayerNum = 0;
	User winner;

	/*
	// �÷��̾� �� �Է�
	playerNum = controller->askPlayerNum();
	cout << endl;
	*/

	// ���� ���� > �÷��̾� ����ŭ
	for (int i = 0; i < playerNum; i++) {
		boolean flag = false;
		string tempId;
		do {
			cout << "���̵� �Է��� �ּ���: ";
			cin >> tempId;
			// flag = controller->checkId(tempId);
		} while (!flag);

		user[i] = *(new User(tempId));
	}
	cout << endl;

	// ����ī�� ����
	dealer->Shard_card();
	controller->setOpenCard(dealer->getOpenCard());
	cout << endl;

	// ����� ī�� ����
	for (int i = 0; i < playerNum; i++) {
		dealer->Shuffle();
		user[i].playerDeck(*dealer);
		controller->setUserCards(user[i].getUserCard(), i);
	}

	// ù ��° ����
	livePtr = controller->Bet(live);

	tempPlayerNum = 0;
	for (int i = 0; i < 3; i++) {
		live[i] = livePtr[i];
		if (live[i] == 1) {
			tempPlayerNum++;
		}
	}

	if (tempPlayerNum == 1) {
		goto end;
	}

	// �� ���� ī�� ����(����-1)
	controller->showOpenCard(1);
	cout << endl;

	// �� ��° ����
	livePtr = controller->Bet(live);

	tempPlayerNum = 0;
	for (int i = 0; i < 3; i++) {
		live[i] = livePtr[i];
		if (live[i] == 1) {
			tempPlayerNum++;
		}
	}

	if (tempPlayerNum == 1) {
		goto end;
	}

	// �� ���� ī�� ����(�� ��°) (����-2)
	controller->showOpenCard(2);
	cout << endl;

	// �� ��° ����
	livePtr = controller->Bet(live);

	tempPlayerNum = 0;
	for (int i = 0; i < 3; i++) {
		live[i] = livePtr[i];
		if (live[i] == 1) {
			tempPlayerNum++;
		}
	}

	if (tempPlayerNum == 1) {
		goto end;
	}

	// ������ ī�� ���� (����-3)
	controller->showOpenCard(3);
	cout << endl;

	// ������ ����
	livePtr = controller->Bet(live);

	tempPlayerNum = 0;
	for (int i = 0; i < 3; i++) {
		live[i] = livePtr[i];
		if (live[i] == 1) {
			tempPlayerNum++;
		}
	}

	if (tempPlayerNum == 1) {
		goto end;
	}

	// ���� ī�� ����, ����� ���� ����
	for (int i = 0; i < 3; i++) {
		if (live[i] != 0) {
			controller->findCombination(controller->askCard(i));
		}
	}

end:
	// ���� ����� ����
	if (tempPlayerNum == 1) {
		for (int i = 0; i < 3; i++) {
			if (live[i] == 1) {
				winner = user[i];
			}
		}
	}

	else {
		winner = user[controller->findWinner()];
	}

	cout << "Winner is " << winner.getPlayerID() << endl;

	// ����ڿ��� ���� �ݾ� �߰�
	

	// ���� ���


	// ����
	return;
}