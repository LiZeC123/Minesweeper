
#include "acllib.h"
#include "Minesweeper.h"
#include <stdio.h>





void keyListener(int key, int event) {
	printf("key = %d event = %d\n",key,event);
}

int Setup()
{
	initWindow("É¨À×", DEFAULT, DEFAULT, 300, 300);

	//initConsole();
	printf("Hello\n");
	beginPaint();
	line(30, 0, 30, 30);
	line(0, 30, 30, 30);
	setTextSize(19);
	setTextColor(BLUE);
	paintText(8, 4, "1");
	endPaint();
	return 0;
}