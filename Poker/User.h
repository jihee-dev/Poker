#pragma once
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
class User {
public:

	int assets;//������ �ڻ�
	int betMoney; //���ñݾ�
	string playerID;//����ID
	int whoisPlayer;//�������� ��������� ������ �ٸ��� ����� ���� �����.(�������� ������ ����)
	int fieldMoney;//�ʵ忡 �� �ݾ�.
	string differplayer;

	User(string ID) { //this->playerNum=index; Index���� playerNum ���� ����. +) ���� �������� ���� case �� �� �߰��� ����.
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
					cout << ID << "�� �α��� �Ǿ����ϴ�." << endl;
				}
			}
		}
		else {
			cout << "������ �� �� �����ϴ�." << endl;
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
	}//�ʵ忡 �򸮴� ���� DB�� �����ϴ� ������.

	int doBet() {
		char answer;
		while (true) {
			cout << "�����Ͻðڽ��ϱ�? (Y/N)";
			cin >> answer;
			if (answer == 'Y') {
				while (true) {
					cout << "������ �ݾ��� �Է��� �ּ���.";
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
						cout << "���� �ڻ� �ʰ�. �ٽ� �������ּ���." << endl;
						this->fieldMoney = fieldMoney;
					}
					else {
						cout << betMoney << "�� �����ϼ̽��ϴ�." << endl;
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
				cout << "������ �����մϴ�." << endl;
				return 0;
			}
			else {
				cout << "�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է��� �ּ���." << endl;
			}
		}
	}
		/*char answer;
		while (true) {
			switch (whoisPlayer) {
			case 1:
			{
				cout << "�����Ͻðڽ��ϱ�? (y/n) ";
				cin >> answer;
				if (answer == 'y') {
					while (true) {
						cout << "������ �ݾ��� �Է��� �ּ���: ";
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
							cout << "���� �ڻ� �ʰ�. �ٽ� �������ּ���." << endl;// �����ڻ꺸�� ���ñݾ��� Ŭ ���.(����)
							this->fieldMoney = fieldMoney;
						}
						else {
							ifstream ifs;
							ifs.open("userID.txt");
							for (int i = 0; i < 1; i++) {
								ifs >> playerID >> assets;
							}//���� �о��
							this->assets = (assets - betMoney);
							ofstream ofs("userID.txt");//���� ����
							ofs << playerID <<" " << assets;//���� ����
							cout << "Player" << whoisPlayer << "���� ���� �ڻ���" << this->assets << "�Դϴ�" << endl;
							ofs.close();
							return assets;
						}// betMoney<=assets �� ���=���� �������� ���

					}
				}
				else if (answer == 'n') {
					cout << "������ �����մϴ�." << endl;
					return 0;
				}
				else {
					cout << "�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է��� �ּ���.";
				}

			}
			break;
			case 2:
			{
				cout << "�����Ͻðڽ��ϱ�? (y/n) ";
				cin >> answer;
				if (answer == 'y') {
					while (true) {
						cout << "������ �ݾ��� �Է��� �ּ���: ";
						cin >> betMoney;
						if (betMoney > assets) {
							cout << "���ñݾ��� �ڻ��� �ʰ��մϴ�. �ٽ� ���ּ���." << endl;
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
							cout << "Player" << whoisPlayer << "���� ���� �ڻ���" << this->assets << "�Դϴ�" << endl;
							ofs.close();
							return assets;
						}//������� �������.
					}
				}
				else if (answer == 'n') {
					cout << "������ �����մϴ�." << endl;
					return 0;
				}
				else {
					cout << "�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է��� �ּ���.";
				}

			}
			break;
			}
		}
	}//�����Ҷ� �ǽð����� -�Ǵ� �ڻ�.��, �����ϴ� �Լ�. betMoney=>���ñݾ�*/ 

	void allAssetShow() {
		cout << "�� �ڻ���" << this->assets << "�Դϴ�" << endl;
	}
	//������ �ִ� �ڻ��� ������.

	/*int assetsMath() {
	if (win) {
	return assets += (�� �ʵ忡 �� ���ñݾ�);
	}*/
	// ���ӳ����� ���ӿ� �� �ǵ��� ������ �ڻ꿡 �����ִ� �Լ�. '���ӿ��� �̱�� ���'�� �Լ��� ���� ��Ʈ�ѷ� Ŭ�������� ����ͼ� ����� ����.

	void playerDeck() {// dealer Ŭ�������� ������ �����ִ� ī�带 user���� ����.
					   //���� ����� ��� .. , DealerŬ������ �����ʿ�. => �ۼ� ���� ����...
	}
	void show() {
		cout << "�ٴڿ� �� �ݾ� : ";
		ifstream imoney;
		char line[200];
		imoney.open("fieldMoney.txt");
		if (imoney.is_open()) {
			while (imoney.getline(line, sizeof(line))) {
				cout << line << endl;
			}
		}
	}//�ʵ忡 �� �� �ݾ��� �����ִ� ����.
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