#pragma once
#include "Drawable.h"

class Cell : public Drawable
{
public:
	virtual void draw(int x, int y) const = 0;
	virtual void click();
	virtual void mark();
	virtual void unmark();

private:
	static const int None = 0;
	static const int Clicked = 1;
	static const int Marked = 2;

	int status;
};


class Number : public Drawable
{
public:
	void draw(int x, int y) const override;
	void click() override;
	void mark() override;
	void die() override;
private:
	enum Status
	{
		UNCHECKED,
		CHECKED,
		MARKED,
		WRONGMINE,
	};
	Status statu;
};

class Mine : public Drawable
{
public:
	void draw(int x, int y) const override;
	void click() override;
	void mark() override;
	void die() override;
private:
	enum Status
	{
		UNCHECKED,
		DEAD,
		MARK,
	};
	Status statu;
};


//
/*
���Ե��������࣬һ�����ʾ��ͨ���ӣ�һ�����ʾ����ĸ���
����������ͬ���Ĳ����¿��ܳ��ֲ�ͬ�ı�����ʽ

*/