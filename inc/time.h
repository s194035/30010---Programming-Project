#ifndef TIME_H
#define TIME_H

#include "stm32f30x_conf.h"
#include "30010_io.h"

typedef struct {
int hr, minute, sec, hundSec;
} timestop_t;

void resetTimer(timestop_t *timer, int timeCount);

void updateTimer(timestop_t *timer);

void drawTimer(timestop_t *timer, int x, int y);

//void TIM2_IRQHandler(void);

void setupTimer();

void startTimer();

#endif
