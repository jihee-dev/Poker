#pragma once
#include<iostream>
#include"GameController.h"
#include"User.h"
#include"Board.h"
#include"FileIO.h"

using namespace std;

class MainClass {
private:
	int playerNum = 3;
	User user[3];
	int live[3] = { 1, 1, 1 };
	int* livePtr;
	int tempPlayerNum = 0;
	User winner;
	string winnername;
	int totalBetting = 0;

public:
	void playingGame() {
		GameController* controller = new GameController();
		Dealer* dealer = new Dealer();
		FileIO* fileIO = new FileIO();


		// ���� ���� > �÷��̾� ����ŭ
		for (int i = 0; i < playerNum; i++) {
			boolean flag = false;
			string tempId;
			int tempMoney = 0;

			fileIO->fileLoad();

			do {
				cout << "���̵� �Է��� �ּ���: ";
				cin >> tempId;
				tempMoney = fileIO->checkID(tempId);
			} while (tempMoney == -1);

			user[i] = *(new User(tempId, tempMoney));
			cout << tempId << "��ü�� �����Ǿ����ϴ�!" << endl;
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
		cout << "ù ��° ������ �����մϴ�" << endl;
		livePtr = controller->Bet(live, user);

		tempPlayerNum = 0;

		for (int i = 0; i < 3; i++) {
			live[i] = livePtr[i];
			if (live[i] == 1) {
				tempPlayerNum++;
			}
		}

		for (int i = 0; i < 3; i++)
		{
			int idx;

			for (int j = 0; j < 15; j++) {
				if (fileIO->getIDs()[j] == user[i].getPlayerID()) {
					idx = j;
					break;
				}
			}

			int* tempF = controller->getEachMoney();
			fileIO->setMoney(idx, fileIO->getMoneys()[idx] - tempF[i]);
		}

		if (tempPlayerNum == 1) {
			goto end;
		}

		this->totalBetting += controller->getBetMoney();
		cout << this->totalBetting << endl;

		// �� ���� ī�� ����(����-1)
		controller->showOpenCard(1);
		cout << endl;

		// �� ��° ����
		cout << "�� ��° ������ �����մϴ�" << endl;
		livePtr = controller->Bet(live, user);

		tempPlayerNum = 0;

		for (int i = 0; i < 3; i++) {
			live[i] = livePtr[i];
			if (live[i] == 1) {
				tempPlayerNum++;
			}
		}

		for (int i = 0; i < 3; i++)
		{
			int idx;

			for (int j = 0; j < 15; j++) {
				if (fileIO->getIDs()[j] == user[i].getPlayerID()) {
					idx = j;
					break;
				}
			}

			int* tempF = controller->getEachMoney();
			fileIO->setMoney(idx, fileIO->getMoneys()[idx] - tempF[i]);
		}

		if (tempPlayerNum == 1) {
			goto end;
		}

		this->totalBetting += controller->getBetMoney();
		cout << this->totalBetting << endl;

		// �� ���� ī�� ����(�� ��°) (����-2)
		controller->showOpenCard(2);
		cout << endl;

		// �� ��° ����
		cout << "�� ��° ������ �����մϴ�" << endl;
		livePtr = controller->Bet(live, user);

		tempPlayerNum = 0;

		for (int i = 0; i < 3; i++) {
			live[i] = livePtr[i];
			if (live[i] == 1) {
				tempPlayerNum++;
			}
		}

		for (int i = 0; i < 3; i++)
		{
			int idx;

			for (int j = 0; j < 15; j++) {
				if (fileIO->getIDs()[j] == user[i].getPlayerID()) {
					idx = j;
					break;
				}
			}

			int* tempF = controller->getEachMoney();
			fileIO->setMoney(idx, fileIO->getMoneys()[idx] - tempF[i]);
		}

		if (tempPlayerNum == 1) {
			goto end;
		}

		this->totalBetting += controller->getBetMoney();
		cout << this->totalBetting << endl;

		// ������ ī�� ���� (����-3)
		controller->showOpenCard(3);
		cout << endl;

		// ������ ����
		cout << "������ ������ �����մϴ�" << endl;
		livePtr = controller->Bet(live, user);

		tempPlayerNum = 0;

		for (int i = 0; i < 3; i++) {
			live[i] = livePtr[i];
			if (live[i] == 1) {
				tempPlayerNum++;
			}
		}

		for (int i = 0; i < 3; i++)
		{
			int idx;

			for (int j = 0; j < 15; j++) {
				if (fileIO->getIDs()[j] == user[i].getPlayerID()) {
					idx = j;
					break;
				}
			}

			int* tempF = controller->getEachMoney();
			fileIO->setMoney(idx, fileIO->getMoneys()[idx] - tempF[i]);
		}

		if (tempPlayerNum == 1) {
			goto end;
		}

		this->totalBetting += controller->getBetMoney();
		cout << this->totalBetting << endl;

		// ���� ī�� ����, ����� ���� ����
		for (int i = 0; i < 3; i++) {
			if (live[i] != 0) {
				user[i].setCombination(controller->askCard(i));
			}
		}
		goto end;

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
			winner = user[controller->findWinner(user)];
		}

		cout << "Winner is " << winner.getPlayerID() << endl;

		// ����ڿ��� ���� �ݾ� �߰�
		winnername = winner.getPlayerID();
		for (int i = 0; i < 15; i++) {
			if (fileIO->getIDs()[i] == winnername) {
				fileIO->setMoney(i, this->totalBetting + fileIO->getMoney(i));
			}
		}

		// ���� ���
		fileIO->fileSave();

		// ����
		cout << endl;
		cout << "������ ����Ǿ����ϴ�!!" << endl;
		cout << endl;
	}
};
