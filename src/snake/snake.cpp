#include <raylib.h>
#include "snake.h"
#include "..\button.h"


void playSnake()
{

	const int screenWidth = 1200;
	const int screenHeight = 800;

	SetWindowSize(screenWidth, screenHeight);

	bool playing = true;

	Button quitButton("assets/sprites/white_button.png", { (float)screenWidth / 2, (float)screenHeight / 2 }, 0.5);


	while (playing == true)
	{
		// Init Variables

		Vector2 mousePosition = GetMousePosition();
		bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);


		// Game Logic

		if (WindowShouldClose() == true)
		{
			playing = false;
		}


		if (quitButton.isPressed(mousePosition, mousePressed))
		{
			playing = false;
		}

		// Drawing
		BeginDrawing();

		DrawText("Snake", 200, 200, 20, WHITE);

		ClearBackground(BLACK);

		quitButton.Draw();




		EndDrawing();
	}
}


// comment
// new commment
// newer comment