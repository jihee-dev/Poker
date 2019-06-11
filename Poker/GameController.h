#pragma once
#include<iostream>
#include<string>
// #include"User.h"
#include"Dealer.h"
#include"Card.h"
#include"EnCard.h"
#include"HandCombination.h"

using namespace std;

class GameController {
private:
	EnCard openCards[5]; // ������ ī�带 ���� �� ���µ� ī�尡 ����� �ٷ� �ʱ�ȭ
	 // Dealer* dealer;
	int bettingMoney;
	int playerNum;
	EnCard UserCard[8][2];
	User user[8];

public:
	GameController() {
		// dealer = new Dealer();
	}

	void setOpenCard(Card open[]) { // ���� ī�� �ʱ�ȭ
		for (int i = 0; i < 5; i++) {
			this->openCards[i] = this->StructToClass(open[i]);
		}
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


	}

	// ���� 7���� ī��(������ �� 2�� + ���µ� �� 5��) �� ���� �� ���� ī�带 ����
	// View ���� ��ư �����ʿ� �����Ͽ� �ۼ�

	Card* askCard(User u/*, Dealer d*/) {
		Card useCard[5];

		// ���� ī�� �� ���� �����ϰ� ������ ī�带 useCard[]�� ���� �� �迭 ����

		return useCard;
	}

	EnHandCombination findCombination(EnCard useCard[5]) { // ������ ī���� ������ User�� �ִٰ� ����
		EnHandCombination result = HIGHCARD;
		EnCard temp;
		bool straight = false;
		bool royal = false;
		bool flush = true;
		bool fourCard = false;
		bool threeCard = false;
		int pairNum = 0;

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
		// cout << result << endl;
		return result;
	}

	// ��� �÷��̾��� ������ ������ �ִ� ��� Ŭ�������� ���� ������ ��� ������
	// User�� combination ���� ���Ͽ� ���� ���� ������ ������ �ִ� User�� ����
	User findWinner(User player[]) {
		return NULL;
	}

	int askPlayerNum() {
		do {
			cout << "�÷��̾� ���� �Է��� �ּ���(2-8): ";
			cin >> this->playerNum;
		} while ((this->playerNum > 1) && (this->playerNum < 9));
		return this->playerNum;
	}

	/*
	void createUser(int n) {
		for (int i = 0; i < n; i++) {
			this->user[i] = new User();
		}
	} */

};