#include <raylib.h>
#include <raymath.h>
#include <deque>
#include "snake.h"
#include "../button.h"
#include "../playAgainMenu.h"
#include <fstream>
#include <string>
using namespace std;


extern Sound buttonPressSound;

Color green = { 152, 251, 152, 255 };
Color darkgreen = { 43, 51, 24, 255 };

int cellSize = 25;
int cellCountX = 38;
int cellCountY = 25;
int  offsetX = 135;
int  offsetY = 80;

double lastUpdateTimeSnake = 0;

bool ElementInDeque(Vector2 element, deque<Vector2> deque)
{
	for (unsigned int i = 0; i < deque.size(); i++)
	{
		if (Vector2Equals(deque[i], element))
		{
			return true;
		}
	}
	return false;
}

bool eventTriggered(double interval)
{
	double currentTime = GetTime();
	if (currentTime - lastUpdateTimeSnake >= interval)
	{
		lastUpdateTimeSnake = currentTime;
		return true;
	}
	return false;
}

class snake
{
public:
	deque <Vector2> body = { Vector2{6,9},Vector2{5,9},Vector2{4,9} };
	Vector2 direction = { 1,0 };
	bool addSegment = false;

	void Draw()
	{
		for (unsigned int i = 0; i < body.size(); i++)
		{
			float x = body[i].x;
			float y = body[i].y;
			Rectangle segment = Rectangle{ offsetX + x * cellSize, offsetY + y * cellSize,(float)cellSize,(float)cellSize };
			DrawRectangleRounded(segment, 0.5, 6, darkgreen);
		}
	}
	void update()
	{
		body.push_front(Vector2Add(body[0], direction));
		if (addSegment == true)
		{
			addSegment = false;

		}
		else
		{
			body.pop_back();

		}

	}
	void Reset()
	{
		body = { Vector2{6,9},Vector2{5,9},Vector2{4,9} };
		direction = { 1,0 };
	}

};

class Food {
public:
	Vector2 position;
	Texture2D texture{};

	Food(deque<Vector2> snakebody) {
		// Load AFTER InitWindow()
		Image image = LoadImage("assets/sprites/snake/apple.png");   // Use relative path or escaped full path
		texture = LoadTextureFromImage(image);
		UnloadImage(image);
		position = GenerateRandomPos(snakebody);
	}

	~Food() {
		UnloadTexture(texture);
	}

	void Draw() const {
		// DrawTexture(texture,offset + position.x * cellSize,offset + position.y * cellSize, WHITE);

		float scale = 0.9f;  // fraction of the cell size
		float targetSize = cellSize * scale;

		float drawX = offsetX + position.x * cellSize + (cellSize - targetSize) / 2;
		float drawY = offsetY + position.y * cellSize + (cellSize - targetSize) / 2;

		DrawTextureEx(
			texture,
			Vector2{ drawX, drawY },
			0.0f,
			targetSize / texture.width, // scales any uploaded image
			WHITE
		);


	}
	Vector2 GenerateRandomCell()
	{
		int x = GetRandomValue(0, cellCountX - 1);
		int y = GetRandomValue(0, cellCountY - 1);
		return Vector2{ (float)x,(float)y };
	}


	Vector2 GenerateRandomPos(deque<Vector2>snakeBody)
	{
		Vector2 position = GenerateRandomCell();
		while (ElementInDeque(position, snakeBody))
		{
			position = GenerateRandomCell();
		}
		return position;
	}
};

class GameSnake {
public:
	snake snakee = snake();
	Food meal = Food(snakee.body);
	bool running = true;
	int score = 0;
	void Draw()
	{
		meal.Draw();
		snakee.Draw();
	}
	void update()
	{
		if (running) {
			snakee.update();
			CheckCollisionWithFood();
			checkCollisionWithEdges();
			CheckCollisionWithTail();
		}
	}

	~GameSnake()
	{
		UnloadSound(eatApple);
		UnloadSound(collision);
	}

	void CheckCollisionWithFood()
	{
		if (Vector2Equals(snakee.body[0], meal.position))
		{
			PlaySound(eatApple);
			meal.position = meal.GenerateRandomPos(snakee.body);
			snakee.addSegment = true;
			score++;
		}
	}
	// check if it hits the edge or the tail or not
	void checkCollisionWithEdges()
	{
		if (snakee.body[0].x == cellCountX || snakee.body[0].x == -1)
		{
			PlaySound(collision);
			running = false;
		}
		if (snakee.body[0].y == cellCountY || snakee.body[0].y == -1)
		{
			PlaySound(collision);
			running = false;
		}
	}
	void GameOver()
	{
		running = true;
		snakee.Reset();
		meal.position = meal.GenerateRandomPos(snakee.body);
		score = 0;

	}
	void CheckCollisionWithTail()
	{
		deque<Vector2> headlessBody = snakee.body;
		headlessBody.pop_front();
		if (ElementInDeque(snakee.body[0], headlessBody))
		{
			PlaySound(collision);
			running = false;
		}
	}

private:
	// Sounds
	Sound eatApple = LoadSound("assets/sounds/snake/eat.mp3");
	Sound collision = LoadSound("assets/sounds/snake/wall.mp3");
};


void playSnake()
{

	const int screenWidth = 1200;
	const int screenHeight = 800;

	SetWindowSize(screenWidth, screenHeight);

	bool playing = true;
	bool showMenu = false;



	// Menu button
	Button menuButton("assets/sprites/setting.png", { 40, 40 }, 0.9);
	Menu menu("assets/sprites/menu.png", { (float)screenWidth / 2, float(screenHeight) / 2 }, 1);

	GameSnake game = GameSnake();

	Music music = LoadMusicStream("assets/sounds/snake/snake_music.ogg");
	PlayMusicStream(music);

	Texture2D background = LoadTexture("assets/sprites/snake/background.png");
	Rectangle srcRecBackground = { 0,0, background.width,background.height };
	Rectangle disRecBackground = { 0,0, 1200,800 };

	int highscore = 0;

	// Read the highscore 
	{
		ifstream fin("data/highscore_snake.txt");
		if (fin.is_open())
		{
			if (!(fin >> highscore))
			{
				highscore = 0;
			}
			fin.close();
		}
	}


	while (playing == true)
	{
		UpdateMusicStream(music);

		// Init Variables
		Vector2 mousePosition = GetMousePosition();
		bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);


		if (WindowShouldClose() == true)
		{
			playing = false;
		}

		// Drawing
		BeginDrawing();

		// Game Code

		if (eventTriggered(0.2))
		{
			game.update();
		}

		if (IsKeyPressed(KEY_UP) && game.snakee.direction.y != 1)
		{
			game.snakee.direction = { 0,-1 };
		}

		if (IsKeyPressed(KEY_DOWN) && game.snakee.direction.y != -1)
		{
			game.snakee.direction = { 0,1 };
		}

		if (IsKeyPressed(KEY_LEFT) && game.snakee.direction.x != 1)
		{
			game.snakee.direction = { -1,0 };
		}

		if (IsKeyPressed(KEY_RIGHT) && game.snakee.direction.x != -1)
		{
			game.snakee.direction = { 1,0 };

		}


		ClearBackground(green);

		DrawTexturePro(background, srcRecBackground, disRecBackground, { 0,0 }, 0, WHITE);



		DrawRectangleLinesEx(Rectangle{ (float)offsetX - 5,(float)offsetY - 5,(float)cellSize * cellCountX + 10,(float)cellSize * cellCountY + 10 }, 5, darkgreen);
		DrawText("Retro Snake", offsetX - 5, 20, 40, WHITE);
		DrawText(TextFormat("%i", game.score), offsetX, offsetY + cellSize * cellCountY + 20, 40, WHITE);
		std::string highscoreText = "Highscore: " + to_string(highscore);
		DrawText(highscoreText.c_str(), offsetX + cellSize * cellCountX - MeasureText(highscoreText.c_str(), 40), offsetY + cellSize * cellCountY + 20, 40, WHITE);

		if (!game.running)
		{
			// handle highscore
			if (game.score > highscore)
			{
				highscore = game.score;
				// Write the new highscore immediately
				ofstream fout("data/highscore_snake.txt", ios::out | ios::trunc);
				if (fout.is_open())
				{
					fout << highscore;
					fout.close();
				}
			}


			int fontSize1 = 50;
			int fontSize2 = 30;

			// center of the board
			int centerX = offsetX + (cellSize * cellCountX) / 2;
			int centerY = offsetY + (cellSize * cellCountY) / 2;

			// measure text widths
			int textWidth1 = MeasureText("GAME OVER", fontSize1);
			int textWidth2 = MeasureText("Press any key to Restart", fontSize2);

			// draw centered
			DrawText("GAME OVER", centerX - textWidth1 / 2, centerY - 60, fontSize1, RED);
			DrawText("Press any key to Restart", centerX - textWidth2 / 2, centerY + 10, fontSize2, BLACK);

			int key = GetKeyPressed();
			if (key > 0)
			{
				game.GameOver();
			}
		}


		game.Draw();



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
				game.GameOver();
				game.running = true;
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

	// Ensure highscore is saved on exit as well
	{
		ofstream fout("data/highscore_snake.txt", ios::out | ios::trunc);
		if (fout.is_open())
		{
			fout << highscore;
			fout.close();
		}
	}

	UnloadMusicStream(music);
	UnloadTexture(background);
}
