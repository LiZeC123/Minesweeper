
#include "acllib.h"
#include "Minesweeper.h"
#include <stdio.h>

Screen Rc;

void mouseListener(int x, int y, int button, int event) 
{
	static int oneButtonStillDown = BUTTON_UP;
	
	if (oneButtonStillDown == BUTTON_DOWN && event == BUTTON_DOWN) {
		//单独的一个键，不可能在up之前down两次
		if (button == RIGHT_BUTTON || button == LEFT_BUTTON) {
			printf("both click\n");
			Rc.BothClick(x / 30, y / 30);
		}
	}
	printf("Live = %d\n", Rc.IsLive());

	if (Rc.IsLive()) {
		if (button == LEFT_BUTTON && event == BUTTON_DOWN) {
			printf("left click\n");
			Rc.LeftClick(x / 30, y / 30);
		}
		else if (button == RIGHT_BUTTON && event == BUTTON_DOWN) {
			printf("right click");
			Rc.RightClick(x / 30, y / 30);
		}
	}
	else {
		Rc.Show();
	}

	//最后记录本次的结果，用于下次判断
	if (button == LEFT_BUTTON || button == RIGHT_BUTTON) {
		oneButtonStillDown = event;
		printf("event = %d oneButtonStillDown = %d\n", event, oneButtonStillDown);
	}
}

void KeyBoardListener(int key, int event) {
	printf("%d %d\n", key, event);
	if (key == 'N' && event == KEY_DOWN) {
		Rc.newGame();
	}
	else if (key == 'R' && event == KEY_DOWN) {
		Rc.restartThisGame();
	}
	Rc.Show();
}

int Setup()
{
	initWindow("扫雷", 300, 20, SCREEN_LENGTH, SCREEN_LENGTH);
	initConsole();
	Rc.Show();
	registerMouseEvent(mouseListener);
	registerKeyboardEvent(KeyBoardListener);
	return 0;
}