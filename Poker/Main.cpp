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
		cout << "1. 게임시작" << endl;
		cout << "2. 랭킹" << endl;
		cout << "3. 나가기" << endl;

		cin >> select;

		switch (select) {

		case 1: //게임 시작
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
				flag = checkId(tempId);
			} while (!flag);

			user[i] = *(new User(i));
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


		// 세 개의 카드 오픈(오픈-1)
		controller->showOpenCard(1);
		cout << endl;

		// 두 번째 베팅


		// 한 개의 카드 오픈(네 번째) (오픈-2)
		controller->showOpenCard(2);
		cout << endl;

		// 세 번째 베팅


		// 마지막 카드 오픈 (오픈-3)
		controller->showOpenCard(3);
		cout << endl;

		// 마지막 베팅


		// 최종 카드 결정, 사용자 족보 판정
		for (int i = 0; i < 3; i++) {
			controller->findCombination(controller->askCard(i));
		}


		// 최종 우승자 판정
		controller->findWinner();

		// 사용자에게 베팅 금액 추가
		

		// 파일 출력


		// 종료
	}
};