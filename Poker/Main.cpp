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

		// 플레이어 수 입력
		playerNum = controller->askPlayerNum();
		cout << endl;

		// 유저 생성 > 플레이어 수만큼
		for (int i = 0; i < playerNum; i++) {
			boolean flag = false;
			string tempId;
			do {
				cout << "아이디를 입력해 주세요: ";
				cin >> tempId;
				flag = checkId(tempId);
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
		}

		// 
	}

	boolean checkId(string id) {
		ifstream ifs;

	}
};