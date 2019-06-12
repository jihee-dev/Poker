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
	EnHandCombination combination;

public:
	static string Total[30];
	static string ID[15];
	static int Assets[15];

	User() {

	}

	User(int index) {//this->playerNum=index; Index���� playerNum ���� ����. +) ���� �������� ���� case �� �� �߰��� ����.
		switch (index) {
		case 1:
		{
			ofstream ofs;
			string str = "ID �Է� : ";
			string str2 = "�ڻ� �Է� : ";
			ofs.open("user1.txt");
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

			ofs << this->playerID << " " << this->assets << endl;
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
			ofs2.open("user2.txt");
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

			ofs2 << this->playerID << " " << this->assets << endl;
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
			ofs.open("user3.txt");
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

			ofs << this->playerID << " " << this->assets << endl;
			cout << "ID, �ڻ� �Է¿Ϸ�" << endl;

			ofs.close();
			this->whoisPlayer = index;
		}
		break;
		}
	}//��ü�� ����� ������ ID�� �ڻ��� DB�� ���Ͽ� �����.

	Card* getUserCard() {
		return user_card;
	}

	EnHandCombination getCombination() {
		return this->combination;
	}

	bool doBet() {//���� ��Ʈ�ѷ� Ŭ������ askBetting() �Լ��� ����ͼ�, ������ �Ұ�� �Լ� ȣ��. �̿��� ����, �Լ� ȣ�� ����.
		char answer;
		while (true) {
			switch (whoisPlayer) {
			case 1:
			{
				cout << "�����Ͻðڽ��ϱ�? (Y/N) ";
				cin >> answer;
				if (answer == 'Y'||answer=='y') {
					while (true) {
						cout << "������ �ݾ��� �Է��� �ּ���: ";
						cin >> betMoney;
						if (betMoney > assets) {
							cout << "���� �ڻ� �ʰ�. �ٽ� �������ּ���." << endl;// �����ڻ꺸�� ���ñݾ��� Ŭ ���.
						}
						else {
							ifstream ifs;
							ifs.open("user1.txt");
							for (int i = 0; i < 1; i++) {
								ifs >> playerID >> assets;
							}//���� �о��
							this->assets = (assets - betMoney);
							ofstream ofs("user1.txt");//���� ����
							ofs << playerID <<" "<< assets;//���� ����
							cout << "���ÿϷ�" << endl;
							cout <<"============"<< this->playerID << "���� ���� �ڻ���" << this->assets << "�Դϴ�==========" << endl;
							ofs.close();
							Sleep(2000);
							return true;
						}// betMoney<=assets �� ���=���� �������� ���

					}
				}
				else if (answer == 'N'|| answer == 'n') {
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
				if (answer == 'Y' || answer == 'y') {
					while (true) {
						cout << "������ �ݾ��� �Է��� �ּ���: ";
						cin >> betMoney;
						if (betMoney > assets) {
							cout << "���ñݾ��� �ڻ��� �ʰ��մϴ�. �ٽ� ���ּ���." << endl;
						}
						else {
							ifstream ifs;
							ifs.open("user2.txt");
							for (int i = 0; i < 1; i++) {
								ifs >> playerID >> assets;
							}
							this->assets = (assets - betMoney);
							ofstream ofs("user2.txt");
							ofs << playerID << " " << assets;
							cout <<"==========="<< this->playerID << "���� ���� �ڻ���" << this->assets << "�Դϴ�=========" << endl;
							ofs.close();
							Sleep(2000);
							return true;
						}//������� �������.
					}
				}
				else if (answer == 'n'||answer=='N') {
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
				if (answer == 'Y' || answer == 'y') {
					while (true) {
						cout << "������ �ݾ��� �Է��� �ּ���: ";
						cin >> betMoney;
						if (betMoney > assets) {
							cout << "���ñݾ��� �ڻ��� �ʰ��մϴ�. �ٽ� ���ּ���." << endl;
						}
						else{
							ifstream ifs;
							ifs.open("user3.txt");
							for (int i = 0; i < 1; i++) {
								ifs >> playerID >> assets;
							}
							this->assets = (assets - betMoney);
							ofstream ofs("user3.txt");
							ofs << playerID <<" "<< assets;
							cout <<"=========="<< this->playerID << "���� ���� �ڻ���" << this->assets << "�Դϴ�===========" << endl;
							ofs.close();
							Sleep(2000);
							return true;
						}//������� �������.
					}
				}
				else if (answer == 'n'||answer=='N') {
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