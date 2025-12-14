#pragma once
#include <raylib.h>
#include "button.h"

class Menu
{
public:
	Menu(const char* imagePath, Vector2 menuPosition, float scale);
	void Draw();
	~Menu();

	Button quitButton;
	Button playAgainButton;
	Button closeMenuButton;

private:
	Texture2D texture;
	Vector2 position;
	Vector2 quitPosition;
	Vector2 playAgainPosition;
	Vector2 closeMenuPosition;

};
