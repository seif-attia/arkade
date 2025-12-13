#include"theduck.hpp"

Texture2D Engduck::duckImages[3] = {};


Engduck::Engduck(int type, Vector2 position)
{
	this->type = type;
	this->position = position;


	// handles duck image scale;
	const float scale = 0.14;
	Image tempImage;

	int newWidth;
	int newHeight;

	if (duckImages[type - 1].id == 0)
	{
		switch (type)
		{
		case 1:
			tempImage = LoadImage("assets/sprites/duckinvaders/yellow_duck.png");
			newWidth = tempImage.width * scale;
			newHeight = tempImage.height * scale;
			ImageResize(&tempImage, newWidth, newHeight);
			duckImages[0] = LoadTextureFromImage(tempImage);
			UnloadImage(tempImage);
			break;
		case 2:
			tempImage = LoadImage("assets/sprites/duckinvaders/beige_duck.png");
			newWidth = tempImage.width * scale;
			newHeight = tempImage.height * scale;
			ImageResize(&tempImage, newWidth, newHeight);
			duckImages[1] = LoadTextureFromImage(tempImage);
			UnloadImage(tempImage);
			break;
		case 3:
			tempImage = LoadImage("assets/sprites/duckinvaders/pink_duck.png");
			newWidth = tempImage.width * scale;
			newHeight = tempImage.height * scale;
			ImageResize(&tempImage, newWidth, newHeight);
			duckImages[2] = LoadTextureFromImage(tempImage);
			UnloadImage(tempImage);
			break;
		default:
			tempImage = LoadImage("assets/sprites/duckinvaders/yellow_duck.png");
			newWidth = tempImage.width * scale;
			newHeight = tempImage.height * scale;
			ImageResize(&tempImage, newWidth, newHeight);
			duckImages[0] = LoadTextureFromImage(tempImage);
			UnloadImage(tempImage);
			break;
		}
	}

}
void Engduck::Draw() {
	DrawTextureV(duckImages[type - 1], position, WHITE);
}
int Engduck::GetType() {
	return type;
}
Rectangle Engduck::getRect() {
	return{ position.x,position.y,float(duckImages[type - 1].width),
	float(duckImages[type - 1].height) };
}
void Engduck::Update(int direction) {
	position.x += direction;
}