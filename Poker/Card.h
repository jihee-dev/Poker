#pragma once
#include <string>

using namespace std;

class Card {
private:
	int Num;
	string Image;
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