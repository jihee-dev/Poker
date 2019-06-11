#include<iostream>
#include"GameController.h"

using namespace std;

int main() {
	playingGame();
}

void playingGame() {
	GameController* controller = new GameController();
	Dealer* dealer = new Dealer();
	int playerNum;
	User user[8];

	// 플레이어 수 입력
	playerNum = controller->askPlayerNum();
	cout << endl;

	// 유저 생성 > 플레이어 수만큼
	controller->createUser(playerNum);
	cout << endl;

	// 공유카드 셋팅
	dealer->Shard_card();
	controller->setOpenCard(dealer->getOpenCard());
	cout << endl;

	// 사용자 카드 셋팅
	for (int i = 0; i < playerNum; i++) {
		dealer->Shuffle();

	}
}