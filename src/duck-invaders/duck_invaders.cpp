#include <raylib.h>
#include "../button.h"
#include "duck_invaders.h"
#include "..\playAgainMenu.h"	
#include <string>
#include "gameDuck.hpp"
#include "theduck.hpp"


extern Sound buttonPressSound;
extern Font font;


void playDuckInvaders() // main
{

	const int screenWidth = 1200;
	const int screenHeight = 800;

	SetWindowSize(screenWidth, screenHeight);

	bool playing = true;
	bool showMenu = false;

	Color pink = { 213,0,149,100 };

	Texture2D livesImage = LoadTexture("assets/sprites/duckinvaders/pink_bow_lives.png");
	GameDuckInvaders game;
	Engduck engduck = Engduck(1, { 100,1000 });

	Texture2D background = LoadTexture("assets/sprites/duckinvaders/background.png");

	// Menu button
	//Button menuButton("assets/sprites/setting.png", { 30, 30 }, 0.72);
	Button menuButton("assets/sprites/setting.png", { 1160, 690 }, 0.72);
	Menu menu("assets/sprites/menu.png", { (float)screenWidth / 2, float(screenHeight) / 2 }, 1);



	// Game Loop
	while (playing)
	{
		UpdateMusicStream(game.music);
		game.HandleInput();
		game.Update();

		// Initilization of variables
		Vector2 mousePosition = GetMousePosition();
		bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

		if (WindowShouldClose() == true)
		{
			playing = false;
		}

		// Drawing
		BeginDrawing();
		ClearBackground(BLACK);

		DrawTexture(background, 0, 0, WHITE);
		DrawRectangleRoundedLinesEx({ 10,10,1180,780 }, 0.18f, 20, 3, pink); //gdeda
		DrawLineEx({ 15,730 }, { 1180,730 }, 3, pink); //gdeda

		if (game.run)
		{
			std::string levelCount = "LEVEL " + std::to_string(game.level);
			DrawTextEx(font, levelCount.c_str(), { 980,745 }, 34, 2, pink);
		}
		else
		{
			DrawTextEx(font, "PRESS ENTER TO RESTART", { 930 - 230,680 }, 34, 2, pink);
			DrawTextEx(font, "GAME OVER", { 960,745 }, 34, 2, pink);
		}

		float x = 75.0;
		for (int i = 0; i < game.lives; i++)
		{
			DrawTextureV(livesImage, { x,745 }, WHITE);
			x += 75.0;
		}

		DrawTextEx(font, "SCORE", { 30,690 }, 34, 2, pink); //msh shayfaha
		std::string scoreText = std::to_string(game.score);
		DrawTextEx(font, scoreText.c_str(), { 30 + 120,690 }, 34, 3, pink);
		DrawTextEx(font, "HIGH-SCORE", { 600 - 150,745 }, 34, 2, pink);
		std::string highscoreText = std::to_string(game.highscore);
		DrawTextEx(font, highscoreText.c_str(), { 600 - 150 + 220,745 }, 34, 3, pink);
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
				game.InitGame();
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

	UnloadTexture(background);
}