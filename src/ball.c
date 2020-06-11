#include "30010_io.h"
#include "Sine_lookup_table.h"
#include "ball.h"
#include "ansi.h"

void initBall(struct ball_t *b, int32_t x0, int32_t y0, int32_t vx0, int32_t vy0){
    b->x = x0 << FIX14_SHIFT;
    b->y = y0 << FIX14_SHIFT;
    b->vx = vx0 << FIX14_SHIFT;
    b->vy = vy0 << FIX14_SHIFT;
}

void update(struct ball_t *b, int on){
  if(on) {
      gotoxy(b->x >> FIX14_SHIFT, b->y >> FIX14_SHIFT);
  }
  b->x = b->x + b->vx;
  b->y = b->y + b->vy;
}


void drawPos(struct ball_t *b){
  gotoxy(b->x >> FIX14_SHIFT, b->y >> FIX14_SHIFT);
  printf("o");
}

int collisionCheck(struct ball_t *b, int32_t x1, int32_t y1, int32_t x2, int32_t y2){
    int32_t temp_x = b->x >> FIX14_SHIFT;
    int32_t temp_y = b->y >> FIX14_SHIFT;
    vector_t vel;
    initVector(&vel, b->vx >> FIX14_SHIFT, b->vy >> FIX14_SHIFT);

    if(temp_x <= x1-1 || temp_x >= x2-1 || temp_y <= y1-1 || temp_y >= y2+1){
        rotate(&vel, 128);
        b->vx = vel.x;
        b->vy = vel.y;
        }
    return 1;
}
