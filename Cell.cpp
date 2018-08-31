#include "Cell.h"

void Number::draw(int x, int y) const
{
	switch (statu)
	{
	case Number::UNCHECKED:
		break;
	case Number::CHECKED:
		break;
	case Number::MARKED:
		break;
	case Number::WRONGMINE:
		break;
	default:
		break;
	}
}

void Number::click()
{
	switch (statu)
	{
	case Number::UNCHECKED:
		statu = CHECKED;
		break;
	case Number::CHECKED:
		break;
	case Number::MARKED:
		break;
	case Number::WRONGMINE:
		break;
	default:
		break;
	}
}

void Number::mark()
{
	switch (statu)
	{
	case Number::UNCHECKED:
		statu = MARKED;
		break;
	case Number::CHECKED:
		break;
	case Number::MARKED:
		statu = UNCHECKED;
		break;
	case Number::WRONGMINE:
		break;
	default:
		break;
	}
}

void Number::die()
{
	switch (statu)
	{
	case Number::UNCHECKED:
		break;
	case Number::CHECKED:
		break;
	case Number::MARKED:
		statu = WRONGMINE;
		break;
	case Number::WRONGMINE:
		break;
	default:
		break;
	}
}

void Mine::draw(int x, int y) const
{

}

void Mine::click()
{
	switch (statu)
	{
	case Mine::UNCHECKED:
		statu = DEAD;
		break;
	case Mine::DEAD:
		break;
	case Mine::MARK:
		break;
	default:
		break;
	}
}

void Mine::mark()
{
	switch (statu)
	{
	case Mine::UNCHECKED:
		statu = MARK;
		break;
	case Mine::DEAD:
		break;
	case Mine::MARK:
		statu = UNCHECKED;
		break;
	default:
		break;
	}
}

void Mine::die()
{
	switch (statu)
	{
	case Mine::UNCHECKED:
		statu = DEAD;
		break;
	case Mine::DEAD:
		break;
	case Mine::MARK:
		break;
	default:
		break;
	}
}
