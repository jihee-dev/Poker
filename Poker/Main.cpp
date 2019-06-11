#include<iostream>
#include"GameController.h"
#include"User.h"

using namespace std;

class Main {
public:
	int main() {
		playingGame();
	}

	void playingGame() {
		GameController* controller = new GameController();
		Dealer* dealer = new Dealer();
		int playerNum = 3;
		User user[3];

		// �÷��̾� �� �Է�
		playerNum = controller->askPlayerNum();
		cout << endl;

		// ���� ���� > �÷��̾� ����ŭ
		for (int i = 0; i < playerNum; i++) {
			boolean flag = false;
			string tempId;
			do {
				cout << "���̵� �Է��� �ּ���: ";
				cin >> tempId;
				flag = checkId(tempId);
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
		}

		// 
	}

	boolean checkId(string id) {
		ifstream ifs;

	}
};