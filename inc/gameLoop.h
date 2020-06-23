#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "ansi.h"
#include "pin_io.h"
#include "lcd.h"
#include "time.h"
#include "updateships.h"
#include <string.h>
#include "charset.h"
#include "gameScreen.h"

#define MAX_C_GRAPH 40
#define MAX_C_UPDATERATE 20

// global variable
static uint32_t checkCount; //This counter will overflow after 44 hours! At that point, the gameloop breaks.

void TIM2_IRQHandler(void);
uint8_t pause();
void gameLoop(uint8_t settings);


#endif
