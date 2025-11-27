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

	closeMenuPosition.x = menuPosition.x + newWidth - 30;
	closeMenuPosition.y = menuPosition.y + 30;

	quitButton.Init("assets/sprites/menu_buttons.png", quitPosition, 0.3);
	playAgainButton.Init("assets/sprites/menu_buttons.png", playAgainPosition, 0.3);
	closeMenuButton.Init("assets/sprites/exit_button.png", closeMenuPosition, 0.15);

	position = menuPosition;
}

void Menu::Draw()
{

	DrawTextureV(texture, position, WHITE);
	quitButton.Draw();
	playAgainButton.Draw();
	closeMenuButton.Draw();

	const int FONT_SIZE = 25;


	// Get the actual size from the button object
	float quitW = quitButton.getWidth();
	float quitH = quitButton.getHeight();
	Vector2 quitPos = quitButton.getPostion();

	const char* quitText = "QUIT";
	int quitTextWidth = MeasureText(quitText, FONT_SIZE);


	int quitTextX = (int)(quitPos.x + (quitW / 2) - (quitTextWidth / 2));
	int quitTextY = (int)(quitPos.y + (quitH / 2) - (FONT_SIZE / 2));

	DrawText(quitText, quitTextX, quitTextY, FONT_SIZE, BLACK);



	float playW = playAgainButton.getWidth();
	float playH = playAgainButton.getHeight();
	Vector2 playPos = playAgainButton.getPostion();

	const char* playText = "PLAY AGAIN";
	int playTextWidth = MeasureText(playText, FONT_SIZE);

	int playTextX = (int)(playPos.x + (playW / 2) - (playTextWidth / 2));
	int playTextY = (int)(playPos.y + (playH / 2) - (FONT_SIZE / 2));

	DrawText(playText, playTextX, playTextY, FONT_SIZE, BLACK);
}

Menu::~Menu()
{
	UnloadTexture(texture);
}
