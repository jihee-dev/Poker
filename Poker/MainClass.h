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


		// 유저 생성 > 플레이어 수만큼
		for (int i = 0; i < playerNum; i++) {
			boolean flag = false;
			string tempId;
			int tempMoney = 0;

			fileIO->fileLoad();

			do {
				cout << "아이디를 입력해 주세요: ";
				cin >> tempId;
				tempMoney = fileIO->checkID(tempId);
			} while (tempMoney == -1);

			user[i] = *(new User(tempId, tempMoney));
			cout << tempId << "객체가 생성되었습니다!" << endl;
		}
		cout << endl;

		// 공유카드 셋팅
		dealer->Shard_card();
		controller->setOpenCard(dealer->getOpenCard());
		cout << endl;

		// 사용자 카드 셋팅
		for (int i = 0; i < playerNum; i++) {
			dealer->Shuffle();
			user[i].playerDeck(*dealer);
			controller->setUserCards(user[i].getUserCard(), i);
		}

		// 첫 번째 베팅
		cout << "첫 번째 베팅을 시작합니다" << endl;
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

		// 세 개의 카드 오픈(오픈-1)
		controller->showOpenCard(1);
		cout << endl;

		// 두 번째 베팅
		cout << "두 번째 베팅을 시작합니다" << endl;
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

		// 한 개의 카드 오픈(네 번째) (오픈-2)
		controller->showOpenCard(2);
		cout << endl;

		// 세 번째 베팅
		cout << "세 번째 베팅을 시작합니다" << endl;
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

		// 마지막 카드 오픈 (오픈-3)
		controller->showOpenCard(3);
		cout << endl;

		// 마지막 베팅
		cout << "마지막 베팅을 시작합니다" << endl;
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

		// 최종 카드 결정, 사용자 족보 판정
		for (int i = 0; i < 3; i++) {
			if (live[i] != 0) {
				user[i].setCombination(controller->askCard(i));
			}
		}
		goto end;

	end:
		// 최종 우승자 판정
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

		// 사용자에게 베팅 금액 추가
		winnername = winner.getPlayerID();
		for (int i = 0; i < 15; i++) {
			if (fileIO->getIDs()[i] == winnername) {
				fileIO->setMoney(i, this->totalBetting + fileIO->getMoney(i));
			}
		}

		// 파일 출력
		fileIO->fileSave();

		// 종료
		cout << endl;
		cout << "게임이 종료되었습니다!!" << endl;
		cout << endl;
	}
};
