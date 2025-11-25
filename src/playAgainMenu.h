#pragma once
#include <raylib.h>
#include "button.h"

class Menu
{
public:
	Menu(const char* imagePath, Vector2 menuPosition, float scale);
	void Draw();
	~Menu();

private:
	Texture2D texture;
	Vector2 position;
	Vector2 quitPosition;
	Vector2 playAgainPosition;
	Button quitButton;
	Button playAgainButton;

};
