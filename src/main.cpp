#include <raylib.h>
#include "button.h"

#include "game_center.h"

Sound buttonPressSound;


int main()
{
	const int screenWidth = 1200;
	const int screenHeight = 800;

	InitWindow(screenWidth, screenHeight, "Arkade++");
	SetTargetFPS(60);

	InitAudioDevice();

	//Sounds

	Sound startSound = LoadSound("assets/sounds/gamestart.mp3");

	buttonPressSound = LoadSound("assets/sounds/Button_Press.mp3");

	// Variables

	Button gameCenterButton("assets/sprites/start.png", { screenWidth / 2, 3 * screenHeight / 4 }, 1);


	Image icon = LoadImage("assets/sprites/arkade_icon.png");

	// Start Background

	Texture2D background = LoadTexture("assets/sprites/start_background.png");

	SetWindowIcon(icon);




	// Game Loop
	while (WindowShouldClose() == false)
	{
		Vector2 mousePosition = GetMousePosition();
		bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

		// User Input
		if (gameCenterButton.isPressed(mousePosition, mousePressed))
		{
			PlaySound(startSound);
			startGameCenter();
		}

		// Drawing On Screen
		BeginDrawing();
		ClearBackground(BLUE);	// Clears every frame

		DrawTexture(background, 0, 0, WHITE);


		// Start Button
		gameCenterButton.Draw();



		EndDrawing();
	}

	UnloadSound(startSound);
	UnloadSound(buttonPressSound);
	UnloadTexture(background);
	UnloadImage(icon);
	CloseWindow();
	return 0;
}