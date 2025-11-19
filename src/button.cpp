#include "button.h"
#include <raylib.h>

Button::Button(const char* imagePath, Vector2 imagePosition, float scale)
{
	Image image = LoadImage(imagePath);

	int originalWidth = image.width;
	int originalHeight = image.height;

	int newWidth = int(originalWidth * scale);
	int newHeight = int(originalHeight * scale);

	ImageResize(&image, newWidth, newHeight);

	// Handles Image Width and Heigth offsets relative to the screen coordinates
	imagePosition.x -= (float)newWidth / 2;
	imagePosition.y -= (float)newHeight / 2;

	texture = LoadTextureFromImage(image);
	UnloadImage(image);
	position = imagePosition;
}

Button::~Button()
{
	UnloadTexture(texture);
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
