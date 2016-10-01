#pragma once
#include <array>
#include <iostream>
#include <ctime>

#include <string>
#include <deque>

#include "acllib.h"

//��Ļ�а����ĸ��ӵĳߴ�
//����
#define SMALL_CELL_WIDTH		9
#define SMALL_CELL_HEIGHT		9
//�м�
#define MIDDLE_CELL_WIDTH		16
#define MIDDLE_CELL_HEIGHT		16
//�߼�
#define BIG_CELL_WIDTH			30
#define BIG_CELL_HEIGHT			16
//�Զ���
#define SELF_CELL_WIDTH			BIG_CELL_WIDTH	
#define SELF_CELL_HEIGHT		BIG_CELL_HEIGHT

//�׵�����
#define SMALL_MINE_NUM			10
#define MIDDLE_MINE_NUM			40
#define BIG_MINE_NUM			99
#define SELF_MINE_NUM			BIG_MINE_NUM

//������Ļ�еĳߴ�
#define MINE_LENGTH				30

//
#define CMD_LENGTH				30

//������Ļ�ߴ�
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
	//�������
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