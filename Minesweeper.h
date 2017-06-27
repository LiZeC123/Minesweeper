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
	CharDeque() = default;
public:
	void push(char one);
	void show();
public:
	bool operator==(const std::string & rs);
private:
	std::deque<int> content;
	const int MaxSize = 14;
};