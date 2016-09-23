
#include "acllib.h"
#include "Minesweeper.h"
#include <stdio.h>

Screen Rc;
CharDeque Cd;
bool NeedCheat = false;

void mouseListener(int x, int y, int button, int event) 
{
	static int oneButtonStillDown = BUTTON_UP;

	if (Rc.IsLive() && event == BUTTON_DOWN) {
		if (oneButtonStillDown == BUTTON_DOWN && (button == RIGHT_BUTTON || button == LEFT_BUTTON)) {
			Rc.BothClick(x / 30, y / 30);
		}

		if (button == LEFT_BUTTON) {
			if (NeedCheat) {
				Rc.cheatLook(x / 30, y / 30);
				NeedCheat = false;
			}
			else {
				Rc.LeftClick(x / 30, y / 30);
			}
		}
		else if (button == RIGHT_BUTTON) {
			Rc.RightClick(x / 30, y / 30);
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
	initWindow("扫雷", 300, 20, SCREEN_WIDTH, SCREEN_HEIGHT);
	Rc.Show();
	registerMouseEvent(mouseListener);
	registerKeyboardEvent(KeyBoardListener);
	registerTimerEvent(TimeListener);

	startTimer(0, 1000);
	return 0;
}