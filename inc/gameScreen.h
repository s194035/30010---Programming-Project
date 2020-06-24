#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "ansi.h"
#include "30010_io.h"
#include "updateships.h"

#define WIDTH 164
#define HEIGHT 48
#define X_OFFSET 8
#define Y_OFFSET 8

uint8_t mainMenu(uint16_t *highScore);
void printMainMenu();
void printHelp();
void printHighScore(uint16_t *highScore);
void printSettings();
void printPlayer();
void moveCursorDown(uint8_t x0, uint8_t y0);
void moveCursorUp(uint8_t x0, uint8_t y0);
void printPauseScreen();
void printGameOverScreen(uint16_t *score);
void printWinScreen(uint8_t *difficulty);
void printBlank();


#endif
