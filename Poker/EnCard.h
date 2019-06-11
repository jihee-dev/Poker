#pragma once
#include"Num.h"
#include"Shape.h"
#include<string>

using namespace std;

class Card {
private:
	EnNum num;
	EnShape shape;

public:
	void setNum(EnNum num) {
		this->num = num;
	}

	EnNum getNum() {
		return this->num;
	}

	void setShape(EnShape shape) {
		this->shape = shape;
	}

	EnShape getShape() {
		return this->shape;
	}

	string printNum(EnNum n) {
		switch (n)
		{
		case TWO:
			return "2";
			break;
		case THREE:
			return "3";
			break;
		case FOUR:
			return "4";
			break;
		case FIVE:
			return "5";
			break;
		case SIX:
			return "6";
			break;
		case SEVEN:
			return "7";
			break;
		case EIGHT:
			return "8";
			break;
		case NINE:
			return "9";
			break;
		case TEN:
			return "10";
			break;
		case JACK:
			return "JACK";
			break;
		case QUEEN:
			return "QUEEN";
			break;
		case KING:
			return "KING";
			break;
		case ACE:
			return "ACE";
			break;
		default:
			return NULL;
			break;
		}
	}

	string printShape(EnShape s) {
		switch (s)
		{
		case CLUB:
			return "CLUB";
			break;
		case HEART:
			return "HEART";
			break;
		case DIAMOND:
			return "DIAMOND";
			break;
		case SPADE:
			return "SPADE";
			break;
		default:
			return NULL;
			break;
		}
	}
};