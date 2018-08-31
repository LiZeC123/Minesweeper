#pragma once
#include "acllib.h"
#include "setting.h"
#include "Minesweeper.h"
#include <array>

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