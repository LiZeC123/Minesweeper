
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
			//printf("both click\n");
			Rc.BothClick(x / 30, y / 30);
		}

		if (button == LEFT_BUTTON) {
			//printf("left click\n");
			if (NeedCheat) {
				Rc.cheatLook(x / 30, y / 30);
				NeedCheat = false;
			}
			else {
				Rc.LeftClick(x / 30, y / 30);
			}
		}
		else if (button == RIGHT_BUTTON) {
			//printf("right click");
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
	//printf("key = %d event = %d\n", key, event);
	const static std::string cheat("LIZECISMYDADDY");
	if (key == 'N' && event == KEY_DOWN) {
		Rc.newGame();
	}
	else if (key == 'R' && event == KEY_DOWN) {
		Rc.restartThisGame();
	}
	else if(event == KEY_DOWN){
		Cd.push(key);
		Cd.show();
		if (Cd == cheat) {
			NeedCheat = true;
		}
	}
	Rc.Show();
	//printf("NeedCheat = %d\n", NeedCheat);
}

int Setup()
{
	initWindow("扫雷", 300, 20, SCREEN_WIDTH, SCREEN_HEIGHT);
	//initConsole();
	Rc.Show();
	registerMouseEvent(mouseListener);
	registerKeyboardEvent(KeyBoardListener);
	return 0;
}