#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "ansi.h"
#include "30010_io.h"
#include "updateships.h"

uint8_t mainMenu(gobj_t *player, gobj_t *laser);
void printMainMenu();
void printHelp();
void printHighScore();



#endif
