#include "Minesweeper.h"
#include "acllib.h"
#include <cstdlib>

Screen::Screen()
{
	srand((unsigned int)time(0));
	newGame();
}

void Screen::restartThisGame()
{
	for (auto &r : Data) {
		for (auto &i : r) {
			i.IsCheck = false;
			i.IsMark = false;
			i.Num = 0;
		}
	}

	resetGameFlag();
}

void Screen::newGame()
{
	for (auto & r : Data) {
		for (auto &i : r) {
			i.IsMine = false;
			i.IsCheck = false;
			i.IsMark = false;
			i.Num = 0;
		}
	}

	int i = 0;
	while (i != SELF_MINE_NUM) {
		int ix, iy;
		ix = rand() % SELF_CELL_WIDTH;
		iy = rand() % SELF_CELL_HEIGHT;
		if (Data[iy][ix].IsMine) {
			continue;
		}
		else {
			Data[iy][ix].IsMine = true;
			++i;
		}
	}
	resetGameFlag();
}

void  Screen::Show()
{	
	//先刷新屏幕
	beginPaint();
	clearDevice();
	endPaint();

	if (IsLive()) {
		for (int i = 0; i < SELF_CELL_HEIGHT; ++i) {
			for (int j = 0; j < SELF_CELL_WIDTH; ++j) {
				if (Data[i][j].IsCheck) {
					Data[i][j].draw(j*MINE_LENGTH, i*MINE_LENGTH, IS_CHECK);
				}
				else if (Data[i][j].IsMark) {
					Data[i][j].draw(j*MINE_LENGTH, i*MINE_LENGTH, IS_MARK);
				}
				else  {
					Data[i][j].draw(j*MINE_LENGTH, i*MINE_LENGTH, NO_CKECK);
				}

			}
		}
	}

	if (!IsLive()) {
		for (int i = 0; i < SELF_CELL_HEIGHT; ++i) {
			for (int j = 0; j < SELF_CELL_WIDTH; ++j) {
				if (Data[i][j].IsMark && !Data[i][j].IsMine) {
					Data[i][j].draw(j*MINE_LENGTH, i*MINE_LENGTH, WRONG_MARK);
				}
				else if (Data[i][j].IsMark && Data[i][j].IsMine) {
					Data[i][j].draw(j*MINE_LENGTH, i*MINE_LENGTH, IS_MARK);
				}
				else if (Data[i][j].IsMine) {
					Data[i][j].draw(j*MINE_LENGTH, i*MINE_LENGTH, DEAD_MINE);
				}
				else if (Data[i][j].IsCheck) {
					Data[i][j].draw(j*MINE_LENGTH, i*MINE_LENGTH, IS_CHECK);
				}
				else {
					Data[i][j].draw(j*MINE_LENGTH, i*MINE_LENGTH, NO_MARK);
				}
				
			}
		}
	}

	if (IsWin()) {
		for (int i = 0; i < SELF_CELL_HEIGHT; ++i) {
			for (int j = 0; j < SELF_CELL_WIDTH; ++j) {
				if (Data[i][j].IsCheck) {
					Data[i][j].draw(j*MINE_LENGTH, i*MINE_LENGTH, IS_CHECK);
				}
				else{
					Data[i][j].draw(j*MINE_LENGTH, i*MINE_LENGTH, IS_MARK);
				}
			}
		}

		beginPaint();
		setTextColor(RED);
		setTextSize(30);
		paintText(0, 0, "You Win!");
		endPaint();
	}

	ShowState();
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
			--MarkNum;
		else
			++MarkNum;
	}
	Show();
}

void Screen::BothClick(int x, int y)
{
	if (!Data[y][x].IsCheck) {
		return;
	}

	int markNum = 0;
	for (int iy = y - 1; iy <= y + 1; ++iy) {
		for (int ix = x - 1; ix <= x + 1; ++ix) {
			if (iy < 0 || ix < 0)
				continue;
			if (iy >= Data.size() || ix >= Data[0].size())
				continue;
			if (ix == x && iy == y)
				continue;
			if (!Data[iy][ix].IsCheck && Data[iy][ix].IsMark)
				++markNum;
		}
	}

	if (markNum == Data[y][x].Num) {
		for (int iy = y - 1; iy <= y + 1; ++iy) {
			for (int ix = x - 1; ix <= x + 1; ++ix) {
				if (iy < 0 || ix < 0)
					continue;
				if (iy >= Data.size() || ix >= Data[0].size())
					continue;
				if (ix == x && iy == y)
					continue;
				if (!Data[iy][ix].IsCheck && !Data[iy][ix].IsMark)
					LeftClick(ix, iy);
			}
		}
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

void Screen::cheatLook(int cx, int cy)
{
	for (int iy = cy - 1; iy <= cy + 1; ++iy) {
		for (int ix = cx - 1; ix <= cx + 1; ++ix) {
			if (iy < 0 || ix < 0)
				continue;
			if (iy >= Data.size() || ix >= Data[0].size())
				continue;
			if (ix == cx && iy == cy)
				continue;
			if (Data[iy][ix].IsMine) {
				Data[iy][ix].IsMark = true;
				--MarkNum;
				++CheatNum;
			}
				
		}
	}
}

void Screen::ReflashTime()
{
	if (Live) {
		++Time;
	}
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

void Screen::ShowState()
{
	static char MarkString[4];
	static char TimeString[4];
	char MinePrompt[10] = "Mine:";
	char TimePrompt[10] = "Time:";

	_itoa_s(MarkNum, MarkString, 10);
	_itoa_s(Time, TimeString, 10);

	strcat(MinePrompt, MarkString);
	strcat(TimePrompt, TimeString);
	const int offset = 5;

	beginPaint();
	setTextColor(BLUE);
	setTextSize(CMD_LENGTH - offset);
	setPenColor(BLUE);
	line(0, SCREEN_HEIGHT - CMD_LENGTH, SCREEN_WIDTH, SCREEN_HEIGHT - CMD_LENGTH);
	paintText(0, SCREEN_HEIGHT - CMD_LENGTH + offset,MinePrompt);
	paintText(SCREEN_WIDTH - CMD_LENGTH * 4, SCREEN_HEIGHT - CMD_LENGTH + offset, TimePrompt);
	endPaint();
	
}

void Mine::draw(int x, int y,MineStyle style)
{
	static char * number[] = { " ","1","2","3","4","5","6","7","8","9" };
	static const int offsetX = 8;
	static const int offsetY = 4;
	beginPaint();
	setTextSize(19);
	setPenColor(BLACK);
	

	int nx = x + MINE_LENGTH, ny = y + MINE_LENGTH;

	switch (style )
	{
	case IS_CHECK:
		setTextColor(BLUE);
		paintText(x + offsetX, y + offsetY, number[Num]);
		break;
	case NO_CKECK:
		line(x, y, nx, y);
		line(nx, y, nx, ny);
		line(nx, ny, x, ny);
		line(x, ny, x, y);
		line(x + MINE_LENGTH / 3, y, x, y + MINE_LENGTH / 3);
		line(x + 2 * MINE_LENGTH / 3, y, x, y + 2 * MINE_LENGTH / 3);
		line(nx, y, x, ny);
		break;
	case IS_MARK:
		line(x, y, nx, y);
		line(nx, y, nx, ny);
		line(nx, ny, x, ny);
		line(x, ny, x, y);
		setTextColor(BLUE);
		paintText(x + offsetX, y + offsetY, "M");
		break;
	case NO_MARK:
		line(x, y, nx, y);
		line(nx, y, nx, ny);
		line(nx, ny, x, ny);
		line(x, ny, x, y);
		line(x + MINE_LENGTH / 3, y, x, y + MINE_LENGTH / 3);
		line(x + 2 * MINE_LENGTH / 3, y, x, y + 2 * MINE_LENGTH / 3);
		line(nx, y, x, ny);
		break;
	case DEAD_MINE:
		line(x, y, nx, y);
		line(nx, y, nx, ny);
		line(nx, ny, x, ny);
		line(x, ny, x, y);
		setTextColor(BLACK);
		paintText(x + offsetX, y + offsetY, "B");
		break;
	case WRONG_MARK:
		line(x, y, nx, y);
		line(nx, y, nx, ny);
		line(nx, ny, x, ny);
		line(x, ny, x, y);
		setTextColor(RED);
		paintText(x + offsetX, y + offsetY, "X");
		break;
	default:
		break;
	}

	endPaint();
}

void CharDeque::push(char one)
{
	content.push_back(one);
	if (content.size() > MaxSize) {
		content.pop_front();
	}
}

void CharDeque::show()
{
	for (const auto &i : content) {
		std::cout << (char)i;
	}
	std::cout << std::endl;
}

bool CharDeque::operator==(const std::string & rs)
{
	auto sit = rs.crbegin();
	auto dit = content.crbegin();
	while (sit != rs.crend() && dit != content.crend()) {
		if (*sit != *dit) {
			return false;
		}
		++sit;
		++dit;
	}
	return true;
}
