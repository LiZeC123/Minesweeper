
#include "acllib.h"
#include "Minesweeper.h"
#include <stdio.h>

Screen Rc;

void mouseListener(int x, int y, int button, int event) 
{
	
	if (Rc.IsLive()) {
		printf("x = %d y = %d button = %d event = %d\n", x, y, button, event);
		if (button == LEFT_BUTTON && event == BUTTON_DOWN) {
			Rc.LeftClick(x / 30, y / 30);
		}
		else if (button == RIGHT_BUTTON && event == BUTTON_DOWN) {
			Rc.RightClick(x / 30, y / 30);
		}
	}
	else {
		Rc.Show();
	}
}


int Setup()
{
	initWindow("É¨À×", DEFAULT, DEFAULT, SCREEN_LENGTH, SCREEN_LENGTH);
	Rc.Show();
	registerMouseEvent(mouseListener);
	return 0;
}