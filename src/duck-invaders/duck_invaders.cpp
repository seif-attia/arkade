#include <raylib.h>
#include "../button.h"
#include "duck_invaders.h"
#include "duck.h"


//Functions









void playDuckInvaders()
{

	const int screenWidth = 1200;
	const int screenHeight = 800;


	SetWindowSize(screenWidth, screenHeight);

	bool playing = true;
	Button quitButton("assets/sprites/white_button.png", { 50, 50 / 2 }, 0.2);

	while (playing)
	{
		Vector2 mousePosition = GetMousePosition();
		bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);


		BeginDrawing();

		ClearBackground(BLACK);

		DrawText("DuckInvaders!", 190, 200, 20, WHITE);

		quitButton.Draw();
		DrawText("quit", quitButton.getPostion().x + 12, quitButton.getPostion().y + 6, 20, BLACK);

		if (quitButton.isPressed(mousePosition, mousePressed))
		{
			playing = false;
		}


		EndDrawing();
	}
}