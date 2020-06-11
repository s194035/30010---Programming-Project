#include "30010_io.h"
#include "Sine_lookup_table.h"
#include "ball.h"
#include "ansi.h"

#define FIX14_SHIFT 14

// Initialize ball with position and velocity
void initBall(ball_t *b, int32_t x0, int32_t y0, int32_t vx0, int32_t vy0){
    b->x = x0 << FIX14_SHIFT;
    b->y = y0 << FIX14_SHIFT;
    b->vx = vx0 << FIX14_SHIFT;
    b->vy = vy0 << FIX14_SHIFT;
}

// Update ball velocity
void update(ball_t *b, int on){
  if(on) {
      gotoxy(b->x >> FIX14_SHIFT, b->y >> FIX14_SHIFT);
  }
  b->x = b->x + b->vx;
  b->y = b->y + b->vy;
}


// Draw the ball's position
void drawPos(ball_t *b){
  gotoxy(b->x >> FIX14_SHIFT, b->y >> FIX14_SHIFT);
  printf("o");
}


// Check if ball collides with window borders
int collisionCheck(ball_t *b, int32_t x1, int32_t y1, int32_t x2, int32_t y2){
    int32_t temp_x = b->x >> FIX14_SHIFT;
    int32_t temp_y = b->y >> FIX14_SHIFT;

    if(temp_x <= x1+1 || temp_x >= x2){
        b->vx = -(b->vx);
    }
    if(temp_y <= y1 || temp_y >= y2){
        b->vy = -(b->vy);
    }
    return 1;
}
