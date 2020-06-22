#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "ansi.h"
#include "30010_io.h"
#include "updateships.h"

uint8_t mainMenu(uint16_t *highScore);
void printMainMenu();
void printHelp();
void printHighScore(uint16_t *highScore);
void printSettings();
void printPlayer();
void moveCursorDown(uint8_t x0, uint8_t y0);
void moveCursorUp(uint8_t x0, uint8_t y0);



#endif
