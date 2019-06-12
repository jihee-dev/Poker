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
	cout << "1. ���ӽ���" << endl;
	cout << "2. ��ŷ" << endl;
	cout << "3. ������" << endl;

	cin >> select;

	switch (select) {

	case 1: //���� ����
		m->playingGame();
		break;

	case 2: // ��ŷ
		board->rankSort();
		break;

	case 3: // ����
		return 0;

	default:
		break;
	}
}