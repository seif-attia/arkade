#include <raylib.h>
#include "../button.h"
#include "duck_invaders.h"
#include "duck.h"


/**********************************************************************/
		// CUSTOM FUNCTION REGION OR CLASSES OR STRUCTS
/**********************************************************************/





/**********************************************************************/


void playDuckInvaders() // main
{
	/**********************************************************************/
				// DECLARE ALL THE VARIABLES HERE LIKE MAIN
	/**********************************************************************/
	const int screenWidth = 1200;
	const int screenHeight = 800;

	SetWindowSize(screenWidth, screenHeight);

	bool playing = true;
	Button quitButton("assets/sprites/white_button.png", { 50, 50 / 2 }, 0.2);






	/**********************************************************************/


	// Game Loop
	while (playing)
	{

		/**********************************************************************/
				// CHECKING FOR VARIABLES THAT NEED TO BE CONSTANTLY UPDATED
		/**********************************************************************/
		// Initilization of variables
		Vector2 mousePosition = GetMousePosition();
		bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);



		/**********************************************************************/
							// INPUT REGION
		/**********************************************************************/

		// Check for user input
		if (quitButton.isPressed(mousePosition, mousePressed))
		{
			playing = false;
		}

		// Returns to the main menu if the X button is pressed
		if (WindowShouldClose() == true)
		{
			playing = false;
		}



		/**********************************************************************/
							// DRAWING REGION
		/**********************************************************************/

		// Drawing
		BeginDrawing();

		ClearBackground(BLACK);

		DrawText("DuckInvaders!", 190, 200, 20, WHITE);

		quitButton.Draw();
		DrawText("quit", quitButton.getPostion().x + 12, quitButton.getPostion().y + 6, 20, BLACK);




		EndDrawing();

		/**********************************************************************/
	}
}