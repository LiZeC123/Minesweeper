#pragma once

//屏幕中包含的格子的尺寸
#define MIDDLE_SIZE

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