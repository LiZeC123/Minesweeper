#include <iostream>
#include <conio.h>
#include "Minesweeper.h"

using std::cin; using std::cout; using std::endl;


int main()
{
	Screen Rc;
	char c;
	Rc.Show();
	while (true) {
		c = _getch();
		switch (c)
		{
		case 'a':
			Rc.GoLeft();
			break;
		case 's':
			Rc.GoDown();
			break;
		case 'd':
			Rc.GoRight();
			break;
		case 'w':
			Rc.GoUp();
			break;
		case 'j':
			Rc.Check();
			break;
		case 'k':
			Rc.Mark();
			break;
		default:
			break;
		}
		if (!Rc.IsLive()) {
			Rc.DeadShow();
			cout << "Game Over!" << endl;
			break;
		}
		if (Rc.IsWin()) {
			Rc.WinShow();
			cout << "You Win!" << endl;
		}
	}
	system("pause");
}