#include <raylib.h>
#include "../button.h"
#include "tic_tac_toe.h"


void playTicTacToe(const int screenWidth, const int screenHeight)
{
	bool playing = true;
	Button test("assets/sprites/white_button.png", { (float)screenWidth / 2, (float)screenHeight / 2 }, 0.5);

	while (playing)
	{
		Vector2 mousePosition = GetMousePosition();
		bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);


		BeginDrawing();

		ClearBackground(BLACK);

		DrawText("TicTacToe!", 190, 200, 20, WHITE);

		test.Draw();

		if (test.isPressed(mousePosition, mousePressed))
		{
			playing = false;
		}


		EndDrawing();
	}
}