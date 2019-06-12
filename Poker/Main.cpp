#include<iostream>
#include"GameController.h"
#include"User.h"
#include"Board.h"


using namespace std;

int main() {
	Board* board = new Board();

	int select;
	cout << "======= Poker with C++ =======" << endl;
	cout << "1. 게임시작" << endl;
	cout << "2. 랭킹" << endl;
	cout << "3. 나가기" << endl;

	cin >> select;

	switch (select) {

	case 1: //게임 시작
		void playingGame();
		break;

	case 2: // 랭킹
		board->rankSort();
		break;

	case 3: // 종료
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
	// 플레이어 수 입력
	playerNum = controller->askPlayerNum();
	cout << endl;
	*/

	// 유저 생성 > 플레이어 수만큼
	for (int i = 0; i < playerNum; i++) {
		boolean flag = false;
		string tempId;
		do {
			cout << "아이디를 입력해 주세요: ";
			cin >> tempId;
			// flag = controller->checkId(tempId);
		} while (!flag);

		user[i] = *(new User(tempId));
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

	// 세 개의 카드 오픈(오픈-1)
	controller->showOpenCard(1);
	cout << endl;

	// 두 번째 베팅
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

	// 한 개의 카드 오픈(네 번째) (오픈-2)
	controller->showOpenCard(2);
	cout << endl;

	// 세 번째 베팅
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

	// 마지막 카드 오픈 (오픈-3)
	controller->showOpenCard(3);
	cout << endl;

	// 마지막 베팅
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

	// 최종 카드 결정, 사용자 족보 판정
	for (int i = 0; i < 3; i++) {
		if (live[i] != 0) {
			controller->findCombination(controller->askCard(i));
		}
	}

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
		winner = user[controller->findWinner()];
	}

	cout << "Winner is " << winner.getPlayerID() << endl;

	// 사용자에게 베팅 금액 추가
	

	// 파일 출력


	// 종료
	return;
}