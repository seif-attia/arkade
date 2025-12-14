#pragma once
#include <raylib.h> 
#include"laser.hpp"
#include<vector>
class WaterGun
{
public:
	WaterGun();
	~WaterGun();
	void Draw();
	void MoveLeft();
	void MoveRight();
	void FireLaser();
	Rectangle getRect();
	void Reset();
	std::vector<Laser>lasers;

	double shootTimer;
	double shootDuration;
private:
	Texture2D waterGunClosed;
	Texture2D waterGunOpened;
	Vector2 position;
	double lastFireTime;
	Sound laserSound;
};
