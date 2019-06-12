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
	static string Total[30];
	static string ID[15];
	static int Assets[15];

	User() {

	}

	User(string playerID) {//this->playerNum=index; Index���� playerNum ���� ����. +) ���� �������� ���� case �� �� �߰��� ����.
		string line;
		string test[1000];
		int str_cnt;
		int n = 0;
		int k = 0;
		int j = 0;
		ifstream ifs("playerID.txt");
		while (getline(ifs, line)) {
			char buff[100];
			strcpy(buff, line.c_str());

			char* tok = strtok(buff, " ");
			while (tok != NULL) {
				Total[n++] = string(tok);
				tok = strtok(NULL, " ");
			}
		}
		ifs.close();
		for (int i = 0; i < n; i++) {
			if (i % 2 == 0) {
				ID[k++] = Total[i];

			}
			else {
				Assets[j++] = atoi(Total[i].c_str());

			}
		}

		for (int i = 0; i < k; i++) {
			if (ID[i] == playerID) {
				this->playerID = ID[i];
				this->assets = Assets[i];
				cout << "Complete Set" << endl;
				break;
			}
			else {
				cout << "Loading.." << endl;
			}
		}
		cout << "================" << endl;
		cout << endl;
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

	int DoBet() {
		char answer;
		cout << "�����Ͻðڽ��ϱ�?(Y/N)" << endl;
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