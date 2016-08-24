
#include "acllib.h"
#include "Minesweeper.h"
#include <stdio.h>

Screen Rc;

void mouseListener(int x, int y, int button, int event) 
{
	static int oneButtonStillDown;
	if (button == LEFT_BUTTON || button == RIGHT_BUTTON) {
		oneButtonStillDown = event;
	}
	
	if (oneButtonStillDown == BUTTON_DOWN && event == BUTTON_DOWN) {
		//单独的一个键，不可能在up之前down两次
		if (button == RIGHT_BUTTON || button == LEFT_BUTTON) {
			printf("both click\n");
			Rc.BothClick(x / 30, y / 30);
		}
	}

	if (Rc.IsLive()) {
		printf("x = %d y = %d button = %d event = %d\n", x, y, button, event);
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
}


int Setup()
{
	initWindow("扫雷", 300, 50, SCREEN_LENGTH, SCREEN_LENGTH);
	//initConsole();
	Rc.Show();
	registerMouseEvent(mouseListener);
	return 0;
}