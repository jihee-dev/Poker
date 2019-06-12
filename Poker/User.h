#pragma once

#include <string>

#include <iostream>

#include <fstream>

#include <Windows.h>

#include "Dealer.h"

#include "Card.h"


using namespace std;

class User {

private:

	Card user_card[2];//유저 고유 카드 2장 
	int assets;//유저의 자산
	int betMoney; //배팅금액
	string playerID;//유저ID

public:

	string Total[30];
	string ID[15];
	int Assets[15];

	User(string playerID) {//this->playerNum=index; Index값이 playerNum 값과 같음. +) 유저 참여수에 따라 case 를 더 추가할 예정.

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

		for (int i = 0; i < k; i++){
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
	//객체를 만들면 유저의 ID와 자산의 DB가 파일에 저장됨.

	int DoBet() {
		char answer;
		cout << "배팅하시겠습니까?(Y/N)" << endl;

		cin >> answer;

		switch (answer) {
		int BetMoney;
		case 'Y':
			while (1) {
				cout << "배팅금액을 입력해주세요." << endl;
				cin >> BetMoney;

				if (BetMoney > this->assets) {
					cout << "자산보다 더 많은 금액을 입력하셨습니다." << endl;
				}
				else {
					this->assets = this->assets - BetMoney;
					cout << "배팅에 성공하셨습니다." << endl;
					return BetMoney;
					break;
				}
			}
		case 'N':
			cout << "Die" << endl;
			BetMoney = 0;
			return BetMoney;
			break;
		}
	}


	void allAssetShow() {

		cout << this->playerID << "님의 총 자산은" << this->assets << "입니다" << endl;

	}



	void playerDeck(Dealer dealer) {

		cout << "==========" << this->playerID << "가 카드를 받습니다." << "==========" << endl;

		for (int i = 0; i < 2; i++) {

			this->user_card[i] = dealer.getUserCard()[i];

		}

	}



	void showCard() {

		cout << "==========" << this->playerID << " 의 카드정보==========" << endl;



		for (int i = 0; i < 2; i++) {

			cout << "Card" << i + 1 << " is " << this->user_card[i].getImage() << " " << user_card[i].getNum() << endl;

		}

	}

};