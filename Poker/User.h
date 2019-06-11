#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "Dealer.h"
#include "Card.h"

using namespace std;
class User {
private:
	Card user_card[2];//유저 고유 카드 2장 
public:
	int assets;//유저의 자산
	int betMoney; //배팅금액
	string playerID;//유저ID
	int whoisPlayer;//유저마다 파일입출력 파일을 다르게 만들기 위해 선언됨.(유저간의 구분을 위해)
	int fieldMoney;//필드에 깔린 금액.

	User() {

	}

	User(int index) {//this->playerNum=index; Index값이 playerNum 값과 같음. +) 유저 참여수에 따라 case 를 더 추가할 예정.
		switch (index) {
		case 1:
		{
			ofstream ofs;
			string str = "ID 입력 : ";
			string str2 = "자산 입력 : ";
			ofs.open("userID.txt");
			if (!ofs) {
				cout << "Can't open file" << endl;
				exit(0);
			}
			cout << str;
			cin >> playerID;
			this->playerID = playerID;

			cout << str2;
			cin >> assets;
			this->assets = assets;

			ofs << playerID << " " << assets << endl;
			cout << "ID, 자산 입력완료" << endl;

			ofs.close();
			this->whoisPlayer = index;
		}
		break;
		case 2:
		{
			ofstream ofs2;
			string str = "ID 입력 : ";
			string str2 = "자산 입력 : ";
			ofs2.open("userID2.txt");
			if (!ofs2) {
				cout << "Can't open file" << endl;
				exit(0);
			}
			cout << str;
			cin >> playerID;
			this->playerID = playerID;

			cout << str2;
			cin >> assets;
			this->assets = assets;

			ofs2 << playerID << " " << assets << endl;
			cout << "ID, 자산 입력완료" << endl;

			ofs2.close();
			this->whoisPlayer = index;
		}
		break;
		case 3:
		{
			ofstream ofs;
			string str = "ID 입력 : ";
			string str2 = "자산 입력 : ";
			ofs.open("userID3.txt");
			if (!ofs) {
				cout << "Can't open file" << endl;
				exit(0);
			}
			cout << str;
			cin >> playerID;
			this->playerID = playerID;

			cout << str2;
			cin >> assets;
			this->assets = assets;

			ofs << playerID << " " << assets << endl;
			cout << "ID, 자산 입력완료" << endl;

			ofs.close();
			this->whoisPlayer = index;
		}
		break;
		}
	}//객체를 만들면 유저의 ID와 자산의 DB가 파일에 저장됨.

	bool doBet() {//게임 컨트롤러 클래스의 askBetting() 함수를 끌어와서, 베팅을 할경우 함수 호출. 이외의 경우는, 함수 호출 안함.
		char answer;
		while (true) {
			switch (whoisPlayer) {
			case 1:
			{
				cout << "배팅하시겠습니까? (y/n) ";
				cin >> answer;
				if (answer == 'y') {
					while (true) {
						cout << "배팅할 금액을 입력해 주세요: ";
						cin >> betMoney;
						ifstream imoney;
						imoney.open("fieldMoney.txt");
						for (int k = 0; k < 1; k++) {
							imoney >> fieldMoney;
						}
						this->fieldMoney = (fieldMoney + betMoney);
						ofstream omoney("fieldMoney.txt");
						omoney << fieldMoney << endl;
						omoney.close();
						imoney.close();
						if (betMoney > assets) {
							cout << "보유 자산 초과. 다시 배팅해주세요." << endl;// 보유자산보다 배팅금액이 클 경우.(수정)
							this->fieldMoney = fieldMoney;
						}
						else {
							ifstream ifs;
							ifs.open("userID.txt");
							for (int i = 0; i < 1; i++) {
								ifs >> playerID >> assets;
							}//파일 읽어옴
							this->assets = (assets - betMoney);
							ofstream ofs("userID.txt");//파일 저장
							ofs << playerID << assets;//파일 쓰기
							cout << "Player" << whoisPlayer << "님의 남은 자산은" << this->assets << "입니다" << endl;
							ofs.close();
							return true;
						}// betMoney<=assets 일 경우=정상 배팅했을 경우

					}
				}
				else if (answer == 'n') {
					cout << "배팅을 종료합니다." << endl;
					return false;
				}
				else {
					cout << "잘못 입력하셨습니다. 다시 입력해 주세요.";
				}

			}
			break;
			case 2:
			{
				cout << "배팅하시겠습니까? (y/n) ";
				cin >> answer;
				if (answer == 'y') {
					while (true) {
						cout << "배팅할 금액을 입력해 주세요: ";
						cin >> betMoney;
						if (betMoney > assets) {
							cout << "배팅금액이 자산을 초과합니다. 다시 해주세요." << endl;
						}
						else {
							ifstream imoney;
							imoney.open("fieldMoney.txt");
							for (int k = 0; k < 1; k++) {
								imoney >> fieldMoney;
							}
							this->fieldMoney = (fieldMoney + betMoney);
							ofstream omoney("fieldMoney.txt");
							omoney << fieldMoney << endl;
							omoney.close();
							imoney.close();
							ifstream ifs;
							ifs.open("userID2.txt");
							for (int i = 0; i < 1; i++) {
								ifs >> playerID >> assets;
							}
							this->assets = (assets - betMoney);
							ofstream ofs("userID2.txt");
							ofs << playerID << assets;
							cout << "Player" << whoisPlayer << "님의 남은 자산은" << this->assets << "입니다" << endl;
							ofs.close();
							return true;
						}//정상배팅 했을경우.
					}
				}
				else if (answer == 'n') {
					cout << "배팅을 종료합니다." << endl;
					return false;
				}
				else {
					cout << "잘못 입력하셨습니다. 다시 입력해 주세요.";
				}
			}
			break;
			case 3:
			{
				cout << "배팅하시겠습니까? (y/n) ";
				cin >> answer;
				if (answer == 'y') {
					while (true) {
						cout << "배팅할 금액을 입력해 주세요: ";
						cin >> betMoney;
						if (betMoney > assets) {
							cout << "배팅금액이 자산을 초과합니다. 다시 해주세요." << endl;
						}
						else {
							ifstream imoney;
							imoney.open("fieldMoney.txt");
							for (int k = 0; k < 1; k++) {
								imoney >> fieldMoney;
							}
							this->fieldMoney = (fieldMoney + betMoney);
							ofstream omoney("fieldMoney.txt");
							omoney << fieldMoney << endl;
							omoney.close();
							imoney.close();
							ifstream ifs;
							ifs.open("userID3.txt");
							for (int i = 0; i < 1; i++) {
								ifs >> playerID >> assets;
							}
							this->assets = (assets - betMoney);
							ofstream ofs("userID3.txt");
							ofs << playerID << assets;
							cout << "Player" << whoisPlayer << "님의 남은 자산은" << this->assets << "입니다" << endl;
							ofs.close();
							return true;
						}//정상배팅 했을경우.
					}
				}
				else if (answer == 'n') {
					cout << "배팅을 종료합니다." << endl;
					return false;
				}
				else {
					cout << "잘못 입력하셨습니다. 다시 입력해 주세요.";
				}
			}
			break;
			}
		}
	}//배팅할때 실시간으로 -되는 자산.즉, 배팅하는 함수. betMoney=>배팅금액 

	void allAssetShow() {
		cout <<this->playerID<< "님의 총 자산은" << this->assets << "입니다" << endl;
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