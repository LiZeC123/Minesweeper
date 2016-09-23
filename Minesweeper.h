#pragma once
#include <array>
#include <iostream>
#include <ctime>

#include <string>
#include <deque>

//注意，调整宏值，需要全部重新编译
//屏幕中包含的格子的尺寸
//初级
#define SMALL_CELL_WIDTH		9
#define SMALL_CELL_HEIGHT		9
//中级
#define MIDDLE_CELL_WIDTH		16
#define MIDDLE_CELL_HEIGHT		16
//高级
#define BIG_CELL_WIDTH			30
#define BIG_CELL_HEIGHT			16
//自定义
#define SELF_CELL_WIDTH			BIG_CELL_WIDTH	
#define SELF_CELL_HEIGHT		BIG_CELL_HEIGHT

//雷的数量
#define SMALL_MINE_NUM			10
#define MIDDLE_MINE_NUM			40
#define BIG_MINE_NUM			99
#define SELF_MINE_NUM			BIG_MINE_NUM

//雷在屏幕中的尺寸
#define MINE_LENGTH				30

//雷区屏幕尺寸
#define SCREEN_WIDTH			MINE_LENGTH * SELF_CELL_WIDTH
#define SCREEN_HEIGHT			MINE_LENGTH * SELF_CELL_HEIGHT

//#define CMD_LENGTH				30


enum MineStyle {
	IS_CHECK,
	NO_CKECK,
	IS_MARK,
	NO_MARK,
	DEAD_MINE,
	WRONG_MARK,
};

class Mine
{
public:
	bool IsMine = false;
	bool IsCheck = false;
	bool IsMark = false;
	int  Num = 0;
	void draw(int x, int y, MineStyle style);
};

class Screen
{
public:
	Screen();
	void restartThisGame();
	void newGame();

public:

	void Show();

	void LeftClick(int x, int y);
	void RightClick(int x, int y);
	void BothClick(int x, int y);

	bool IsLive();
	bool IsWin();

	void cheatLook(int cx, int cy);

private:
	std::array<std::array<Mine, SELF_CELL_WIDTH>, SELF_CELL_HEIGHT> Data;

	//检查指定位置的雷的数量，并返回
	int CheckMine(int cx, int cy);

	//递归翻开所有雷数量为0的位置
	void RecuCheck(int cx, int cy);

	//非雷数量，归零时游戏胜利
	unsigned int NotMineNum = SELF_CELL_WIDTH * SELF_CELL_HEIGHT - SELF_MINE_NUM;

	unsigned int MarkNum = 0;

	bool Live = true;

	void resetGameFlag() {
		NotMineNum = SELF_CELL_WIDTH * SELF_CELL_HEIGHT - SELF_MINE_NUM;
		MarkNum = 0;
		Live = true;
	}

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