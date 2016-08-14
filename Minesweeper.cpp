#include "Minesweeper.h"
#include "acllib.h"

Screen::Screen()
{
	srand((unsigned int)time(0));
	int i = 0;
	while (i != SELF_MINE_NUM) {
		int ix, iy;
		ix = rand() % SELF_CELL_LENGTH;
		iy = rand() % SELF_CELL_LENGTH;
		if (Data[iy][ix].IsMine) {
			continue;
		}
		else {
			Data[iy][ix].IsMine = true;
			++i;
		}
	}
}

void  Screen::Show()
{	
	//先刷新屏幕
	beginPaint();
	clearDevice();
	endPaint();

	for (int i = 0; i < SELF_CELL_LENGTH; ++i) {
		for (int j = 0; j < SELF_CELL_LENGTH; ++j) {
			Data[i][j].draw(j*MINE_LENGTH, i*MINE_LENGTH);
		}
	}
	if (!IsLive()) {
		//叠加错误的地方，标记误判，以及没有发现的雷
		beginPaint();
		setTextColor(RED);
		setTextSize(30);
		paintText(0, 0, "Game Over!");
		endPaint();
	}
	if (IsWin()) {
		beginPaint();
		setTextColor(RED);
		setTextSize(30);
		paintText(0, 0, "You Win!");
		endPaint();
	}

}

void Screen::LeftClick(int x, int y)
{
	//注意由于坐标系的定义和二维数组的定义
	//顺序是反的
	if (!Data[y][x].IsCheck && !Data[y][x].IsMark) {
		Data[y][x].IsCheck = true;
		if (Data[y][x].IsMine) {
			Live = false;
		}
		else {
			--NotMineNum;
			Data[y][x].Num = CheckMine(x, y);
			if (Data[y][x].Num == 0) {
				RecuCheck(x, y);
			}
			Show();
		}
	}
}

void Screen::RightClick(int x, int y)
{
	if (!Data[y][x].IsCheck) {
		Data[y][x].IsMark = !Data[y][x].IsMark;
		if (Data[y][x].IsMark)
			++MarkNum;
		else
			--MarkNum;
	}
	Show();
}

bool Screen::IsLive()
{
	return Live;
}

bool Screen::IsWin()
{
	return NotMineNum == 0;
}

int Screen::CheckMine(int cx, int cy)
{
	int count = 0;
	for (int iy = cy - 1; iy <= cy + 1; ++iy) {
		for (int ix = cx - 1; ix <= cx + 1; ++ix) {
			if (iy < 0 || ix < 0)
				continue;
			if (iy >= Data.size() || ix >= Data[0].size())
				continue;
			if (ix == cx && iy == cy)
				continue;
			if (Data[iy][ix].IsMine)
				++count;
		}
	}
	return count;

	
}

void Screen::RecuCheck(int cx, int cy)
{
	for (int iy = cy - 1; iy <= cy + 1; ++iy) {
		for (int ix = cx - 1; ix <= cx + 1; ++ix) {
			if (iy < 0 || ix < 0)
				continue;
			if (iy >= Data.size() || ix >= Data[0].size())
				continue;
			if (ix == cx && iy == cy)
				continue;
			if ( !Data[iy][ix].IsCheck ) {
				Data[iy][ix].IsCheck = true;
				--NotMineNum;
				Data[iy][ix].Num = CheckMine(ix, iy);
				if (Data[iy][ix].Num == 0) 
					RecuCheck(ix, iy);
			}
		}
	}
}

void Mine::draw(int x, int y)
{
	static char * number[] = { " ","1","2","3","4","5","6","7","8","9" };
	static const int offsetX = 8;
	static const int offsetY = 4;
	beginPaint();
	setTextSize(19);
	setTextColor(BLUE);

	int nx = x + MINE_LENGTH, ny = y + MINE_LENGTH;
	if (IsCheck) {
		paintText(x + offsetX, y + offsetY, number[Num]);
	}
	else if (IsMark) {
		line(x, y, nx, y);
		line(nx, y, nx, ny);
		line(nx, ny, x, ny);
		line(x, ny, x, y);
		paintText(x + offsetX, y + offsetY, "M");
	}
	else {
		line(x, y, nx, y);
		line(nx, y, nx, ny);
		line(nx, ny, x, ny);
		line(x, ny, x, y);
		line(x + MINE_LENGTH / 3, y, x, y + MINE_LENGTH / 3);
		line(x + 2 * MINE_LENGTH / 3, y, x, y + 2 * MINE_LENGTH / 3);
		line(nx, y, x, ny);	
	}
	endPaint();
}
