#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "Dealer.h"
#include "Card.h"

using namespace std;
class User {
private:
	Card user_card[2];//���� ���� ī�� 2�� 
public:
	int assets;//������ �ڻ�
	int betMoney; //���ñݾ�
	string playerID;//����ID
	int whoisPlayer;//�������� ��������� ������ �ٸ��� ����� ���� �����.(�������� ������ ����)
	int fieldMoney;//�ʵ忡 �� �ݾ�.

	User() {

	}

	User(int index) {//this->playerNum=index; Index���� playerNum ���� ����. +) ���� �������� ���� case �� �� �߰��� ����.
		switch (index) {
		case 1:
		{
			ofstream ofs;
			string str = "ID �Է� : ";
			string str2 = "�ڻ� �Է� : ";
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
			cout << "ID, �ڻ� �Է¿Ϸ�" << endl;

			ofs.close();
			this->whoisPlayer = index;
		}
		break;
		case 2:
		{
			ofstream ofs2;
			string str = "ID �Է� : ";
			string str2 = "�ڻ� �Է� : ";
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
			cout << "ID, �ڻ� �Է¿Ϸ�" << endl;

			ofs2.close();
			this->whoisPlayer = index;
		}
		break;
		case 3:
		{
			ofstream ofs;
			string str = "ID �Է� : ";
			string str2 = "�ڻ� �Է� : ";
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
			cout << "ID, �ڻ� �Է¿Ϸ�" << endl;

			ofs.close();
			this->whoisPlayer = index;
		}
		break;
		}
	}//��ü�� ����� ������ ID�� �ڻ��� DB�� ���Ͽ� �����.

	bool doBet() {//���� ��Ʈ�ѷ� Ŭ������ askBetting() �Լ��� ����ͼ�, ������ �Ұ�� �Լ� ȣ��. �̿��� ����, �Լ� ȣ�� ����.
		char answer;
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
							ofs << playerID << assets;//���� ����
							cout << "Player" << whoisPlayer << "���� ���� �ڻ���" << this->assets << "�Դϴ�" << endl;
							ofs.close();
							return true;
						}// betMoney<=assets �� ���=���� �������� ���

					}
				}
				else if (answer == 'n') {
					cout << "������ �����մϴ�." << endl;
					return false;
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
							return true;
						}//������� �������.
					}
				}
				else if (answer == 'n') {
					cout << "������ �����մϴ�." << endl;
					return false;
				}
				else {
					cout << "�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է��� �ּ���.";
				}
			}
			break;
			case 3:
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
							ifs.open("userID3.txt");
							for (int i = 0; i < 1; i++) {
								ifs >> playerID >> assets;
							}
							this->assets = (assets - betMoney);
							ofstream ofs("userID3.txt");
							ofs << playerID << assets;
							cout << "Player" << whoisPlayer << "���� ���� �ڻ���" << this->assets << "�Դϴ�" << endl;
							ofs.close();
							return true;
						}//������� �������.
					}
				}
				else if (answer == 'n') {
					cout << "������ �����մϴ�." << endl;
					return false;
				}
				else {
					cout << "�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է��� �ּ���.";
				}
			}
			break;
			}
		}
	}//�����Ҷ� �ǽð����� -�Ǵ� �ڻ�.��, �����ϴ� �Լ�. betMoney=>���ñݾ� 

	void allAssetShow() {
		cout <<this->playerID<< "���� �� �ڻ���" << this->assets << "�Դϴ�" << endl;
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