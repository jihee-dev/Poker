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
	Card user_card[2];//유저 고유 카드 2장 
	int betMoney; //배팅금액
	int whoisPlayer;//유저마다 파일입출력 파일을 다르게 만들기 위해 선언됨.(유저간의 구분을 위해)
	string playerID;//유저의ID
	int assets;//유저의자산

	// Controller에서 추가
	EnHandCombination combination = NOTHING;

public:
	User() {

	}

	User(string playerID, int money) {//this->playerNum=index; Index값이 playerNum 값과 같음. +) 유저 참여수에 따라 case 를 더 추가할 예정.
		this->playerID = playerID;
		this->assets = money;
	}

	//객체를 만들면 유저의 ID와 자산의 DB가 파일에 저장됨.

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
		cout << this->playerID <<"님 배팅하시겠습니까?(Y/N)" << endl;
	inputBet:
		cin >> answer;

		switch (answer) {
			int BetMoney;
		case 'Y':
			while (1) {
				cout << "추가 배팅금액을 입력해주세요." << endl;
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

		default:
			goto inputBet;
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