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


		// ���� ī�� ����


		// ����� ���� ����


		// ���� ����� ����


		// ����ڿ��� ���� �ݾ� �߰�
		

		// ���� ���


		// ����
	}

	boolean checkId(string id) {
		ifstream ifs;
		string fileName = "userID.txt";
		string temp;

		ifs.open(fileName.c_str());

		if (!ifs) {
			cout << "Unable to open file!" << endl;
			exit(0);
		}

		while (ifs >> temp) {
			if (temp == id) {
				return true;
			}
		}

		return false;
	}
};