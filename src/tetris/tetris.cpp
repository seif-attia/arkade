#include <raylib.h>
#include "tetris.h"
#include "..\button.h"
#include "..\playAgainMenu.h"
#include "game.h"
#include "colors.h"
#include <cstdio>
#include <fstream>
#include <iostream>
using namespace std;


double lastUpdateTimeTetris = 0;
extern Sound buttonPressSound;

bool EventTriggered(double interval)
{
	double currentTime = GetTime();
	if (currentTime - lastUpdateTimeTetris >= interval)
	{
		lastUpdateTimeTetris = currentTime;
		return true;
	}
	return false;
}

void playTetris()
{
	// Window Sizing
	const int screenWidth = 1200;
	const int screenHeight = 800;

	Font font = LoadFontEx("assets/fonts/tetris.ttf", 64, 0, 0);

	// Flags
	bool playing = true;
	bool showMenu = false;

	GameTetris game = GameTetris();

	// Button Inits
	Button menuButton("assets/sprites/setting.png", { 40, 40 }, 0.9);
	Menu menu("assets/sprites/menu.png", { (float)screenWidth / 2, float(screenHeight) / 2 }, 1);

	// Handles all the sprites
	Image Tetris = LoadImage("assets/sprites/tetris/Tetris.png");
	Image Arkade = LoadImage("assets/sprites/tetris/Arkade.png");
	Image Album = LoadImage("assets/sprites/tetris/Album.png");

	ImageResize(&Tetris, int(Tetris.width * 0.08), int(Tetris.height * 0.08));
	ImageResize(&Arkade, int(Arkade.width * 0.015), int(Arkade.height * 0.015));
	ImageResize(&Album, int(Album.width * 0.3), int(Album.height * 0.3));

	Texture2D tetris = LoadTextureFromImage(Tetris);
	Texture2D arkade = LoadTextureFromImage(Arkade);
	Texture2D album = LoadTextureFromImage(Album);

	UnloadImage(Tetris);
	UnloadImage(Arkade);
	UnloadImage(Album);

	int previousscore = 0;
	int highscore = 0;

	// Read existing highscore (do not open an ofstream that truncates the file here)
	{
		ifstream fin("data/highscore_tetris.txt");
		if (fin.is_open())
		{
			if (!(fin >> highscore))
			{
				highscore = 0;
			}
			fin.close();
		}
	}

	while (playing)
	{
		// Mouse position		
		Vector2 mousePosition = GetMousePosition();
		bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

		// Music
		UpdateMusicStream(game.music);

		// input
		game.HandleInput();
		if (EventTriggered(0.2))
		{
			game.MoveBlockDown();
		}


		if (WindowShouldClose() == true)
		{
			playing = false;
		}

		BeginDrawing();
		ClearBackground(darkBlue);

		// Game drawing
		DrawTexture(tetris, 885, 180, WHITE);
		DrawTexture(arkade, 885, 10, WHITE);
		DrawTexture(album, 40, 420, WHITE);
		DrawTextEx(font, "Score:", { 907, 240 }, 60, 2, WHITE);
		DrawTextEx(font, "High score:", { 97, 100 }, 40, 2, WHITE);
		DrawTextEx(font, "Previous score:", { 55, 227 }, 40, 2, WHITE);
		DrawTextEx(font, "Next:", { 925, 372 }, 60, 2, WHITE);
		DrawTextEx(font, "Hold On Tight - aespa", { 35, 755 }, 30, 2, WHITE);

		if (game.gameOver)
		{
			DrawTextEx(font, "GAME", { 895, 630 }, 100, 2, WHITE);
			DrawTextEx(font, "OVER", { 895, 700 }, 100, 2, WHITE);
			previousscore = game.score;
			if (game.score > highscore)
			{
				highscore = game.score;
				// Write the new highscore immediately
				ofstream fout("data/highscore_tetris.txt", ios::out | ios::trunc);
				if (fout.is_open())
				{
					fout << highscore;
					fout.close();
				}
			}

		}
		DrawRectangleRounded({ 875, 305, 230, 70 }, 0.3, 6, lightBlue);
		DrawRectangleRounded({ 90, 150, 230, 70 }, 0.3, 6, lightBlue);
		DrawRectangleRounded({ 90, 280, 230, 70 }, 0.3, 6, lightBlue);

		char scoreText[10];
		sprintf(scoreText, "%d", game.score);
		Vector2 textSize = MeasureTextEx(font, scoreText, 60, 2);

		char highscoreText[10];
		sprintf(highscoreText, "%d", highscore);
		Vector2 hstextSize = MeasureTextEx(font, highscoreText, 60, 2);

		char previousscoreText[10];
		sprintf(previousscoreText, "%d", previousscore);
		Vector2 pstextSize = MeasureTextEx(font, previousscoreText, 60, 2);

		DrawTextEx(font, scoreText, { 877 + (230 - textSize.x) / 2, 308 }, 60, 2, WHITE);
		DrawTextEx(font, highscoreText, { 90 + (230 - hstextSize.x) / 2, 152 }, 60, 2, WHITE);
		DrawTextEx(font, previousscoreText, { 90 + (230 - pstextSize.x) / 2, 282 }, 60, 2, WHITE);
		DrawRectangleRounded({ 875, 435, 230, 200 }, 0.3, 6, lightBlue);
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
				game.Reset();
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
		ofstream fout("data/highscore_tetris.txt", ios::out | ios::trunc);
		if (fout.is_open())
		{
			fout << highscore;
			fout.close();
		}
	}

	UnloadTexture(tetris);
	UnloadTexture(arkade);
	UnloadTexture(album);
	UnloadFont(font);
}