#pragma once
#include <raylib.h>

class Cell
{
public:
	Cell();
	bool isPressed(Vector2 mousePos, bool mousePressed);
	int getState();
	void setState(int state);
	void setRectangle(Rectangle rect);
	Rectangle getRectangle();

private:
	Rectangle cell;
	int cellState;
};
