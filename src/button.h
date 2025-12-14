#pragma once
#include <raylib.h>

class Button
{
public:
	Button();
	Button(const char* imagePath, Vector2 buttonPosition, float scale);	// Constructor
	~Button();	// Destructor


	float getWidth();
	float getHeight();

	void Init(const char* imagePath, Vector2 buttonPosition, float scale);

	void Draw();
	bool isPressed(Vector2 mousePos, bool mousePressed);

	Vector2 getPostion();

private:
	Texture2D texture;
	Vector2 position;
};