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

	void setShape(string shape) {
		this->Image = shape;
	}

	string getImage() {
		return this->Image;
	}
};
};