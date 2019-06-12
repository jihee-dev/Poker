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
	EnCard openCards[5]; // 딜러가 카드를 셔플 후 오픈된 카드가 생기면 바로 초기화
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

	void setOpenCard(Card open[]) { // 오픈 카드 초기화
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
			cout << "세 장의 공유 카드를 오픈합니다." << endl;
			for (int i = 0; i < 3; i++) {
				cout << i + 1 << "번 공유 카드: ";
				cout << openCards[i].printShape(openCards[i].getShape()) << " " << openCards[i].printNum(openCards[i].getNum()) << endl;
			}
			break;

		case 2:
			cout << "네 번째 공유 카드를 오픈합니다." << endl;
			cout << "4번 공유 카드: ";
			cout << openCards[3].printShape(openCards[3].getShape()) << " " << openCards[3].printNum(openCards[3].getNum()) << endl;
			break;

		case 3:
			cout << "다섯 번째 공유 카드를 오픈합니다." << endl;
			cout << "5번 공유 카드: ";
			cout << openCards[4].printShape(openCards[4].getShape()) << " " << openCards[4].printNum(openCards[4].getNum()) << endl;
			break;

		default:
			break;
		}
	}

	// 최종 7장의 카드(유저의 패 2장 + 오픈된 패 5장) 중 버릴 두 장의 카드를 선택
	// View 쪽의 버튼 리스너와 협업하여 작성

	EnHandCombination askCard(int userNum) { // 0, 1, 2
		EnCard selectCard[7];
		EnCard useCard[5];
		for (int i = 0; i < 5; i++) {
			selectCard[i] = openCards[i];
		}

		selectCard[5] = userCard[userNum][0];
		selectCard[6] = userCard[userNum][1];

		cout << "현재 유저의 보유 카드와 오픈 카드 목록입니다." << endl;
		for (int i = 0; i < 7; i++) {
			cout << i + 1 << ". " << selectCard[i].printShape(selectCard[i].getShape()) << " " << selectCard[i].printNum(selectCard[i].getNum()) << endl;
		}
		cout << "버릴 카드 두 장을 선택해 주세요. (남겨진 다섯 장의 카드로 최종 조합을 완성합니다)" << endl;

		int select1;
		bool flagSelect;

		do {
			cout << "첫 번째 버릴 카드 입력: ";
			cin >> select1;
			flagSelect = (select1 > 0) && (select1 < 8);
		} while (!flagSelect);

		int select2;

		do {
			cout << "두 번째 버릴 카드 입력: ";
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

		// 족보 판정 시작
		EnHandCombination result = HIGHCARD;
		EnCard temp;
		bool straight = false;
		bool royal = false;
		bool flush = true;
		bool fourCard = false;
		bool threeCard = false;
		int pairNum = 0;

		/*
		cout << "findCombination에서 잘 넘어왔을까요??" << endl;
		for (int i = 0; i < 5; i++) {
			cout << useCard[i].printShape(useCard[i].getShape()) << " " << useCard[i].printNum(useCard[i].getNum()) << endl;
		} */

		// cout << result << endl;

		// 카드를 숫자 기준으로 내림차순 정렬
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (useCard[j].getNum() < useCard[j + 1].getNum()) {
					temp = useCard[j];
					useCard[j] = useCard[j + 1];
					useCard[j + 1] = temp;
				}
			}
		}


		// 스트레이트, 플러시 확인
		int straightCnt = 0;
		for (int i = 0; i < 4; i++) {
			if (useCard[i].getNum() == useCard[i + 1].getNum() + 1) {
				straightCnt++;
			}

			if (useCard[i].getShape() != useCard[i + 1].getShape()) {
				flush = false; // 모양이 같지 않음 > 플러시 X
			}
		}



		if (straightCnt == 4) {
			straight = true; // 스트레이트
			if (useCard[0].getNum() == ACE) {
				royal = true; // 로얄스트레이트
			}
		}

		else if ((straightCnt == 3) && (useCard[0].getNum() == ACE) && (useCard[1].getNum() == FIVE)) {
			straight = true; // A 5 4 3 2 스트레이트
		}

		// cout << result << endl;

		// 같은 숫자 확인
		int tempNum[13] = { 0 };
		for (int i = 0; i < 5; i++) {
			// cout << result << endl;
			tempNum[useCard[i].getNum() - 2] += 1;
		}


		for (int i = 0; i < 13; i++) {
			switch (tempNum[i]) {
			case 2:
				pairNum++; // 페어 한 쌍 추가
				break;
			case 3:
				threeCard = true; // 쓰리카드
				break;
			case 4:
				fourCard = true;  // 포카드
				break;
			}
		}


		// cout << result << endl;

		// 최종 족보 결정
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

	EnHandCombination findCombination(EnCard useCard[5]) { // 유저의 카드패 정보가 User에 있다고 가정
		/*
		EnHandCombination result = HIGHCARD;
		EnCard temp;
		bool straight = false;
		bool royal = false;
		bool flush = true;
		bool fourCard = false;
		bool threeCard = false;
		int pairNum = 0;

		cout << "findCombination에서 잘 넘어왔을까요??" << endl;
		for (int i = 0; i < 5; i++) {
			cout << useCard[i].printShape(useCard[i].getShape()) << " " << useCard[i].printNum(useCard[i].getNum()) << endl;
		}

		// cout << result << endl;

		// 카드를 숫자 기준으로 내림차순 정렬
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (useCard[j].getNum() < useCard[j + 1].getNum()) {
					temp = useCard[j];
					useCard[j] = useCard[j + 1];
					useCard[j + 1] = temp;
				}
			}
		}


		// 스트레이트, 플러시 확인
		int straightCnt = 0;
		for (int i = 0; i < 4; i++) {
			if (useCard[i].getNum() == useCard[i + 1].getNum() + 1) {
				straightCnt++;
			}

			if (useCard[i].getShape() != useCard[i + 1].getShape()) {
				flush = false; // 모양이 같지 않음 > 플러시 X
			}
		}



		if (straightCnt == 4) {
			straight = true; // 스트레이트
			if (useCard[0].getNum() == ACE) {
				royal = true; // 로얄스트레이트
			}
		}

		else if ((straightCnt == 3) && (useCard[0].getNum() == ACE) && (useCard[1].getNum() == FIVE)) {
			straight = true; // A 5 4 3 2 스트레이트
		}

		// cout << result << endl;

		// 같은 숫자 확인
		int tempNum[13] = { 0 };
		for (int i = 0; i < 5; i++) {
			// cout << result << endl;
			tempNum[useCard[i].getNum() - 2] += 1;
		}


		for (int i = 0; i < 13; i++) {
			switch (tempNum[i]) {
			case 2:
				pairNum++; // 페어 한 쌍 추가
				break;
			case 3:
				threeCard = true; // 쓰리카드
				break;
			case 4:
				fourCard = true;  // 포카드
				break;
			}
		}


		// cout << result << endl;

		// 최종 족보 결정
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

	// 모든 플레이어의 정보를 가지고 있는 어떠한 클래스에서 유저 정보를 모두 가져옴
	// User의 combination 값을 비교하여 가장 높은 족보를 가지고 있는 User를 리턴
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
		each_money[0] = 0; // 사용자가 라운드마다 베팅한 총 금액
		each_money[1] = 0;
		each_money[2] = 0;

		int i = 0;
		boolean flagBet;
		boolean flagExit;

		while (true) {
			flagExit = true;

			// i번째 플레이어에게 베팅 요청
			if (livePlayer[i] != 0) {
				do {
					cout << "배팅 기준 금액: " << betMoney << endl;
					cout << "현재 배팅 금액: " << each_money[i] << endl;
					cout << user[i].getPlayerID() << "님의 현재 잔액: " << user[i].getAssets() << endl;
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

			// 플레이어들의 베팅 금액이 동일해졌는지 확인
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