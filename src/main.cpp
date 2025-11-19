#include <iostream>
#include <raylib.h>
#include "button.h"


int main()
{
	const int screenWidth = 1200;
	const int screenHeight = 800;

	InitWindow(screenWidth, screenHeight, "placeholder");
	SetTargetFPS(60);

	// Variables

	Button game1_button("assets/sprites/white_button.png", { screenWidth / 4, screenHeight / 3 }, 0.5);
	Button game2_button("assets/sprites/white_button.png", { screenWidth / 2, screenHeight / 3 }, 0.5);
	Button game3_button("assets/sprites/white_button.png", { screenWidth / 2 + screenWidth / 4 , screenHeight / 3 }, 0.5);
	Button game4_button("assets/sprites/white_button.png", { screenWidth / 3, 2 * screenHeight / 3 }, 0.5);
	Button game5_button("assets/sprites/white_button.png", { 2 * screenWidth / 3, 2 * screenHeight / 3 }, 0.5);

	// Game Loop
	while (WindowShouldClose() == false)
	{
		Vector2 mousePosition = GetMousePosition();
		bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
		// User Input

		if (game1_button.isPressed(mousePosition, mousePressed))
		{
			std::cout << "game 1 button is pressed\n";
		}
		if (game2_button.isPressed(mousePosition, mousePressed))
		{
			std::cout << "game 2 button is pressed\n";
		}
		if (game3_button.isPressed(mousePosition, mousePressed))
		{
			std::cout << "game 3 button is pressed\n";
		}
		if (game4_button.isPressed(mousePosition, mousePressed))
		{
			std::cout << "game 4 button is pressed\n";
		}
		if (game5_button.isPressed(mousePosition, mousePressed))
		{
			std::cout << "game 5 button is pressed\n";
		}

		// Drawing On Screen
		BeginDrawing();
		ClearBackground(BLACK);	// Clears every frame
		game1_button.Draw();
		game2_button.Draw();
		game3_button.Draw();
		game4_button.Draw();
		game5_button.Draw();


		EndDrawing();
	}

	CloseWindow();
	return 0;
}