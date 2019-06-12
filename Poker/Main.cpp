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

	// �÷��̾� �� �Է�
	playerNum = controller->askPlayerNum();
	cout << endl;

	// ���� ���� > �÷��̾� ����ŭ
	controller->createUser(playerNum);
	cout << endl;

	// ����ī�� ����
	dealer->Shard_card();
	controller->setOpenCard(dealer->getOpenCard());
	cout << endl;

	// ����� ī�� ����
	for (int i = 0; i < playerNum; i++) {
		dealer->Shuffle();

	}
}