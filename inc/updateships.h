#ifndef UPDATESHIPS_H
#define UPDATESHIPS_H
#include "30010_io.h"
#include <string.h>
#include "ansi.h"

typedef struct {
    int32_t x; // x position
    int32_t y; // y position
    int8_t speed; // speed

    int8_t img[6][6];

    //Collison bounds:
    int8_t boxX1;
    int8_t boxY1;
    int8_t boxX2;
    int8_t boxY2;


} gobj_t;

void spawnLaser(gobj_t *player, gobj_t *laser);
void updatePlayer(gobj_t *player, gobj_t *laser);
void updateLaser(gobj_t *laser);
void initPlayer(gobj_t *player);
void initLaser(gobj_t *laser);
void drawObj(gobj_t *player);


#endif
