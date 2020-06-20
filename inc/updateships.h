#ifndef UPDATESHIPS_H
#define UPDATESHIPS_H
#include "30010_io.h"
#include <string.h>
#include "ansi.h"
#include "graphicsSheet.h"

#define LASER_POOL 6 // amount of active shots on screen
#define LASER_SPEED 1 // speed of laser

// Playfield constants
#define WIDTH 50 // width of playfield
#define HEIGHT 75 // height of playfield
#define PF_OFF_X 8 // playfield offset on x-axis
#define PF_OFF_Y 8 //playfield offset on y-axis


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


} gobj_t;


uint8_t boundaryCheck(uint8_t w, uint8_t h, uint8_t x, uint8_t y);
void spawnLaser(gobj_t *player, gobj_t *laser);
void updatePlayer(gobj_t *player, gobj_t *laser);
void updateLaser(gobj_t *laser);
void initPlayer(gobj_t *player);
void initLaser(gobj_t *laser);
void initEnemy(gobj_t *enemy);
void initObj(gobj_t *obj, uint8_t startx, uint8_t starty, int8_t speed, uint8_t img, uint8_t active,
             uint8_t boxX1, uint8_t boxY1, uint8_t boxX2, uint8_t boxY2);

void drawObj(gobj_t *player);
void writeToUpdateBuffer(gobj_t *obj, uint8_t upBuffer[WIDTH][HEIGHT]);
void drawFromBuffer(uint8_t upBuffer[WIDTH][HEIGHT], uint8_t scrBuffer[WIDTH][HEIGHT]);
uint8_t checkCollision(gobj_t *obj1, gobj_t *obj2);


#endif
