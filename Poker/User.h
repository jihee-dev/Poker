#pragma once
#include<string>
#include<iostream>
#include<fstream>
#include"Dealer.h"
#include"Card.h"
#include"HandCombination.h"

using namespace std;
class User {
private:
	Card user_card[2];//���� ���� ī�� 2�� 
	int betMoney; //���ñݾ�
	int whoisPlayer;//�������� ��������� ������ �ٸ��� ����� ���� �����.(�������� ������ ����)
	string playerID;//������ID
	int assets;//�������ڻ�

	// Controller���� �߰�
	EnHandCombination combination = NOTHING;

public:
	User() {

	}

	User(string playerID, int money) {//this->playerNum=index; Index���� playerNum ���� ����. +) ���� �������� ���� case �� �� �߰��� ����.
		this->playerID = playerID;
		this->assets = money;
	}

	//��ü�� ����� ������ ID�� �ڻ��� DB�� ���Ͽ� �����.

	Card* getUserCard() {
		return user_card;
	}

	EnHandCombination getCombination() {
		return this->combination;
	}

	string getPlayerID() {
		return this->playerID;
	}

	int getAssets() {
		return this->assets;
	}

	int DoBet() {
		char answer;
		cout << this->playerID <<"�� �����Ͻðڽ��ϱ�?(Y/N)" << endl;
	inputBet:
		cin >> answer;

		switch (answer) {
			int BetMoney;
		case 'Y':
			while (1) {
				cout << "�߰� ���ñݾ��� �Է����ּ���." << endl;
				cin >> BetMoney;

				if (BetMoney > this->assets) {
					cout << "�ڻ꺸�� �� ���� �ݾ��� �Է��ϼ̽��ϴ�." << endl;
				}
				else {
					this->assets = this->assets - BetMoney;
					cout << "���ÿ� �����ϼ̽��ϴ�." << endl;
					return BetMoney;
					break;
				}
			}
		case 'N':
			cout << "Die" << endl;
			BetMoney = 0;
			return BetMoney;
			break;

		default:
			goto inputBet;
		}
	}


	void allAssetShow() {
			cout << this->playerID << "���� �� �ڻ���" << this->assets << "�Դϴ�" << endl;
	}

	void playerDeck(Dealer dealer) {
		cout << "==========" << this->playerID << "�� ī�带 �޽��ϴ�." << "==========" << endl;
		for (int i = 0; i < 2; i++) {
			this->user_card[i] = dealer.getUserCard()[i];
		}
	}

	void showCard() {
		cout << "==========" << this->playerID << " �� ī������==========" << endl;

		for (int i = 0; i < 2; i++) {
			cout << "Card" << i + 1 << " is " << this->user_card[i].getImage() << " " << user_card[i].getNum() << endl;
		}
	}
};