#include <raylib.h>
#include "button.h"
#include <string>

#include "game_center.h"

#define MAX_INPUT_CHARS 20

Sound buttonPressSound;
Font font;
Music opening_music;

std::string PlayerName;

int main()
{
	const int screenWidth = 1200;
	const int screenHeight = 800;

	SetConfigFlags(FLAG_WINDOW_HIGHDPI);
	InitWindow(screenWidth, screenHeight, "Arkade++");
	SetTargetFPS(60);

	InitAudioDevice();

	// Font

	font = LoadFont("assets/fonts/MontserratAlternates-Bold.otf");

	//Sounds
	opening_music = LoadMusicStream("assets/sounds/opening.ogg");
	PlayMusicStream(opening_music);

	Sound startSound = LoadSound("assets/sounds/start.ogg");

	buttonPressSound = LoadSound("assets/sounds/Button_Press.mp3");

	// Variables

	Button gameCenterButton("assets/sprites/start.png", { screenWidth / 2, 3 * screenHeight / 4 }, 1);


	Image icon = LoadImage("assets/sprites/arkade_icon.png");

	// Start Background

	Texture2D background = LoadTexture("assets/sprites/start_background.png");

	SetWindowIcon(icon);


	// Handle Text Input for player name
	std::string name = "";
	bool chosePlayerName = false;
	bool mouseOnText = false;
	Rectangle playerNameRec = { 50, 7.0 * screenHeight / 8.0 + 40, 150, 40 };
	int framesCounter = 0;
	Color chosen_name_color = { 255,0,76, 255 };



	// Game Loop
	while (WindowShouldClose() == false)
	{
		UpdateMusicStream(opening_music);
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

		// Enter Player Name

		DrawRectangleRec(playerNameRec, WHITE);
		if (CheckCollisionPointRec(mousePosition, playerNameRec) && mousePressed)
		{
			mouseOnText = true;
		}
		if (!CheckCollisionPointRec(mousePosition, playerNameRec) && mousePressed)
		{
			mouseOnText = false;
		}

		if (mouseOnText)
		{
			SetMouseCursor(MOUSE_CURSOR_IBEAM);

			int key = GetCharPressed();
			while (key > 0)
			{
				if ((key >= 32) && (key <= 126) && name.length() < MAX_INPUT_CHARS)
				{
					name += (char)key;
				}

				key = GetCharPressed();

			}
			if (IsKeyPressed(KEY_BACKSPACE))
			{
				if (!name.empty())
				{
					name.pop_back();
				}
			}

			if (IsKeyPressed(KEY_ENTER))
			{
				PlayerName = name;
				name = "";
				mouseOnText = false;
			}
		}
		else
		{
			SetMouseCursor(MOUSE_CURSOR_DEFAULT);
		}


		DrawText(name.c_str(), playerNameRec.x + 5, playerNameRec.y + 8, 25, BLACK);

		// Chosen Name
		std::string chosenName = "Player name: " + PlayerName;
		Vector2 chosenNamePos = { screenWidth - MeasureTextEx(font,chosenName.c_str(),25,3).x - 25, 25 };
		DrawTextEx(font, chosenName.c_str(), chosenNamePos, 25, 3, chosen_name_color);



		EndDrawing();
	}

	UnloadMusicStream(opening_music);
	UnloadFont(font);
	UnloadSound(startSound);
	UnloadSound(buttonPressSound);
	UnloadTexture(background);
	UnloadImage(icon);
	CloseWindow();
	return 0;
}