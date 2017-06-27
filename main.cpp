
#include "acllib.h"
#include "Minesweeper.h"
#include "Screen.h"
#include <stdio.h>

Screen Rc;
CharDeque Cd;
bool NeedCheat = false;

void mouseListener(int x, int y, int button, int event) 
{
	static int oneButtonStillDown = BUTTON_UP;
	
	//点击属性栏直接开始
	if (event == BUTTON_DOWN && y <= 30) {
		Rc.newGame();
		return;
	}

	printf("x = %d y = %d\n", x, y);

	//去除命令行产生的偏移
	y = y - CMD_LENGTH;

	//计算在数据表中的实际坐标
	int int_x = x / MINE_LENGTH;
	int int_y = y / MINE_LENGTH;

	if (Rc.IsLive() && event == BUTTON_DOWN) {
		if (oneButtonStillDown == BUTTON_DOWN && (button == RIGHT_BUTTON || button == LEFT_BUTTON)) {
			Rc.BothClick(int_x, int_y);
		}

		if (button == LEFT_BUTTON) {
			if (NeedCheat) {
				Rc.cheatLook(int_x, int_y);
				NeedCheat = false;
			}
			else {
				printf("In LeftChilk: x = %d y = %d int_x = %d int_y = %d\n", x, y,int_x,int_y);
				Rc.LeftClick(int_x, int_y);
			}
		}
		else if (button == RIGHT_BUTTON) {
			Rc.RightClick(int_x, int_y);
		}
	}

	//最后记录本次的结果，用于下次判断
	if (button == LEFT_BUTTON || button == RIGHT_BUTTON) {
		oneButtonStillDown = event;
	}

	Rc.Show();

}

void KeyBoardListener(int key, int event) {
	const static std::string cheat("LIZECISMYDADDY");
	if (key == 'N' && event == KEY_DOWN) {
		Rc.newGame();
	}
	else if (key == 'R' && event == KEY_DOWN) {
		Rc.restartThisGame();
	}
	else if(event == KEY_DOWN){
		Cd.push(key);
		if (Cd == cheat) {
			NeedCheat = true;
		}
	}
	Rc.Show();
}

void TimeListener(int TimeID)
{
	if (TimeID == 0) {
		Rc.ReflashTime();
		Rc.Show();
	}
}

int Setup()
{
	//已经初始化windows
	initWindow("扫雷", 300, 20, SCREEN_WIDTH, SCREEN_HEIGHT);

	registerMouseEvent(mouseListener);
	registerKeyboardEvent(KeyBoardListener);
	registerTimerEvent(TimeListener);

	Rc.loadImg();
	Rc.Show();
	
	startTimer(0, 1000);
	return 0;
}