#include <raylib.h>
#include "../button.h"
#include "tic_tac_toe.h"
#include "cell.h"



void cellDraw(const int screenWidth, const int screenHeight)
{
	int sideLength = 700;
	int cellSize = sideLength / 3;
	int xPosition = (float)screenWidth / 2 - (float)sideLength / 2;
	int yPosition = (float)screenHeight / 2 - (float)sideLength / 2 + 40;
	DrawRectangle(xPosition, yPosition, sideLength, sideLength, WHITE);

	// Vertical Lines
	DrawLine(xPosition + cellSize, yPosition, xPosition + cellSize, yPosition + 3 * cellSize, BLACK);
	DrawLine(xPosition + 2 * cellSize, yPosition, xPosition + 2 * cellSize, yPosition + 3 * cellSize, BLACK);
	// Horizontal Lines
	DrawLine(xPosition, yPosition + cellSize, xPosition + 3 * cellSize, yPosition + cellSize, BLACK);
	DrawLine(xPosition, yPosition + 2 * cellSize, xPosition + 3 * cellSize, yPosition + 2 * cellSize, BLACK);

}

void drawMarks(Cell(&cells)[3][3], Texture2D oTexture, Texture2D xTexture)
{
	float padding = 20;
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			int state = cells[r][c].getState();
			Rectangle cellRect = cells[r][c].getRectangle();

			if (state == X_MARK)
			{
				Rectangle srcRec = { 0, 0, xTexture.width, xTexture.height };
				Rectangle disRec = { cellRect.x + padding, cellRect.y + padding, cellRect.width - 2 * padding, cellRect.height - 2 * padding };

				DrawTexturePro(xTexture, srcRec, disRec, { 0,0 }, 0, WHITE);
			}
			else if (state == O_MARK)
			{
				Rectangle srcRec = { 0, 0, oTexture.width, oTexture.height };
				Rectangle disRec = { cellRect.x + padding, cellRect.y + padding, cellRect.width - 2 * padding, cellRect.height - 2 * padding };

				DrawTexturePro(oTexture, srcRec, disRec, { 0,0 }, 0, WHITE);
			}
		}
	}
}

void clearCells(Cell(&cells)[3][3])
{
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			cells[r][c].setState(IS_EMPTY);
		}
	}
}

bool checkWin(Cell(&cells)[3][3], int currentPlayer)
{
	// check for row wins
	for (int r = 0; r < 3; r++)
	{
		if (cells[r][0].getState() == currentPlayer &&
			cells[r][1].getState() == currentPlayer &&
			cells[r][2].getState() == currentPlayer)
			return true;
	}

	// check for column	wins
	for (int c = 0; c < 3; c++)
	{
		if (cells[0][c].getState() == currentPlayer &&
			cells[1][c].getState() == currentPlayer &&
			cells[2][c].getState() == currentPlayer)
			return true;
	}

	// check for diagonal wins
	if (cells[0][0].getState() == currentPlayer &&
		cells[1][1].getState() == currentPlayer &&
		cells[2][2].getState() == currentPlayer)
		return true;

	if (cells[2][0].getState() == currentPlayer &&
		cells[1][1].getState() == currentPlayer &&
		cells[2][0].getState() == currentPlayer)
		return true;

	return false;
}


void playTicTacToe(const int screenWidth, const int screenHeight)
{
	bool playing = true;
	bool canPlay = false;  // to prevent mouse from double clicking at the start

	Texture2D oTexture = LoadTexture("assets/sprites/o.png");
	Texture2D xTexture = LoadTexture("assets/sprites/x.png");

	Button quitButton("assets/sprites/white_button.png", { 50, 50 / 2 }, 0.2);

	float sideLength = 700;
	float cellSize = sideLength / 3;
	float xPosition = (float)screenWidth / 2 - sideLength / 2;
	float yPosition = (float)screenHeight / 2 - sideLength / 2 + 40;


	int moveCount = 0;
	int gameState = PLAYING;
	int currentPlayer = X_MARK;

	Cell cells[3][3];

	// Init cell postions
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			Rectangle rect = { xPosition + c * cellSize, yPosition + r * cellSize, cellSize, cellSize };
			cells[r][c].setRectangle(rect);
		}
	}


	while (playing)
	{
		if (WindowShouldClose() == true)
		{
			playing = false;
		}

		Vector2 mousePosition = GetMousePosition();
		bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

		BeginDrawing();
		ClearBackground(BLUE);
		cellDraw(screenWidth, screenHeight);

		drawMarks(cells, oTexture, xTexture);

		// game state text
		if (gameState == X_WON)
		{
			DrawText("X WON", screenWidth / 2, 20, 20, WHITE);
		}
		else if (gameState == O_WON)
		{
			DrawText("O WON", screenWidth / 2, 20, 20, WHITE);
		}

		if (canPlay == false)
		{
			if (IsMouseButtonUp(MOUSE_BUTTON_LEFT))
			{
				canPlay = true;
			}
		}

		// Check for cell presses
		if (canPlay)
		{
			for (int r = 0; r < 3; r++)
			{
				for (int c = 0; c < 3; c++)
				{
					if (cells[r][c].isPressed(mousePosition, mousePressed))
					{
						if (cells[r][c].getState() == IS_EMPTY)
						{
							if (currentPlayer == X_MARK && gameState == PLAYING)
							{
								cells[r][c].setState(X_MARK);

								if (checkWin(cells, currentPlayer))
									gameState = X_WON;
								else
									currentPlayer = O_MARK;
							}
							else if (currentPlayer == O_MARK && gameState == PLAYING)
							{
								cells[r][c].setState(O_MARK);

								if (checkWin(cells, currentPlayer))
									gameState = O_WON;
								else
									currentPlayer = X_MARK;
							}
						}
					}
				}
			}
		}



		quitButton.Draw();
		if (quitButton.isPressed(mousePosition, mousePressed))
		{
			playing = false;
		}
		EndDrawing();
	}

	UnloadTexture(oTexture);
	UnloadTexture(xTexture);
}