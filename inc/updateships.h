#ifndef UPDATESHIPS_H
#define UPDATESHIPS_H
#include "30010_io.h"
#include <string.h>
#include "ansi.h"
#include "graphicsSheet.h"
#include "pin_io.h"

#define LASER_POOL 6 // amount of active shots on screen
#define LASER_SPEED -1 // speed of laser

#define ENEMY_POOL 16 // amount of enemies on screen

// Playfield constants
#define WIDTH_PF 50 // width of playfield
#define HEIGHT_PF 70 // height of playfield
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
void initObj(gobj_t *obj, uint8_t startx, uint8_t starty, int8_t speed, uint8_t img, uint8_t active,
             uint8_t boxX1, uint8_t boxY1, uint8_t boxX2, uint8_t boxY2);

void drawObj(gobj_t *player);
void writeToUpdateBuffer(gobj_t *obj, uint8_t upBuffer[WIDTH_PF][HEIGHT_PF]);
void writeBgToBuffer(uint8_t img, uint8_t x, uint8_t y, uint8_t flip, uint8_t upBuffer[WIDTH_PF][HEIGHT_PF]);
void drawBackground(uint8_t upBuffer[WIDTH_PF][HEIGHT_PF]);
void drawFromBuffer(uint8_t upBuffer[WIDTH_PF][HEIGHT_PF], uint8_t scrBuffer[WIDTH_PF][HEIGHT_PF]);
uint8_t checkCollision(gobj_t *obj1, gobj_t *obj2);

void updateEnemy(gobj_t enemy[]);
void enemyHandler(gobj_t enemy[], uint8_t difficulty);

#endif
