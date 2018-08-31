#pragma once
class Drawable
{
public:
	virtual void draw(int x, int y) const = 0;
	virtual void click() = 0;
	virtual void mark() = 0;
	virtual void die() = 0;

private:

};