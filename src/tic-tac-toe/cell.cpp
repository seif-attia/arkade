#include "cell.h"
#include "tic_tac_toe.h"

Cell::Cell()
{
	cellState = IS_EMPTY;
}


bool Cell::isPressed(Vector2 mousePos, bool mousePressed)
{
	if (CheckCollisionPointRec(mousePos, cell) && mousePressed)
	{
		return true;
	}
	return false;
}

int Cell::getState()
{
	return cellState;
}

void Cell::setState(int state)
{
	cellState = state;
}

void Cell::setRectangle(Rectangle rect)
{
	cell = rect;
}

Rectangle Cell::getRectangle()
{
	return cell;
}

