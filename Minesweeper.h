#pragma once
#include <array>
#include <iostream>
#include <ctime>

#include <string>
#include <deque>

#include "acllib.h"

//屏幕中包含的格子的尺寸
#define BIG_SIZE

#if defined(SMALL_SIZE)
//初级
#define SELF_CELL_WIDTH			9
#define SELF_CELL_HEIGHT		9
#define SELF_MINE_NUM			10

#elif defined(MIDDLE_SIZE)
//中级
#define SELF_CELL_WIDTH			16
#define SELF_CELL_HEIGHT		16
#define SELF_MINE_NUM			40

#elif defined(BIG_SIZE)
//高级
#define SELF_CELL_WIDTH			30
#define SELF_CELL_HEIGHT		16
#define SELF_MINE_NUM			99

#elif defined(USER_DEFINED)
//自定义
#define SELF_CELL_WIDTH			__USER_WIDTH__
#define SELF_CELL_HEIGHT		__USER_HEIGHT__

#else
//error的出现本身就是一个错误
#error WIDTH and HEIGHT  not defined
#endif //判断游戏模式

//雷在屏幕中的尺寸
#define MINE_LENGTH				30

//命令行区域宽度
#define CMD_LENGTH				30

//雷区屏幕尺寸
#define SCREEN_WIDTH			MINE_LENGTH * SELF_CELL_WIDTH
#define SCREEN_HEIGHT			MINE_LENGTH * SELF_CELL_HEIGHT + CMD_LENGTH


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


public:
	bool IsMine = false;
	bool IsCheck = false;
	bool IsMark = false;
	int  Num = 0;
	
private:
	

};

class Screen
{
public:
	Screen();
	void loadImg();
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
	void ReflashTime();

private:
	std::array<std::array<Mine, SELF_CELL_WIDTH>, SELF_CELL_HEIGHT> Data;

	//检查指定位置的雷的数量，并返回
	int CheckMine(int cx, int cy);

	//递归翻开所有雷数量为0的位置
	void RecuCheck(int cx, int cy);

	//显示游戏状态
	void ShowState();

	//辅助绘制图形
	void draw(int x, int y, MineStyle style, int Num = 0);
	
	//非雷数量，归零时游戏胜利
	unsigned int NotMineNum = SELF_CELL_WIDTH * SELF_CELL_HEIGHT - SELF_MINE_NUM;
	//标记剩余雷数
	int MarkNum = SELF_MINE_NUM;
	//作弊产生的雷的数量
	int CheatNum = 0;
	//是否存活
	bool Live = true;
	//游戏单局用时
	unsigned int Time = 0;

	//需要的全部图形
	ACL_Image imgSmile, imgDead, imgWin, imgRedFlag, imgMine, imgWrongMine;
	

	void resetGameFlag() {
		NotMineNum = SELF_CELL_WIDTH * SELF_CELL_HEIGHT - SELF_MINE_NUM;
		MarkNum = SELF_MINE_NUM;
		CheatNum = 0;
		Live = true;
		Time = 0;
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