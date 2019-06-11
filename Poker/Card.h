#pragma once
#include <string>

using namespace std;

class Card {
private:
	int Num; // 1 - 13
	string Image; // "Club", "Heart", "Diamond", "Spade"
public:
	void setNum(int num) {
		this->Num = num;
	}

	int getNum() {
		return this->Num;
	}

	void setImage(string image) {
		this->Image = image;
	}

	string getImage() {
		return this->Image;
	}
};