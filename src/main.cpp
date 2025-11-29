#include <raylib.h>
#include "button.h"

#include "game_center.h"




int main()
{
	const int screenWidth = 1200;
	const int screenHeight = 800;

	InitWindow(screenWidth, screenHeight, "Arkade++");
	SetTargetFPS(60);

	// Variables

	Button gameCenterButton("assets/sprites/white_button.png", { screenWidth / 2, 2 * screenHeight / 3 }, 0.8);

	// LOGO LOADING
	const float logoScale = 0.3;
	Image image = LoadImage("assets/sprites/arkade_logo.png");
	int newWidth = image.width * logoScale;
	int newHeight = image.height * logoScale;


	ImageResize(&image, newWidth, newHeight);
	Texture2D logo = LoadTextureFromImage(image);
	UnloadImage(image);

	// Game Loop
	while (WindowShouldClose() == false)
	{
		Vector2 mousePosition = GetMousePosition();
		bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

		// User Input
		if (gameCenterButton.isPressed(mousePosition, mousePressed))
		{
			startGameCenter();
		}

		// Drawing On Screen
		BeginDrawing();
		ClearBackground(BLUE);	// Clears every frame


		// LOGO

		DrawTexture(logo, screenWidth / 2 - logo.width / 2, screenHeight / 3 - logo.height / 2, WHITE);


		// Start Button
		gameCenterButton.Draw();
		// Start text
		const int startFont = 50;
		int startOffset = MeasureText("START", startFont) / 2;
		int startX = gameCenterButton.getPostion().x + gameCenterButton.getWidth() / 2 - startOffset;
		int startY = gameCenterButton.getPostion().y + gameCenterButton.getHeight() / 2 - startFont / 2;
		DrawText("START", startX, startY, startFont, BLACK);




		EndDrawing();
	}

	UnloadTexture(logo);
	CloseWindow();
	return 0;
}