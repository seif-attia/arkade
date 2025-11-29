#include <iostream>
#include <raylib.h>
#include "button.h"
// Game Includes
#include "tic-tac-toe\tic_tac_toe.h"
#include "duck-invaders\duck_invaders.h"	
#include "snake\snake.h"
#include "tetris\tetris.h"
#include "game_center.h"



void startGameCenter()
{
	const int screenWidth = 1200;
	const int screenHeight = 800;

	SetWindowSize(screenWidth, screenHeight);

	// Variables
	bool playing = true;

	Button backToStartButton("assets/sprites/white_button.png", { 75 , 50 }, 0.3);
	Button ticTacToeButton("assets/sprites/white_button.png", { screenWidth / 4, screenHeight / 3 }, 0.5);
	Button duckInvadersButton("assets/sprites/white_button.png", { screenWidth / 2, screenHeight / 3 }, 0.5);
	Button snakeButton("assets/sprites/white_button.png", { screenWidth / 2 + screenWidth / 4 , screenHeight / 3 }, 0.5);
	Button tetrisButton("assets/sprites/white_button.png", { screenWidth / 3, 2 * screenHeight / 3 }, 0.5);
	Button game5_button("assets/sprites/white_button.png", { 2 * screenWidth / 3, 2 * screenHeight / 3 }, 0.5);

	// Game Loop
	while (playing)
	{
		if (WindowShouldClose() == true)
		{
			playing = false;
		}

		Vector2 mousePosition = GetMousePosition();
		bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
		// User Input
		if (backToStartButton.isPressed(mousePosition, mousePressed))
		{
			playing = false;
		}
		if (ticTacToeButton.isPressed(mousePosition, mousePressed))
		{
			playTicTacToe();
			SetWindowSize(screenWidth, screenHeight);
		}
		if (duckInvadersButton.isPressed(mousePosition, mousePressed))
		{
			playDuckInvaders();
			SetWindowSize(screenWidth, screenHeight);
		}
		if (snakeButton.isPressed(mousePosition, mousePressed))
		{
			playSnake();
			SetWindowSize(screenWidth, screenHeight);
		}
		if (tetrisButton.isPressed(mousePosition, mousePressed))
		{
			playTetris();
			SetWindowSize(screenWidth, screenHeight);
		}
		if (game5_button.isPressed(mousePosition, mousePressed))
		{
			std::cout << "game 5 button is pressed\n";
		}

		// Drawing On Screen
		BeginDrawing();
		ClearBackground(BLACK);	// Clears every frame

		// Back Button
		backToStartButton.Draw();
		const int backOffset = MeasureText("BACK", 20) / 2;
		const int backX = backToStartButton.getPostion().x + backToStartButton.getWidth() / 2 - backOffset;
		const int backY = backToStartButton.getPostion().y + backToStartButton.getHeight() / 2 - 20 / 2;
		DrawText("BACK", backX, backY, 20, BLACK);


		ticTacToeButton.Draw();
		duckInvadersButton.Draw();
		snakeButton.Draw();
		tetrisButton.Draw();
		game5_button.Draw();


		EndDrawing();
	}
}