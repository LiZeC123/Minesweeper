#pragma once
#include <array>
#include <iostream>
#include <ctime>

//ע�⣬������ֵ����Ҫȫ�����±���
//��Ļ�а����ĸ�������
#define SMALL_CELL_LENGTH		9
#define MIDDLE_CELL_LENGTH		16
#define SELF_CELL_LENGTH		MIDDLE_CELL_LENGTH

//�׵�����
#define SMALL_MINE_NUM			10
#define MIDDLE_MINE_NUM			40
#define SELF_MINE_NUM			MIDDLE_MINE_NUM

//������Ļ�еĳߴ�
#define MINE_LENGTH				30

//������Ļ�ߴ�
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

	//���ָ��λ�õ��׵�������������
	int CheckMine(int cx, int cy);

	//�ݹ鷭������������Ϊ0��λ��
	void RecuCheck(int cx, int cy);

	//��������������ʱ��Ϸʤ��
	unsigned int NotMineNum = SELF_CELL_LENGTH * SELF_CELL_LENGTH - SELF_MINE_NUM;

	unsigned int MarkNum = 0;

	bool Live = true;

};