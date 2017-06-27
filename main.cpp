
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
	
	//���������ֱ�ӿ�ʼ
	if (event == BUTTON_DOWN && y <= 30) {
		Rc.newGame();
		return;
	}

	printf("x = %d y = %d\n", x, y);

	//ȥ�������в�����ƫ��
	y = y - CMD_LENGTH;

	//���������ݱ��е�ʵ������
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

	//����¼���εĽ���������´��ж�
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
	//�Ѿ���ʼ��windows
	initWindow("ɨ��", 300, 20, SCREEN_WIDTH, SCREEN_HEIGHT);

	registerMouseEvent(mouseListener);
	registerKeyboardEvent(KeyBoardListener);
	registerTimerEvent(TimeListener);

	Rc.loadImg();
	Rc.Show();
	
	startTimer(0, 1000);
	return 0;
}