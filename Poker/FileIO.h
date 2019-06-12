#pragma once
#include<string>
#include<iostream>
#include<fstream>

using namespace std;

class FileIO {
private:
	string id[15];
	int money[15];
	string Total[30];


public:
	FileIO() {

	}

	string* getIDs() {
		return this->id;
	}
	void setMoney(int i, int val) {
		this->money[i] = val;
	}
	int* getMoneys() {
		return this->money;
	}
	int getMoney(int i) {
		return this->money[i];
	}

	void fileLoad() {
		int n = 0; // total indx
		int k = 0; // id idx
		int j = 0; // money idx

		string line;
		ifstream iuser;

		iuser.open("playerID.txt");

		while (getline(iuser, line)) {
			char buff[100];
			strcpy(buff, line.c_str());

			char* tok = strtok(buff, " ");

			while (tok != NULL) {
				Total[n++] = string(tok);
				tok = strtok(NULL, " ");
			}
		}

		iuser.close();

		for (int i = 0; i < n; i++) {
			if (i % 2 == 0) {
				id[k++] = Total[i];
			}
			else {
				money[j++] = atoi(Total[i].c_str());
			}
		}
	}

	int checkID(string input) {
		for (int i = 0; i < 15; i++) {
			if (input == id[i]) return money[i];
		}
		return -1;
	}

	void fileSave() {
		ofstream ofs;
		ofs.open("playerID.txt");

		if (!ofs) {
			cout << "Unable to open file!" << endl;
			exit(0);
		}

		for (int i = 0; i < 15; i++) {
			ofs << id[i] << " " << money[i] << endl;
		}
	}
};