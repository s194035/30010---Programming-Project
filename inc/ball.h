#ifndef BALL_H
#define BALL_H

#include "stm32f30x_conf.h"
#include "30010_io.h"

typedef struct{
  int32_t x, y, vx, vy;
}ball_t;

void initBall(ball_t *b, int32_t x0, int32_t y0, int32_t vx0, int32_t vy0);

void update( ball_t *b, int on);

void drawPos(ball_t *b);

int collisionCheck(ball_t *b, int32_t x1, int32_t y1, int32_t x2, int32_t y2);


#endif
