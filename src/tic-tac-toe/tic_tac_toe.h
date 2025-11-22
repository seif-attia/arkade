#pragma once
#include "cell.h"

#define X_MARK 1
#define O_MARK 2
#define IS_EMPTY 0
#define PLAYING 0
#define X_WON 1
#define O_WON 2
#define DRAW 3

void playTicTacToe(const int screenWidth, const int screenHeight);
void cellDraw(const int screenWidth, const int screenHeight);
void drawMarks(Cell(&cells)[3][3], Texture2D oTexture, Texture2D xTexture);
