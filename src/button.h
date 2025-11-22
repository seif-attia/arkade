#pragma once
#include <raylib.h>

class Button
{
public:
	Button(const char* imagePath, Vector2 imagePosition, float scale);	// Constructor
	~Button();	// Destructor

	void Draw();
	bool isPressed(Vector2 mousePos, bool mousePressed);

	Vector2 getPostion();

private:
	Texture2D texture;
	Vector2 position;
};