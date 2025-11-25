#include "button.h"
#include <raylib.h>

Button::Button()
{
	texture = { 0 };
	position = { 0,0 };
}

Button::Button(const char* imagePath, Vector2 buttonPosition, float scale)
{
	Image image = LoadImage(imagePath);

	int originalWidth = image.width;
	int originalHeight = image.height;

	int newWidth = int(originalWidth * scale);
	int newHeight = int(originalHeight * scale);

	ImageResize(&image, newWidth, newHeight);

	// Handles Image Width and Heigth offsets relative to the screen coordinates
	buttonPosition.x -= (float)newWidth / 2;
	buttonPosition.y -= (float)newHeight / 2;

	texture = LoadTextureFromImage(image);
	UnloadImage(image);
	position = buttonPosition;
}

Button::~Button()
{
	UnloadTexture(texture);
}

void Button::Init(const char* imagePath, Vector2 buttonPosition, float scale)
{
	Image image = LoadImage(imagePath);

	int originalWidth = image.width;
	int originalHeight = image.height;

	int newWidth = int(originalWidth * scale);
	int newHeight = int(originalHeight * scale);

	ImageResize(&image, newWidth, newHeight);

	// Handles Image Width and Heigth offsets relative to the screen coordinates
	buttonPosition.x -= (float)newWidth / 2;
	buttonPosition.y -= (float)newHeight / 2;

	texture = LoadTextureFromImage(image);
	UnloadImage(image);
	position = buttonPosition;
}

void Button::Draw()
{
	DrawTextureV(texture, position, WHITE);
}

bool Button::isPressed(Vector2 mousePos, bool mousePressed)
{
	Rectangle rect = { position.x, position.y, float(texture.width), float(texture.height) };

	if (CheckCollisionPointRec(mousePos, rect) && mousePressed == true)
	{
		return true;
	}

	return false;
}

Vector2 Button::getPostion()
{
	return position;
}
