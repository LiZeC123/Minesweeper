#pragma once
#include <array>
#include <iostream>
#include <ctime>

//注意，调整宏值，需要全部重新编译
//屏幕中包含的格子数量
#define SMALL_CELL_LENGTH		9
#define MIDDLE_CELL_LENGTH		16
#define SELF_CELL_LENGTH		MIDDLE_CELL_LENGTH

//雷的数量
#define SMALL_MINE_NUM			10
#define MIDDLE_MINE_NUM			40
#define SELF_MINE_NUM			MIDDLE_MINE_NUM

//雷在屏幕中的尺寸
#define MINE_LENGTH				30

//雷区屏幕尺寸
#define SCREEN_LENGTH			MINE_LENGTH * SELF_CELL_LENGTH	

#define CMD_LENGTH				30

class Mine
{
public:
	bool IsMine = false;
	bool IsCheck = false;
	bool IsMark = false;
	int  Num = 0;
	void draw(int x, int y);
};

class Screen
{
public:
	Screen();
public:


	void Show();

	void LeftClick(int x, int y);
	void RightClick(int x, int y);

	bool IsLive();
	bool IsWin();

private:
	std::array<std::array<Mine, SELF_CELL_LENGTH>, SELF_CELL_LENGTH> Data;

	//检查指定位置的雷的数量，并返回
	int CheckMine(int cx, int cy);

	//递归翻开所有雷数量为0的位置
	void RecuCheck(int cx, int cy);

	//非雷数量，归零时游戏胜利
	unsigned int NotMineNum = SELF_CELL_LENGTH * SELF_CELL_LENGTH - SELF_MINE_NUM;

	unsigned int MarkNum = 0;

	bool Live = true;

};