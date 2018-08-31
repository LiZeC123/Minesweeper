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

	//���ָ��λ�õ��׵�������������
	int CheckMine(int cx, int cy);

	//�ݹ鷭������������Ϊ0��λ��
	void RecuCheck(int cx, int cy);

	//��ʾ��Ϸ״̬
	void ShowState();

	//��������ͼ��
	void draw(int x, int y, MineStyle style, int Num = 0);

	//��������������ʱ��Ϸʤ��
	unsigned int NotMineNum = SELF_CELL_WIDTH * SELF_CELL_HEIGHT - SELF_MINE_NUM;
	//���ʣ������
	int MarkNum = SELF_MINE_NUM;
	//���ײ������׵�����
	int CheatNum = 0;
	//�Ƿ���
	bool Live = true;
	//��Ϸ������ʱ
	unsigned int Time = 0;

	//��Ҫ��ȫ��ͼ��
	ACL_Image imgSmile, imgDead, imgWin, imgRedFlag, imgMine, imgWrongMine;


	void resetGameFlag() {
		NotMineNum = SELF_CELL_WIDTH * SELF_CELL_HEIGHT - SELF_MINE_NUM;
		MarkNum = SELF_MINE_NUM;
		CheatNum = 0;
		Live = true;
		Time = 0;
	}

};