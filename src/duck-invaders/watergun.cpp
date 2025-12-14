#include "watergun.hpp"

WaterGun::WaterGun()
{

	const float scale = 0.15;

	Image tempClosedGun = LoadImage("assets/sprites/duckinvaders/water_gun_closed.png");
	ImageResize(&tempClosedGun, int(tempClosedGun.width * scale), int(tempClosedGun.height * scale));
	waterGunClosed = LoadTextureFromImage(tempClosedGun);
	UnloadImage(tempClosedGun);

	Image tempOpenedGun = LoadImage("assets/sprites/duckinvaders/water_gun_opened.png");
	ImageResize(&tempOpenedGun, int(tempOpenedGun.width * scale), int(tempOpenedGun.height * scale));
	waterGunOpened = LoadTextureFromImage(tempOpenedGun);
	UnloadImage(tempOpenedGun);

	shootTimer = 0.0f;
	shootDuration = 0.15f;

	position.x = (GetScreenWidth() - waterGunOpened.width) / 2;
	position.y = GetScreenHeight() - waterGunOpened.height - 100;
	lastFireTime = 0.0;
	laserSound = LoadSound("assets/sounds/duckinvaders/water_sound.mp3");
	SetSoundVolume(laserSound, 0.3);
}
WaterGun::~WaterGun()
{
	UnloadTexture(waterGunClosed);
	UnloadTexture(waterGunOpened);
	UnloadSound(laserSound);
}
void WaterGun::Draw()
{
	if (shootTimer > 0.0f)
	{
		DrawTextureV(waterGunClosed, position, WHITE);
	}
	else
	{
		DrawTextureV(waterGunOpened, position, WHITE);
	}
}
void WaterGun::MoveLeft() {
	position.x -= 10;
	if (position.x < 0)
	{
		position.x = 0;
	}
}
void WaterGun::MoveRight()
{
	position.x += 10;
	if (position.x > GetScreenWidth() - waterGunOpened.width)
	{
		position.x = GetScreenWidth() - waterGunOpened.width;
	}
}
void WaterGun::FireLaser() {
	if (GetTime() - lastFireTime >= 0.35)
	{
		lasers.push_back(Laser({ position.x + waterGunOpened.width / 2 - 2,position.y }, -6));
		lastFireTime = GetTime();
		PlaySound(laserSound);
	}
}
Rectangle WaterGun::getRect() {
	return { position.x,position.y,float(waterGunOpened.width),float(waterGunOpened.height) };
}
void WaterGun::Reset()
{
	position.x = (GetScreenWidth() - waterGunOpened.width) / 2;
	position.y = GetScreenHeight() - waterGunOpened.height - 100;
	lasers.clear();
}