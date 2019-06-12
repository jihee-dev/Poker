#pragma once
#include<iostream>
#include<string>
#include"User.h"
#include"Dealer.h"
#include"Card.h"
#include"EnCard.h"
#include"HandCombination.h"

using namespace std;

class GameController {
private:
	EnCard openCards[5]; // ������ ī�带 ���� �� ���µ� ī�尡 ����� �ٷ� �ʱ�ȭ
						 // Dealer* dealer;
	int bettingMoney = 0;
	int playerNum = 3;
	EnCard userCard[3][2];
	User user[3];
	int each_money[3];


public:
	GameController() {
		// dealer = new Dealer();
	}

	void setOpenCard(Card open[]) { // ���� ī�� �ʱ�ȭ
		for (int i = 0; i < 5; i++) {
			this->openCards[i] = this->StructToClass(open[i]);
		}
	}

	void setUserCards(Card user[], int temp) {
		this->userCard[temp][0] = this->StructToClass(user[0]);
		this->userCard[temp][1] = this->StructToClass(user[1]);
	}

	EnCard StructToClass(Card c) {
		EnCard* tempCard = new EnCard();

		switch (c.getNum()) {
		case 1:
			tempCard->setNum(ACE);
			break;
		case 2:
			tempCard->setNum(TWO);
			break;
		case 3:
			tempCard->setNum(THREE);
			break;
		case 4:
			tempCard->setNum(FOUR);
			break;
		case 5:
			tempCard->setNum(FIVE);
			break;
		case 6:
			tempCard->setNum(SIX);
			break;
		case 7:
			tempCard->setNum(SEVEN);
			break;
		case 8:
			tempCard->setNum(EIGHT);
			break;
		case 9:
			tempCard->setNum(NINE);
			break;
		case 10:
			tempCard->setNum(TEN);
			break;
		case 11:
			tempCard->setNum(JACK);
			break;
		case 12:
			tempCard->setNum(QUEEN);
			break;
		case 13:
			tempCard->setNum(KING);
			break;
		default:
			break;
		}

		if (c.getImage() == "Spade") {
			tempCard->setShape(SPADE);
		}

		else if (c.getImage() == "Heart") {
			tempCard->setShape(HEART);
		}

		else if (c.getImage() == "Diamond") {
			tempCard->setShape(DIAMOND);
		}

		else if (c.getImage() == "Club") {
			tempCard->setShape(CLUB);
		}

		return *tempCard;
	}

	void showOpenCard(int n) {
		switch (n) {
		case 1:
			cout << "�� ���� ���� ī�带 �����մϴ�." << endl;
			for (int i = 0; i < 3; i++) {
				cout << i + 1 << "�� ���� ī��: ";
				cout << openCards[i].printShape(openCards[i].getShape()) << " " << openCards[i].printNum(openCards[i].getNum()) << endl;
			}
			break;

		case 2:
			cout << "�� ��° ���� ī�带 �����մϴ�." << endl;
			cout << "4�� ���� ī��: ";
			cout << openCards[3].printShape(openCards[3].getShape()) << " " << openCards[3].printNum(openCards[3].getNum()) << endl;
			break;

		case 3:
			cout << "�ټ� ��° ���� ī�带 �����մϴ�." << endl;
			cout << "5�� ���� ī��: ";
			cout << openCards[4].printShape(openCards[4].getShape()) << " " << openCards[4].printNum(openCards[4].getNum()) << endl;
			break;

		default:
			break;
		}
	}

	// ���� 7���� ī��(������ �� 2�� + ���µ� �� 5��) �� ���� �� ���� ī�带 ����
	// View ���� ��ư �����ʿ� �����Ͽ� �ۼ�

	EnHandCombination askCard(int userNum) { // 0, 1, 2
		EnCard selectCard[7];
		EnCard useCard[5];
		for (int i = 0; i < 5; i++) {
			selectCard[i] = openCards[i];
		}

		selectCard[5] = userCard[userNum][0];
		selectCard[6] = userCard[userNum][1];

		cout << "���� ������ ���� ī��� ���� ī�� ����Դϴ�." << endl;
		for (int i = 0; i < 7; i++) {
			cout << i + 1 << ". " << selectCard[i].printShape(selectCard[i].getShape()) << " " << selectCard[i].printNum(selectCard[i].getNum()) << endl;
		}
		cout << "���� ī�� �� ���� ������ �ּ���. (������ �ټ� ���� ī��� ���� ������ �ϼ��մϴ�)" << endl;

		int select1;
		bool flagSelect;

		do {
			cout << "ù ��° ���� ī�� �Է�: ";
			cin >> select1;
			flagSelect = (select1 > 0) && (select1 < 8);
		} while (!flagSelect);

		int select2;

		do {
			cout << "�� ��° ���� ī�� �Է�: ";
			cin >> select2;
			flagSelect = (select1 > 0) && (select1 < 8) && (select1 != select2);
		} while (!flagSelect);

		int idx = 0;

		for (int i = 0; i < 7; i++) {
			if ((i != select1 - 1) && (i != select2 - 1)) {
				useCard[idx] = selectCard[i];
				// cout << useCard[idx].printShape(useCard[idx].getShape()) << " " << useCard[idx].printNum(useCard[idx].getNum()) << endl;
				idx++;
			}
		}

		for (int i = 0; i < 5; i++) {
			useCard[i].showCard();
		}

		// ���� ���� ����
		EnHandCombination result = HIGHCARD;
		EnCard temp;
		bool straight = false;
		bool royal = false;
		bool flush = true;
		bool fourCard = false;
		bool threeCard = false;
		int pairNum = 0;

		/*
		cout << "findCombination���� �� �Ѿ�������??" << endl;
		for (int i = 0; i < 5; i++) {
			cout << useCard[i].printShape(useCard[i].getShape()) << " " << useCard[i].printNum(useCard[i].getNum()) << endl;
		} */

		// cout << result << endl;

		// ī�带 ���� �������� �������� ����
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (useCard[j].getNum() < useCard[j + 1].getNum()) {
					temp = useCard[j];
					useCard[j] = useCard[j + 1];
					useCard[j + 1] = temp;
				}
			}
		}


		// ��Ʈ����Ʈ, �÷��� Ȯ��
		int straightCnt = 0;
		for (int i = 0; i < 4; i++) {
			if (useCard[i].getNum() == useCard[i + 1].getNum() + 1) {
				straightCnt++;
			}

			if (useCard[i].getShape() != useCard[i + 1].getShape()) {
				flush = false; // ����� ���� ���� > �÷��� X
			}
		}



		if (straightCnt == 4) {
			straight = true; // ��Ʈ����Ʈ
			if (useCard[0].getNum() == ACE) {
				royal = true; // �ξ⽺Ʈ����Ʈ
			}
		}

		else if ((straightCnt == 3) && (useCard[0].getNum() == ACE) && (useCard[1].getNum() == FIVE)) {
			straight = true; // A 5 4 3 2 ��Ʈ����Ʈ
		}

		// cout << result << endl;

		// ���� ���� Ȯ��
		int tempNum[13] = { 0 };
		for (int i = 0; i < 5; i++) {
			// cout << result << endl;
			tempNum[useCard[i].getNum() - 2] += 1;
		}


		for (int i = 0; i < 13; i++) {
			switch (tempNum[i]) {
			case 2:
				pairNum++; // ��� �� �� �߰�
				break;
			case 3:
				threeCard = true; // ����ī��
				break;
			case 4:
				fourCard = true;  // ��ī��
				break;
			}
		}


		// cout << result << endl;

		// ���� ���� ����
		if (royal && flush) {
			result = ROYALFLUSH;
		}

		else if (straight && flush) {
			result = STRAIGHTFLUSH;
		}

		else if (fourCard) {
			result = FOURCARD;
		}

		else if (threeCard && pairNum == 1) {
			result = FULLHOUSE;
		}

		else if (flush) {
			result = FLUSH;
		}

		else if (straight) {
			result = STRAIGHT;
		}

		else if (threeCard) {
			result = THREECARD;
		}

		else if (pairNum == 2) {
			result = TWOPAIR;
		}

		else if (pairNum == 1) {
			result = PAIR;
		}

		// u.combination = result;
		cout << result << endl;
		return result;
	}

	EnHandCombination findCombination(EnCard useCard[5]) { // ������ ī���� ������ User�� �ִٰ� ����
		/*
		EnHandCombination result = HIGHCARD;
		EnCard temp;
		bool straight = false;
		bool royal = false;
		bool flush = true;
		bool fourCard = false;
		bool threeCard = false;
		int pairNum = 0;

		cout << "findCombination���� �� �Ѿ�������??" << endl;
		for (int i = 0; i < 5; i++) {
			cout << useCard[i].printShape(useCard[i].getShape()) << " " << useCard[i].printNum(useCard[i].getNum()) << endl;
		}

		// cout << result << endl;

		// ī�带 ���� �������� �������� ����
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (useCard[j].getNum() < useCard[j + 1].getNum()) {
					temp = useCard[j];
					useCard[j] = useCard[j + 1];
					useCard[j + 1] = temp;
				}
			}
		}


		// ��Ʈ����Ʈ, �÷��� Ȯ��
		int straightCnt = 0;
		for (int i = 0; i < 4; i++) {
			if (useCard[i].getNum() == useCard[i + 1].getNum() + 1) {
				straightCnt++;
			}

			if (useCard[i].getShape() != useCard[i + 1].getShape()) {
				flush = false; // ����� ���� ���� > �÷��� X
			}
		}



		if (straightCnt == 4) {
			straight = true; // ��Ʈ����Ʈ
			if (useCard[0].getNum() == ACE) {
				royal = true; // �ξ⽺Ʈ����Ʈ
			}
		}

		else if ((straightCnt == 3) && (useCard[0].getNum() == ACE) && (useCard[1].getNum() == FIVE)) {
			straight = true; // A 5 4 3 2 ��Ʈ����Ʈ
		}

		// cout << result << endl;

		// ���� ���� Ȯ��
		int tempNum[13] = { 0 };
		for (int i = 0; i < 5; i++) {
			// cout << result << endl;
			tempNum[useCard[i].getNum() - 2] += 1;
		}


		for (int i = 0; i < 13; i++) {
			switch (tempNum[i]) {
			case 2:
				pairNum++; // ��� �� �� �߰�
				break;
			case 3:
				threeCard = true; // ����ī��
				break;
			case 4:
				fourCard = true;  // ��ī��
				break;
			}
		}


		// cout << result << endl;

		// ���� ���� ����
		if (royal && flush) {
			result = ROYALFLUSH;
		}

		else if (straight && flush) {
			result = STRAIGHTFLUSH;
		}

		else if (fourCard) {
			result = FOURCARD;
		}

		else if (threeCard && pairNum == 1) {
			result = FULLHOUSE;
		}

		else if (flush) {
			result = FLUSH;
		}

		else if (straight) {
			result = STRAIGHT;
		}

		else if (threeCard) {
			result = THREECARD;
		}

		else if (pairNum == 2) {
			result = TWOPAIR;
		}

		else if (pairNum == 1) {
			result = PAIR;
		}

		// u.combination = result;
		cout << result << endl;
		return result; */
	}

	// ��� �÷��̾��� ������ ������ �ִ� ��� Ŭ�������� ���� ������ ��� ������
	// User�� combination ���� ���Ͽ� ���� ���� ������ ������ �ִ� User�� ����
	int findWinner(User user[]) { // 0, 1, 2
		EnHandCombination high = NOTHING;
		int tempWinner;

		for (int i = 0; i < 3; i++) {
			if (high <= user[i].getCombination()) {
				tempWinner = i;
				high = user[i].getCombination();
			}
		}

		return tempWinner;
	}

	int* Bet(int p[], User* user) {

		int livePlayer[3];
		for (int i = 0; i < 3; i++) {
			livePlayer[i] = p[i];
		}

		int tempMoney;
		int betMoney = -1;
		each_money[0] = 0; // ����ڰ� ���帶�� ������ �� �ݾ�
		each_money[1] = 0;
		each_money[2] = 0;

		int i = 0;
		boolean flagBet;
		boolean flagExit;

		while (true) {
			flagExit = true;

			// i��° �÷��̾�� ���� ��û
			if (livePlayer[i] != 0) {
				do {
					cout << "���� ���� �ݾ�: " << betMoney << endl;
					cout << "���� ���� �ݾ�: " << each_money[i] << endl;
					cout << user[i].getPlayerID() << "���� ���� �ܾ�: " << user[i].getAssets() << endl;
					tempMoney = user[i].DoBet();
					flagBet = (tempMoney == 0) || (tempMoney >= betMoney - each_money[i]);
				} while (!flagBet);

				if (tempMoney != 0) {
					each_money[i] += tempMoney;
					betMoney = each_money[i];
					this->bettingMoney += tempMoney;
				}

				else {
					livePlayer[i] = 0;
				}
			}

			// �÷��̾���� ���� �ݾ��� ������������ Ȯ��
			for (int j = 0; j < 3; j++) {
				if ((livePlayer[j] != 0) && (each_money[j] != betMoney)) {
					flagExit = false;
				}
			}

			if (flagExit) {
				return livePlayer;
			}


			if (i != 2) {
				i++;
			}

			else {
				i = 0;
			}
		}

		return livePlayer;
	}

	int getBetMoney()
	{
		return this->bettingMoney;
	}
	int* getEachMoney() {
		return this->each_money;
	}

	
};