#pragma once
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
class User {
public:

	int assets;//유저의 자산
	int betMoney; //배팅금액
	string playerID;//유저ID
	int whoisPlayer;//유저마다 파일입출력 파일을 다르게 만들기 위해 선언됨.(유저간의 구분을 위해)
	int fieldMoney;//필드에 깔린 금액.
	string differplayer;

	User(string ID) { //this->playerNum=index; Index값이 playerNum 값과 같음. +) 유저 참여수에 따라 case 를 더 추가할 예정.
		ifstream iuser;
		ofstream ouser;
		int offset;
		string line;
		assets = 10000;
		iuser.open("playerID.txt");
		if (iuser.is_open()) {
			while (!iuser.eof()) {
				getline(iuser, line);
				if ((offset = line.find(ID, 0)) != string::npos) {
					cout << ID << "가 로그인 되었습니다." << endl;
				}
			}
		}
		else {
			cout << "파일을 열 수 없습니다." << endl;
		}
		this->playerID = ID;
		iuser.close();
		ouser.open("playerMoney.txt");
		for (int k = 65; k < 80; k++) {
			ouser << "player"<< (char)k << " " << assets << endl;
			ouser << " " << endl;
		}
		this->differplayer = playerID.substr(6);
		ouser.close();
	}

	User() {
		ofstream omoney;
		string str3 = "=====Typing 0 to start Game===== ";
		omoney.open("fieldMoney.txt");
		if (!omoney) {
			cout << "Can't open file" << endl;
			exit(0);
		}
		cout << str3 << endl;
		cin >> fieldMoney;
		this->fieldMoney = fieldMoney;
		omoney << fieldMoney << endl;
		omoney.close();
	}//필드에 깔리는 돈의 DB를 저장하는 생성자.

	int doBet() {
		char answer;
		while (true) {
			cout << "배팅하시겠습니까? (Y/N)";
			cin >> answer;
			if (answer == 'Y') {
				while (true) {
					cout << "배팅할 금액을 입력해 주세요.";
					cin >> betMoney;
					ifstream imoney;
					imoney.open("fieldMoney.txt");
					imoney >> fieldMoney;
					this->fieldMoney = (fieldMoney + betMoney);
					ofstream omoney("filedMoney.txt");
					omoney << fieldMoney << endl;
					omoney.close();
					imoney.close();
					if (betMoney > assets) {
						cout << "보유 자산 초과. 다시 배팅해주세요." << endl;
						this->fieldMoney = fieldMoney;
					}
					else {
						cout << betMoney << "원 배팅하셨습니다." << endl;
						ifstream iuser;
						iuser.open("playerMoney.txt");
						while (!iuser.eof()) {
							int offset;
							string line;
							getline(iuser, line);
							if ((offset = line.find(this->differplayer, 0)) != string::npos) {
								iuser >> differplayer >> assets;
								this->assets = (assets - betMoney);
								ofstream ouser;
								ouser.open("playerMoney.txt");
								this->add_plus_plus(iuser, ouser);
								iuser.close();
								ouser.close();
							}
						}

						return assets; 
					}
				}
			}
			else if (answer == 'N') {
				cout << "배팅을 종료합니다." << endl;
				return 0;
			}
			else {
				cout << "잘못 입력하셨습니다. 다시 입력해 주세요." << endl;
			}
		}
	}
		/*char answer;
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
							ofs << playerID <<" " << assets;//파일 쓰기
							cout << "Player" << whoisPlayer << "님의 남은 자산은" << this->assets << "입니다" << endl;
							ofs.close();
							return assets;
						}// betMoney<=assets 일 경우=정상 배팅했을 경우

					}
				}
				else if (answer == 'n') {
					cout << "배팅을 종료합니다." << endl;
					return 0;
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
							return assets;
						}//정상배팅 했을경우.
					}
				}
				else if (answer == 'n') {
					cout << "배팅을 종료합니다." << endl;
					return 0;
				}
				else {
					cout << "잘못 입력하셨습니다. 다시 입력해 주세요.";
				}

			}
			break;
			}
		}
	}//배팅할때 실시간으로 -되는 자산.즉, 배팅하는 함수. betMoney=>배팅금액*/ 

	void allAssetShow() {
		cout << "총 자산은" << this->assets << "입니다" << endl;
	}
	//가지고 있는 자산을 보여줌.

	/*int assetsMath() {
	if (win) {
	return assets += (총 필드에 깔린 배팅금액);
	}*/
	// 게임끝난후 게임에 깔린 판돈을 승자의 자산에 더해주는 함수. '게임에서 이기는 경우'의 함수를 게임 컨트롤러 클래스에서 끌어와서 사용할 예정.

	void playerDeck() {// dealer 클래스에서 딜러가 나눠주는 카드를 user에게 저장.
					   //파일 입출력 사용 .. , Dealer클래스와 협업필요. => 작성 아직 못함...
	}
	void show() {
		cout << "바닥에 깔린 금액 : ";
		ifstream imoney;
		char line[200];
		imoney.open("fieldMoney.txt");
		if (imoney.is_open()) {
			while (imoney.getline(line, sizeof(line))) {
				cout << line << endl;
			}
		}
	}//필드에 깔린 총 금액을 보여주는 역할.
	void add_plus_plus(ifstream &in_stream, ofstream& out_stream) {
		char next;
		in_stream.get(next);
		while (!in_stream.eof()) {
			if (next == '.' && (in_stream.get() == assets )) {
				out_stream << assets;
			}
			else {
				out_stream << next;
				in_stream.get(next);
			}
		}
	}
};