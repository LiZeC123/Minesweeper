#pragma once
#include <array>
#include <iostream>
#include <ctime>

#include <string>
#include <deque>

#include "acllib.h"

class Mine
{
public:


public:
	bool IsMine = false;
	bool IsCheck = false;
	bool IsMark = false;
	int  Num = 0;
	
private:
	

};



class CharDeque {
public:
	CharDeque();
public:
	void push(char one);
	bool canCheat();
private:
	const std::string cheatString;
	std::deque<int> content;
	const int MaxSize;
};