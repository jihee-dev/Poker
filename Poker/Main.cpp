#include<iostream>
#include"GameController.h"
#include"User.h"
#include"Board.h"
#include"FileIO.h"
#include"MainClass.h"

using namespace std;

int main() {
	Board* board = new Board();
	static MainClass* m = new MainClass();

	int select;
	cout << "======= Poker with C++ =======" << endl;
	cout << "1. 게임시작" << endl;
	cout << "2. 랭킹" << endl;
	cout << "3. 나가기" << endl;

	cin >> select;

	switch (select) {

	case 1: //게임 시작
		m->playingGame();
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