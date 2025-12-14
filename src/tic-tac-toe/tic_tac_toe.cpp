#include <raylib.h>
#include "../button.h"
#include "tic_tac_toe.h"
#include "cell.h"
#include <string>
#include "..\playAgainMenu.h"



extern Sound buttonPressSound;
extern Font font;

struct WinningLine
{
	Vector2 start;
	Vector2 end;
	bool active;
};

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

bool checkWin(Cell(&cells)[3][3], int currentPlayer, WinningLine& line)
{
	int offSet = 110;
	// check for row wins
	for (int r = 0; r < 3; r++)
	{
		if (cells[r][0].getState() == currentPlayer &&
			cells[r][1].getState() == currentPlayer &&
			cells[r][2].getState() == currentPlayer)
		{
			Rectangle startRec = cells[r][0].getRectangle();
			Rectangle endRec = cells[r][2].getRectangle();

			line.start = { startRec.x + startRec.width / 2 - offSet,startRec.y + startRec.height / 2 };
			line.end = { endRec.x + endRec.width / 2 + offSet, endRec.y + endRec.height / 2 };
			line.active = true;

			return true;
		}
	}

	// check for column	wins
	for (int c = 0; c < 3; c++)
	{
		if (cells[0][c].getState() == currentPlayer &&
			cells[1][c].getState() == currentPlayer &&
			cells[2][c].getState() == currentPlayer)
		{
			Rectangle startRec = cells[0][c].getRectangle();
			Rectangle endRec = cells[2][c].getRectangle();

			line.start = { startRec.x + startRec.width / 2 ,startRec.y + startRec.height / 2 - offSet };
			line.end = { endRec.x + endRec.width / 2 , endRec.y + endRec.height / 2 + offSet };
			line.active = true;

			return true;
		}
	}

	// check for diagonal wins
	if (cells[0][0].getState() == currentPlayer &&
		cells[1][1].getState() == currentPlayer &&
		cells[2][2].getState() == currentPlayer)
	{
		Rectangle startRec = cells[0][0].getRectangle();
		Rectangle endRec = cells[2][2].getRectangle();

		line.start = { startRec.x + startRec.width / 2 - offSet,startRec.y + startRec.height / 2 - offSet };
		line.end = { endRec.x + endRec.width / 2 + offSet, endRec.y + endRec.height / 2 + offSet };
		line.active = true;

		return true;
	}

	if (cells[2][0].getState() == currentPlayer &&
		cells[1][1].getState() == currentPlayer &&
		cells[0][2].getState() == currentPlayer)
	{
		Rectangle startRec = cells[2][0].getRectangle();
		Rectangle endRec = cells[0][2].getRectangle();

		line.start = { startRec.x + startRec.width / 2 - offSet,startRec.y + startRec.height / 2 + offSet };
		line.end = { endRec.x + endRec.width / 2 + offSet, endRec.y + endRec.height / 2 - offSet };
		line.active = true;

		return true;
	}

	return false;
}



void playTicTacToe()
{
	const int screenWidth = 1200, screenHeight = 800;

	SetWindowSize(screenWidth, screenHeight);

	// turn color
	Color turn_color = { 255,176,3, 255 };

	bool playing = true;
	bool canPlay = false;  // to prevent mouse from double clicking at the start
	bool showMenu = false;
	bool showPlayAgain = false;


	Texture2D oTexture = LoadTexture("assets/sprites/o.png");
	Texture2D xTexture = LoadTexture("assets/sprites/x.png");

	// Background
	Texture2D background = LoadTexture("assets/sprites/tic-tac-toe-background.png");

	Music music = LoadMusicStream("assets/sounds/tic-tac-toe/town.ogg");
	PlayMusicStream(music);
	SetMusicVolume(music, 0.5f);

	Sound drawXO = LoadSound("assets/sounds/tic-tac-toe/xo_draw.ogg");


	GenTextureMipmaps(&oTexture);
	GenTextureMipmaps(&xTexture);

	SetTextureFilter(oTexture, TEXTURE_FILTER_TRILINEAR);
	SetTextureFilter(xTexture, TEXTURE_FILTER_TRILINEAR);

	Button menuButton("assets/sprites/setting.png", { 40, 40 }, 0.9);
	//Button restartButtton("assets/sprites/white_button.png", { screenWidth - 100 , screenHeight - 50 }, 0.4);

	Menu menu("assets/sprites/menu.png", { (float)screenWidth / 2, float(screenHeight) / 2 }, 1);

	Button playAgainButton("assets/sprites/retry.png", { 1100,735 }, 0.7);


	float sideLength = 700;
	float cellSize = sideLength / 3;
	float xPosition = (float)screenWidth / 2 - sideLength / 2;
	float yPosition = (float)screenHeight / 2 - sideLength / 2 + 40;


	int moveCount = 0;
	int gameState = PLAYING;
	int currentPlayer = X_MARK;
	int xScore = 0;
	int oScore = 0;

	Cell cells[3][3];

	WinningLine line = { {0,0}, {0,0}, false };

	// Init cell postions
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			Rectangle rect = { xPosition + c * cellSize, yPosition + r * cellSize, cellSize, cellSize };
			cells[r][c].setRectangle(rect);
		}
	}


	// restartGame function
	auto restartGame = [&cells, &moveCount, &gameState, &currentPlayer, &line, &showPlayAgain]()
		{
			clearCells(cells);
			showPlayAgain = false;
			moveCount = 0;
			gameState = PLAYING;
			currentPlayer = X_MARK;
			line.active = false;
		};


	while (playing)
	{
		UpdateMusicStream(music);
		if (WindowShouldClose() == true)
		{
			playing = false;
		}

		Vector2 mousePosition = GetMousePosition();
		bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

		BeginDrawing();
		ClearBackground(BLUE);
		// Background 
		DrawTexture(background, 0, 0, WHITE);

		cellDraw(screenWidth, screenHeight);

		drawMarks(cells, oTexture, xTexture);

		// game state text
		if (gameState == X_WON)
		{
			int textOffset = MeasureText("X WON", 40) / 2;
			DrawTextEx(font, "X WON", { (float)screenWidth / 2 - textOffset, 20 }, 40, 3, RED);
		}
		else if (gameState == O_WON)
		{
			int textOffset = MeasureText("O WON", 40) / 2;
			DrawTextEx(font, "O WON", { (float)screenWidth / 2 - textOffset, 20 }, 40, 3, RED);
		}
		else if (gameState == DRAW)
		{
			int textOffset = MeasureText("DRAW", 40) / 2;
			DrawTextEx(font, "DRAW", { (float)screenWidth / 2 - textOffset, 20 }, 40, 3, GREEN);

		}



		// current turn text
		if (currentPlayer == X_MARK && gameState == PLAYING)
		{
			int textOffset = MeasureText("X's TURN", 40) + 20;
			DrawTextEx(font, "X's TURN", { (float)screenWidth - textOffset, 20 }, 40, 3, turn_color);
		}
		else if (currentPlayer == O_MARK && gameState == PLAYING)
		{
			int textOffset = MeasureText("O's TURN", 40) + 20;
			DrawTextEx(font, "O's TURN", { (float)screenWidth - textOffset, 20 }, 40, 3, turn_color);
		}

		// Player score text

		std::string x_score = "Player X: " + std::to_string(xScore);
		std::string o_score = "Player O: " + std::to_string(oScore);

		int x_scoreXPos = cells[0][0].getRectangle().x;
		int x_scoreYPos = cells[0][0].getRectangle().y;
		int o_scoreXPos = cells[0][2].getRectangle().x + cells[0][2].getRectangle().width - MeasureText(o_score.c_str(), 35) - 25;
		int o_scoreYPos = cells[0][2].getRectangle().y;

		DrawTextEx(font, x_score.c_str(), { (float)x_scoreXPos, (float)x_scoreYPos - 60 }, 40, 3, BLACK);
		DrawTextEx(font, o_score.c_str(), { (float)o_scoreXPos, (float)o_scoreYPos - 60 }, 40, 3, BLACK);


		// Winning line Draw
		if (line.active == true)
		{
			DrawLineEx(line.start, line.end, 15, RED);
		}

		if (canPlay == false)
		{
			if (IsMouseButtonUp(MOUSE_BUTTON_LEFT))
			{
				canPlay = true;
			}
		}

		if (playAgainButton.isPressed(mousePosition, mousePressed))
		{
			restartGame();
		}


		// Menu buttons input code
		if (showMenu == true)
		{
			canPlay = false;
			if (menu.quitButton.isPressed(mousePosition, mousePressed))
			{
				PlaySound(buttonPressSound);
				playing = false;
			}
			if (menu.playAgainButton.isPressed(mousePosition, mousePressed))
			{
				PlaySound(buttonPressSound);
				showMenu = false;
				canPlay = false; // avoid mouse double clicking
				restartGame();
			}

			if (menu.closeMenuButton.isPressed(mousePosition, mousePressed))
			{
				PlaySound(buttonPressSound);
				showMenu = false;
			}

			menu.Draw();
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
								PlaySound(drawXO);
								cells[r][c].setState(X_MARK);
								moveCount++;

								if (checkWin(cells, currentPlayer, line))
								{
									gameState = X_WON;
									showPlayAgain = true;
									xScore++;
								}
								else if (moveCount == 9 && gameState == PLAYING)
								{
									gameState = DRAW;
									showPlayAgain = true;
								}
								else
									currentPlayer = O_MARK;
							}
							else if (currentPlayer == O_MARK && gameState == PLAYING)
							{
								PlaySound(drawXO);
								cells[r][c].setState(O_MARK);
								moveCount++;

								if (checkWin(cells, currentPlayer, line))
								{
									gameState = O_WON;
									showPlayAgain = true;
									oScore++;
								}
								else if (moveCount == 9 && gameState == PLAYING)
								{
									gameState = DRAW;
									showPlayAgain = true;
								}
								else
									currentPlayer = X_MARK;
							}
						}
					}
				}
			}
		}

		if (showPlayAgain == true)
		{
			playAgainButton.Draw();
		}

		// quit button
		menuButton.Draw();

		// menu button
		if (menuButton.isPressed(mousePosition, mousePressed))
		{
			PlaySound(buttonPressSound);
			showMenu = !showMenu;
		}



		EndDrawing();
	}

	UnloadSound(drawXO);
	UnloadMusicStream(music);
	UnloadTexture(background);
	UnloadTexture(oTexture);
	UnloadTexture(xTexture);
}