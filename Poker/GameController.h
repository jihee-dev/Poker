#pragma once
#include<iostream>
#include<string>
#include"User.h"
#include"Dealer.h"
#include"Card.h"
#include"HandCombination.h"
#include"Card2.h"

using namespace std;

class GameController {
private:
	Card openCards[5]; // 딜러가 카드를 셔플 후 오픈된 카드가 생기면 바로 초기화
	Dealer* dealer;

public:
	GameController() {
		dealer = new Dealer();
	}

	Card StructToClass(card2 c) {
		Card* tempCard = new Card();

		switch (c.Num) {
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

		if (c.Image == "Space") {
			tempCard->setShape(SPADE);
		}

		else if (c.Image == "Heart") {
			tempCard->setShape(HEART);
		}

		else if (c.Image == "Diamond") {
			tempCard->setShape(DIAMOND);
		}

		else if (c.Image == "Clover") {
			tempCard->setShape(CLUB);
		}


	}

	void setOpenCards() {
		// card2 tempOpen[5] =
		for (int i = 0; i < 5; i++) {

		}
		// 딜러에게서 카드를 받아와서 셋팅
	}

	// 최종 7장의 카드(유저의 패 2장 + 오픈된 패 5장) 중 버릴 두 장의 카드를 선택
	// View 쪽의 버튼 리스너와 협업하여 작성

	Card* askCard(User u/*, Dealer d*/) {
		Card useCard[5];

		// 버릴 카드 두 장을 제외하고 나머지 카드를 useCard[]에 넣은 후 배열 리턴

		return useCard;
	}

	EnHandCombination findCombination(Card useCard[5]) { // 유저의 카드패 정보가 User에 있다고 가정
		EnHandCombination result = HIGHCARD;
		Card temp;
		bool straight = false;
		bool royal = false;
		bool flush = true;
		bool fourCard = false;
		bool threeCard = false;
		int pairNum = 0;

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
		// cout << result << endl;
		return result;
	}

	// 모든 플레이어의 정보를 가지고 있는 어떠한 클래스에서 유저 정보를 모두 가져옴
	// User의 combination 값을 비교하여 가장 높은 족보를 가지고 있는 User를 리턴
	User findWinner(User player[]) {
		return NULL;
	}

	void playerNum() {
		// 메인 함수 구현하면서 바디 구현
	}

	/* int askBetting() {
	char answer;
	int betting;

	while (true) {
	cout << "베팅하시겠습니까? (y/n) ";
	cin >> answer;

	if (answer == 'y') {
	cout << "베팅할 금액을 입력해 주세요: ";
	cin >> betting;
	return betting;
	}

	else if (answer == 'n') {
	cout << "베팅을 종료합니다." << endl;
	return 0;
	}

	else {
	cout << "잘못 입력하셨습니다. 다시 입력해 주세요.";
	}
	}

	return 0;
	} */

};