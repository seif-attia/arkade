#include "playAgainMenu.h"
#include <raylib.h>
#include "button.h"

Menu::Menu(const char* imagePath, Vector2 menuPosition, float scale)
{
	Image image = LoadImage(imagePath);
	int originalWidth = image.width;
	int originalHeight = image.height;

	int newWidth = int(originalWidth * scale);
	int newHeight = int(originalHeight * scale);

	ImageResize(&image, newWidth, newHeight);

	texture = LoadTextureFromImage(image);
	UnloadImage(image);

	menuPosition.x -= newWidth / 2;
	menuPosition.y -= newHeight / 2;


	quitPosition.x = menuPosition.x + newWidth / 4;
	quitPosition.y = menuPosition.y + newHeight / 2;


	playAgainPosition.x = menuPosition.x + newWidth - newWidth / 4;
	playAgainPosition.y = menuPosition.y + newHeight / 2;

	quitButton.Init(imagePath, quitPosition, 0.3);
	playAgainButton.Init(imagePath, playAgainPosition, 0.3);

	position = menuPosition;
}

void Menu::Draw()
{
	DrawTextureV(texture, position, WHITE);
	quitButton.Draw();
	playAgainButton.Draw();
}

Menu::~Menu()
{
	UnloadTexture(texture);
}
