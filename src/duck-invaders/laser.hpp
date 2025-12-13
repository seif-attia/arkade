#pragma once

#include <raylib.h>
class Laser {
public:
	Laser(Vector2 position, int speed, const char* eggPath);
	Laser(Vector2 position, int speed);
	Rectangle getRectEgg();
	void DrawEgg();
	void UpdateEgg();
	void Update();
	void Draw();
	Rectangle getRect();
	bool active;
private:
	Vector2 position;
	Texture2D eggTexture;
	int speed;
};