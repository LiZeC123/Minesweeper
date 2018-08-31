#pragma once

//��Ļ�а����ĸ��ӵĳߴ�
#define MIDDLE_SIZE

#if defined(SMALL_SIZE)
//����
#define SELF_CELL_WIDTH			9
#define SELF_CELL_HEIGHT		9
#define SELF_MINE_NUM			10

#elif defined(MIDDLE_SIZE)
//�м�
#define SELF_CELL_WIDTH			16
#define SELF_CELL_HEIGHT		16
#define SELF_MINE_NUM			40

#elif defined(BIG_SIZE)
//�߼�
#define SELF_CELL_WIDTH			30
#define SELF_CELL_HEIGHT		16
#define SELF_MINE_NUM			99

#elif defined(USER_DEFINED)
//�Զ���
#define SELF_CELL_WIDTH			__USER_WIDTH__
#define SELF_CELL_HEIGHT		__USER_HEIGHT__

#else
//error�ĳ��ֱ������һ������
#error WIDTH and HEIGHT  not defined
#endif //�ж���Ϸģʽ

//������Ļ�еĳߴ�
#define MINE_LENGTH				30

//������������
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