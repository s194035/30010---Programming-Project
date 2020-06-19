#ifndef UPDATESHIPS_H
#define UPDATESHIPS_H
#include "30010_io.h"
#include <string.h>
#include "ansi.h"
#include "graphicsSheet.h"

#define LASER_POOL 6 // amount of active shots on screen
#define LASER_SPEED 1 // speed of laser

typedef struct {
    uint8_t x; // x position
    uint8_t y; // y position
    int8_t speed; // speed *IMPORTANT* must be signed

    // graphic
    uint8_t img;

    //flags
    uint8_t active;

    //Collison bounds:
    uint8_t boxX1;
    uint8_t boxY1;
    uint8_t boxX2;
    uint8_t boxY2;


}

gobj_t;

void spawnLaser(gobj_t *player, gobj_t *laser);
void updatePlayer(gobj_t *player, gobj_t *laser);
void updateLaser(gobj_t *laser);
void initPlayer(gobj_t *player);
void initLaser(gobj_t *laser);
void initEnemy(gobj_t *enemy);
void drawPlayer(gobj_t *player);
uint8_t checkCollision(gobj_t *obj1, gobj_t *obj2);


#endif
