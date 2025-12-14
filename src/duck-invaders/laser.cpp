#include "laser.hpp"
#include<iostream>

Laser::Laser(Vector2 position, int speed)
{
	this->position = position;
	this->speed = speed;
	active = true;
}
Laser::Laser(Vector2 position, int speed, const char* eggPath)
{
	const float eggScale = 0.08;
	Image image = LoadImage(eggPath);
	ImageResize(&image, int(image.width * eggScale), int(image.height * eggScale));
	eggTexture = LoadTextureFromImage(image);
	UnloadImage(image);

	this->position = position;
	this->speed = speed;
	active = true;
}
Rectangle Laser::getRectEgg()
{
	Rectangle rect;
	rect.x = position.x;
	rect.y = position.y;
	rect.width = eggTexture.width;
	rect.height = eggTexture.height;
	return rect;
}
void Laser::DrawEgg()
{
	if (active)
		DrawTexture(eggTexture, position.x, position.y, WHITE);
}
void Laser::UpdateEgg()
{
	//move on y axis
	position.y += speed;//+ as it move up
	if (active) {
		if (position.y > GetScreenHeight() || position.y < 0)
		{
			active = false;
		}
	}
}
void Laser::Draw()
{
	if (active)
		DrawRectangle(position.x, position.y, 4, 15, { 106, 153, 255, 255 });
}
Rectangle Laser::getRect()
{
	Rectangle rect;
	rect.x = position.x;
	rect.y = position.y;
	rect.width = 4;
	rect.height = 15;
	return rect;
}
void Laser::Update()
{
	//move on y axis
	position.y += speed;//+ as it move up
	if (active) {
		if (position.y > GetScreenHeight() || position.y < 0)
		{
			active = false;
		}
	}
}