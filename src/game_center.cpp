#include <iostream>
#include <raylib.h>
#include "button.h"
// Game Includes
#include "tic-tac-toe\tic_tac_toe.h"
#include "duck-invaders\duck_invaders.h"	
#include "snake\snake.h"
#include "tetris\tetris.h"
#include "game_center.h"
#include "car-racing\carRacing.h"


extern Sound buttonPressSound;
extern Music opening_music;

void startGameCenter()
{
	const int screenWidth = 1200;
	const int screenHeight = 800;

	SetWindowSize(screenWidth, screenHeight);

	// Variables
	bool playing = true;

	// background 
	Texture2D background = LoadTexture("assets/sprites/gamecenter_background.png");


	Button backToStartButton("assets/sprites/home.png", { 50 , 50 }, 0.9);
	Button ticTacToeButton("assets/sprites/Tictactoe_button.png", { screenWidth / 4, 2 * screenHeight / 5 }, 0.4);
	Button duckInvadersButton("assets/sprites/Duck_invaders_button.png", { screenWidth / 2, 2 * screenHeight / 5 }, 0.4);
	Button snakeButton("assets/sprites/Retro_snake_button.png", { screenWidth / 2 + screenWidth / 4 , 2 * screenHeight / 5 }, 0.4);
	Button tetrisButton("assets/sprites/Tetris_button.png", { screenWidth / 3, 3 * screenHeight / 5 }, 0.4);
	Button game5_button("assets/sprites/car_button.png", { 2 * screenWidth / 3, 3 * screenHeight / 5 }, 0.47);

	// Game Loop
	while (playing)
	{
		UpdateMusicStream(opening_music);
		if (WindowShouldClose() == true)
		{
			playing = false;
		}

		Vector2 mousePosition = GetMousePosition();
		bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
		// User Input
		if (backToStartButton.isPressed(mousePosition, mousePressed))
		{
			PlaySound(buttonPressSound);
			playing = false;
		}
		if (ticTacToeButton.isPressed(mousePosition, mousePressed))
		{
			PlaySound(buttonPressSound);
			playTicTacToe();
			SetWindowSize(screenWidth, screenHeight);
		}
		if (duckInvadersButton.isPressed(mousePosition, mousePressed))
		{
			PlaySound(buttonPressSound);
			playDuckInvaders();
			SetWindowSize(screenWidth, screenHeight);
		}
		if (snakeButton.isPressed(mousePosition, mousePressed))
		{
			PlaySound(buttonPressSound);
			playSnake();
			SetWindowSize(screenWidth, screenHeight);
		}
		if (tetrisButton.isPressed(mousePosition, mousePressed))
		{
			PlaySound(buttonPressSound);
			playTetris();
			SetWindowSize(screenWidth, screenHeight);
		}
		if (game5_button.isPressed(mousePosition, mousePressed))
		{
			PlaySound(buttonPressSound);
			playCarRacing();
			SetWindowSize(screenWidth, screenHeight);
		}

		// Drawing On Screen
		BeginDrawing();
		ClearBackground(BLACK);	// Clears every frame

		DrawTexture(background, 0, 0, WHITE);

		// Back Button
		backToStartButton.Draw();
		/*const int backOffset = MeasureText("BACK", 20) / 2;
		const int backX = backToStartButton.getPostion().x + backToStartButton.getWidth() / 2 - backOffset;
		const int backY = backToStartButton.getPostion().y + backToStartButton.getHeight() / 2 - 20 / 2;
		DrawText("BACK", backX, backY, 20, BLACK);*/


		ticTacToeButton.Draw();
		duckInvadersButton.Draw();
		snakeButton.Draw();
		tetrisButton.Draw();
		game5_button.Draw();


		EndDrawing();
	}

	UnloadTexture(background);

}