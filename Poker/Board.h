#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std;
class Board {
private:
	string Total[30];
	string ID[15];
	int Assets[15];

public:
	void rankSort() {
		int i = 0, j = 0, m = 0;
		string temp1;
		int temp2;
		string line;
		string buffer[15][2];
		string test[1000];
		int str_cnt;
		int n = 0;
		int k = 0;
		int l = 0;
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
				Assets[l++] = atoi(Total[i].c_str());

			}
		}

		for (j = 15; j > 1; j--) {
			for (i = 0; i < j - 1; i++) {
				if (this->Assets[i] < this->Assets[i + 1]) {
					temp2 = this->Assets[i + 1];
					temp1 = this->ID[i + 1];
					Assets[i + 1] = this->Assets[i];
					ID[i + 1] = this->ID[i];
					Assets[i] = temp2;
					ID[i] = temp1;
				}
			}
		}

		cout << "\t\n--------RANKING--------\n" << endl;
		cout << "playerID\tassets" << endl;
		for (m = 0; m < 15; m++) {
			cout << ID[m] << "\t\t" << Assets[m] << "\n" << endl;
		}
	}
};