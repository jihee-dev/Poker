#pragma once


//Type: main�Լ����� �ٷ� �����ؼ� �Լ� ����� �� �ֵ��� ���� ����
//UserŬ������ �����ʿ�
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<cstdlib>
#include<string>
#include<Windows.h>
#include"Card.h"
using namespace std;

class Dealer {
	//private: ��ü ī����, �� ������ ī����(2�徿)--�����Ҵ� �ʿ�, ����ī����
private:   //int num[13] = { 0 }, shape[4] = { 0 };   //ī�� ��ü ���

	Card opened_card[5];   //����ī�� ���
	Card total_card[53];
	Card user_card[2];

public:
	Dealer() {
		int square;
		for (int i = 0; i < 4; i++) {
			for (int j = 1; j <= 13; j++) {
				square = 13 * i + j;
				if (i == 0) {
					total_card[square].setImage("Spade");
				}
				else if (i == 1) {
					total_card[square].setImage("Heart");
				}
				else if (i == 2) {
					total_card[square].setImage("Diamond");
				}
				else {
					total_card[square].setImage("Club");
				}
				total_card[square].setNum(j);
			}

		}
	}

	void Show() {
		cout << endl;
		cout << "���� ī�� ���� ����" << endl;
		for (int i = 1; i <= 52; i++) {
			cout << total_card[i].getImage() << " " << total_card[i].getNum() << endl;
			Sleep(100);
		}
		cout << "----------------------" << endl;
	}

	void Shuffle() {
		cout << endl;
		cout << "-----�� ���� �̽��ϴ�-----" << endl;
		srand(time(NULL));
		for (int i = 0; i < 2; i++) {
			while (1) {
				int randn = rand() % 53 + 1;

				if (total_card[randn].getNum() != 0 && total_card[randn].getNum() != 100) {
					user_card[i].setImage(total_card[randn].getImage());
					user_card[i].setNum(total_card[randn].getNum());
					total_card[randn].setNum(0);
					cout << user_card[i].getImage() << " " << user_card[i].getNum() << endl;
					break;
				}
			}
		}
		cout << "--------------------------" << endl;
		cout << endl;
		Sleep(300);
	}

	void Shard_card() {
		cout << endl;
		cout << "-----����ī�带 �̽��ϴ�-----" << endl;
		srand(time(NULL));
		for (int i = 0; i < 5; i++) {
			while (1) {
				int randn = rand() % 53 + 1;
				if (total_card[randn].getNum() != 0) {
					opened_card[i].setImage(total_card[randn].getImage());
					opened_card[i].setNum(total_card[randn].getNum());
					total_card[randn].setNum(100);
					break;
				}
			}
		}
		for (int i = 0; i < 5; i++) {
			cout << opened_card[i].getImage() << " " << opened_card[i].getNum() << endl;
		}
		cout << "-----------------------------" << endl;
	}

	Card* getUserCard() {
		return user_card;
	}

	Card* getOpenCard() {
		return this->opened_card;
	}
};