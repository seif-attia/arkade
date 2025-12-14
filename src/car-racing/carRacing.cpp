#include <raylib.h>
#include <vector>
#include <algorithm>
#include "..\playAgainMenu.h"
#include "..\button.h"
#include "carRacing.h"
#include <fstream>
using namespace std;

extern Sound buttonPressSound;
extern Font font;


//================ CAR ====================
class Car {
public:
	Rectangle rect;
	float speed;
	Texture2D carTex;

	void init(Texture2D tex) {
		rect = { 550, 550, 75, 150 };
		speed = 600;
		carTex = tex;
	}

	void draw() {
		DrawTextureV(carTex, { rect.x, rect.y }, WHITE);
	}
};

//================ ENEMY ==================
class Enemy {
public:
	Rectangle rect;
	float speed;
	Texture2D enemyTex;

	Enemy(int roadX1, int roadX2, Texture2D tex, float spd) {
		rect.width = 75;
		rect.height = 150;
		rect.x = GetRandomValue(roadX1, roadX2 - rect.width);
		rect.y = -rect.height;
		speed = spd;
		enemyTex = tex;
	}


	void update(float dt) { rect.y += speed * dt; }
	void draw() { DrawTextureV(enemyTex, { rect.x, rect.y }, WHITE); }
};

//================ ENEMY MANAGER ==========
class EnemyManager {
public:
	vector<Enemy> enemies;
	float spawnTimer = 0.0f;
	float spawnInterval = 1.0f;
	float baseSpeed = 300.0f;
	Texture2D enemyTex;

	void init(Texture2D tex) { enemyTex = tex; }

	void update(float dt, int roadX1, int roadX2, int score) {
		// Difficulty scaling
		spawnInterval = 1.0f - score * 0.025f;
		if (spawnInterval < 0.4f) spawnInterval = 0.4f;

		baseSpeed = 300.0f + score * 5.0f;

		spawnTimer += dt;
		if (spawnTimer >= spawnInterval) {
			spawnTimer = 0.0f;
			enemies.emplace_back(roadX1, roadX2, enemyTex, baseSpeed);
		}

		for (auto& e : enemies)
			e.update(dt);
	}


	void removeOffscreen(int screenHeight, int& score) {
		enemies.erase(remove_if(enemies.begin(), enemies.end(),
			[&](Enemy& e) { if (e.rect.y > screenHeight) { score++; return true; } return false; }),
			enemies.end());
	}

	void draw() { for (auto& e : enemies) e.draw(); }
	void reset() { enemies.clear(); spawnTimer = 0.0f; }
};

//================ BUTTON ==================
class CarRacingButton {
public:
	Rectangle rect;
	Texture2D texture;
	float scale = 1.0f;
	float targetScale = 1.0f;
	float scaleSpeed = 6.0f;

	void init(const char* path, Vector2 centerPos, float s = 1.0f) {
		Image img = LoadImage(path);
		ImageResize(&img, img.width * s, img.height * s);
		texture = LoadTextureFromImage(img);
		UnloadImage(img);

		rect.width = texture.width;
		rect.height = texture.height;
		rect.x = centerPos.x - rect.width / 2;
		rect.y = centerPos.y - rect.height / 2;
	}

	Rectangle getScaledRect() {
		float w = rect.width * scale;
		float h = rect.height * scale;
		return {
			rect.x + rect.width / 2 - w / 2,
			rect.y + rect.height / 2 - h / 2,
			w, h
		};
	}

	void update(Vector2 mousePos, float dt) {
		Rectangle scaled = getScaledRect();
		targetScale = CheckCollisionPointRec(mousePos, scaled) ? 1.1f : 1.0f;
		scale += (targetScale - scale) * scaleSpeed * dt;
	}

	void draw() {
		Rectangle r = getScaledRect();
		DrawTexturePro(
			texture,
			{ 0,0,(float)texture.width,(float)texture.height },
			r,
			{ 0,0 },
			0,
			WHITE
		);
	}

	bool isPressed(Vector2 mousePos, bool pressed) {
		return pressed && CheckCollisionPointRec(mousePos, getScaledRect());
	}

	~CarRacingButton() {
		UnloadTexture(texture);
	}
};


//================ GAME ===================
class Game {
public:
	const int screenW = 1200;
	const int screenH = 800;
	const int roadX1 = 200;
	const int roadX2 = 980;

	enum Theme { DAY, NIGHT };
	Theme currentTheme = DAY;

	float themeTimer = 0.0f;
	const float THEME_SWITCH_TIME = 100.0f;

	enum ControlType { NONE, ARROWS, MOUSE };
	ControlType playerControl = NONE;

	bool gameStarted = false;
	bool gameOver = false;

	int score = 0;
	int highScore = 0;

	float dt;
	float headlightRadius = 180.0f;


	Vector2 mousePos;
	bool mousePressed;

	Texture2D roadDayTex, roadNightTex, carTex, enemyTex, scoreTex, highScoreTex, gameover, readyGo;
	Sound crashSound;
	Music backMusic;

	Car car;
	EnemyManager enemyManager;
	CarRacingButton arrowsBtn, mouseBtn;

	void init() {

		highScoreTex = LoadTexture("assets/sprites/carRacing/high.png");
		scoreTex = LoadTexture("assets/sprites/carRacing/scorebutton (2).png");

		roadDayTex = LoadTexture("assets/sprites/carRacing/final bg.png");
		roadNightTex = LoadTexture("assets/sprites/carRacing/background night.png");

		carTex = LoadTexture("assets/sprites/carRacing/finalcar.png");
		enemyTex = LoadTexture("assets/sprites/carRacing/final enemy.png");

		gameover = LoadTexture("assets/sprites/carRacing/game over.png");
		readyGo = LoadTexture("assets/sprites/carRacing/READY GO.png");

		crashSound = LoadSound("assets/sounds/carRacing/crash.mp3");
		backMusic = LoadMusicStream("assets/sounds/carRacing/bg3.mp3");

		PlayMusicStream(backMusic);
		SetMusicVolume(backMusic, 0.4f); // 0.0 → 1.0


		car.init(carTex);
		enemyManager.init(enemyTex);

		arrowsBtn.init("assets/sprites/carRacing/KEYSBUTTON.png", { 400, 400 });
		mouseBtn.init("assets/sprites/carRacing/WHEELBUTTON.png", { 800, 400 });

		{
			ifstream fin("data/highscore_carRacing.txt");
			if (fin.is_open())
			{
				if (!(fin >> highScore))
				{
					highScore = 0;
				}
				fin.close();
			}
		}

	}

	void update(float dt) {
		this->dt = dt;
		mousePos = GetMousePosition();
		mousePressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
		UpdateMusicStream(backMusic);

		// Update buttons
		arrowsBtn.update(mousePos, dt);
		mouseBtn.update(mousePos, dt);

		themeTimer += dt;

		if (gameStarted && !gameOver) {
			themeTimer += dt;

			if (themeTimer >= THEME_SWITCH_TIME) {
				themeTimer = 0.0f;
				currentTheme = (currentTheme == DAY) ? NIGHT : DAY;
			}
		}



		if (!gameStarted) {
			if (arrowsBtn.isPressed(mousePos, mousePressed)) { playerControl = ARROWS; gameStarted = true; }
			else if (mouseBtn.isPressed(mousePos, mousePressed)) { playerControl = MOUSE; gameStarted = true; }
			return; // wait until player chooses
		}

		if (gameOver)
			PauseMusicStream(backMusic);

		if (!gameOver) {
			// Car movement
			if (playerControl == ARROWS) {
				if (IsKeyDown(KEY_RIGHT)) car.rect.x += car.speed * dt;
				if (IsKeyDown(KEY_LEFT)) car.rect.x -= car.speed * dt;
			}
			else if (playerControl == MOUSE) {
				float lerpSpeed = 10.0f;
				car.rect.x += (mousePos.x - car.rect.width / 2 - car.rect.x) * lerpSpeed * dt;
			}

			if (car.rect.x < roadX1) car.rect.x = roadX1;
			if (car.rect.x + car.rect.width > roadX2) car.rect.x = roadX2 - car.rect.width;

			enemyManager.update(dt, roadX1, roadX2, score);
			enemyManager.removeOffscreen(screenH, score);

			// Collision
			for (auto& e : enemyManager.enemies)
				if (CheckCollisionRecs(car.rect, e.rect)) {
					PlaySound(crashSound);
					gameOver = true;

					if (score > highScore)
					{
						highScore = score;

						ofstream fout("data/highscore_carRacing.txt", ios::out | ios::trunc);
						if (fout.is_open())
						{
							fout << highScore;
							fout.close();
						}
					}

					break;

				}
		}
		else {
			if (IsKeyPressed(KEY_R)) restart();
		}
	}

	void draw() {


		Texture2D currentRoad =
			(currentTheme == NIGHT) ? roadNightTex : roadDayTex;
		DrawTextureV(currentRoad, { 0, 0 }, WHITE);

		// DrawTextureV(roadDayTex, {0.0f,0.0f}, WHITE);
		car.draw();
		enemyManager.draw();


		if (currentTheme == NIGHT && gameStarted && !gameOver) {
			Vector2 lightPos = {
				car.rect.x + car.rect.width / 2,
				car.rect.y
			};

			DrawCircleGradient(
				lightPos.x,
				lightPos.y,
				220,
				Color{ 255, 255, 200, 120 },
				Color{ 0, 0, 0, 0 }
			);
		}


		if (!gameStarted) {
			arrowsBtn.draw();
			mouseBtn.draw();
			DrawTexture(readyGo, 450.0f, 180.0f, WHITE);
		}

		// score ...
		Color DARKORANGE = { 237,63,39,255 };
		DrawTexture(scoreTex, 6.0f, 675.0f, WHITE);
		DrawTextEx(font, TextFormat("%i", score), { 105 - MeasureTextEx(font,TextFormat("%i", score),30,0).x, 730.0f }, 30, 0, DARKORANGE);

		// Highscore ...
		DrawTexture(highScoreTex, 1020.0f, 10.0f, WHITE);
		DrawTextEx(font, TextFormat("%i", highScore), { 1100.0f, 35.0f }, 30, 2, ORANGE);

		if (gameOver) {
			DrawTexture(gameover, 450.0f, 180.0f, WHITE);
			DrawTextEx(font, "Press R to Restart", { 420, 350 }, 40, 3, WHITE);
		}

		if (currentTheme == NIGHT) {
			DrawRectangle(0, 0, screenW, screenH, Color{ 10, 20, 40, 120 });
		}

	}

	void restart() {
		themeTimer = 0.0f;
		currentTheme = DAY;
		ResumeMusicStream(backMusic);
		enemyManager.reset();
		score = 0;
		gameOver = false;
		gameStarted = false;
		car.rect.x = 550;
		playerControl = NONE;
	}

	void run() {

		update(GetFrameTime());
		draw();
	}

	~Game() {
		UnloadTexture(roadDayTex);
		UnloadTexture(roadNightTex);
		UnloadTexture(carTex);
		UnloadTexture(enemyTex);
		UnloadSound(crashSound);
		UnloadMusicStream(backMusic);
	}
};


void playCarRacing()
{
	const int screenWidth = 1200;
	const int screenHeight = 800;

	bool playing = true;
	bool showMenu = false;

	Game game;
	game.init();

	// Button Inits
	Button menuButton("assets/sprites/setting.png", { 40, 40 }, 0.9);
	Menu menu("assets/sprites/menu.png", { (float)screenWidth / 2, float(screenHeight) / 2 }, 1);

	while (playing == true)
	{

		Vector2 mousePosition = GetMousePosition();
		bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

		if (WindowShouldClose() == true)
		{
			playing = false;

		}

		BeginDrawing();

		game.run();

		// Menu buttons input code
		if (showMenu == true)
		{

			if (menu.quitButton.isPressed(mousePosition, mousePressed))
			{
				PlaySound(buttonPressSound);
				playing = false;
			}
			if (menu.playAgainButton.isPressed(mousePosition, mousePressed))
			{
				PlaySound(buttonPressSound);
				game.restart();
				showMenu = false;

			}

			if (menu.closeMenuButton.isPressed(mousePosition, mousePressed))
			{
				PlaySound(buttonPressSound);
				showMenu = false;
			}

			menu.Draw();
		}
		// quit button
		menuButton.Draw();

		// menu button
		if (menuButton.isPressed(mousePosition, mousePressed))
		{
			PlaySound(buttonPressSound);
			showMenu = !showMenu;
		}


		EndDrawing();
	}

	{
		ofstream fout("data/highscore_carRacing.txt", ios::out | ios::trunc);
		if (fout.is_open())
		{

			fout << game.highScore;
			fout.close();
		}
	}

}