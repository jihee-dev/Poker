#include<iostream>
#include"GameController.h"
#include"User.h"
#include"Board.h"

using namespace std;

class Main {
public:
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
			playingGame();
			break;

		case 2:
			board->rankSort();
			break;

		case 3:
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
				flag = checkId(tempId);
			} while (!flag);

			user[i] = *(new User(i));
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


		// �� ���� ī�� ����(����-1)
		controller->showOpenCard(1);
		cout << endl;

		// �� ��° ����


		// �� ���� ī�� ����(�� ��°) (����-2)
		controller->showOpenCard(2);
		cout << endl;

		// �� ��° ����


		// ������ ī�� ���� (����-3)
		controller->showOpenCard(3);
		cout << endl;

		// ������ ����


		// ���� ī�� ����, ����� ���� ����
		for (int i = 0; i < 3; i++) {
			controller->findCombination(controller->askCard(i));
		}


		// ���� ����� ����
		controller->findWinner();

		// ����ڿ��� ���� �ݾ� �߰�
		

		// ���� ���


		// ����
	}
};