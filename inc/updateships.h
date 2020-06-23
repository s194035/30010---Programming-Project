#ifndef UPDATESHIPS_H
#define UPDATESHIPS_H
#include "30010_io.h"
#include <string.h>
#include "ansi.h"
#include "graphicsSheet.h"
#include "pin_io.h"

// general
#define SET_ACTIVE 1
#define SET_INACTIVE 0

// Laser constants
#define LASER_POOL 6 // amount of active shots on screen
#define LASER_SPEED -512 // speed of laser in 8.8
#define LASER_BBOX_x1 1
#define LASER_BBOX_Y1 0
#define LASER_BBOX_X2 4
#define LASER_BBOX_Y2 5

// player constants
#define PLAYER_BBOX_XY1 1 // x and y coordinates for bbox
#define PLAYER_BBOX_XY2 4 // x and y coordinates for bbox
#define PLAYER_SPEED 256 // speed of player in 8.8

// enemy constants
#define ENEMY_POOL 16 // amount of enemies on screen
#define ENEMY_BBOX_XY1 1 // x and y coordinates for bbox
#define ENEMY_BBOX_XY2 4 // x and y coordinates for bbox
#define ENEMY_SPEED 128 // speed of enemy in 8.8

// Playfield constants
#define WIDTH_PF 50 // width of playfield
#define HEIGHT_PF 70 // height of playfield
#define PF_OFF_X 8 // playfield offset on x-axis
#define PF_OFF_Y 8 //playfield offset on y-axis

// for fixedpoint calculations:
#define FIX8_shift 8

typedef struct {
    uint16_t x; // x position in floating point 8.8 (remember to shift >> 4 when using this number!)
    uint16_t y; // y position in floating point 8.8
    int16_t speed; // speed in floating point 8.8 *IMPORTANT* must be signed

    // graphic
    uint8_t img;

    //flags
    uint8_t active;

    //Collison bounds:
    uint16_t boxX1;
    uint16_t boxY1;
    uint16_t boxX2;
    uint16_t boxY2;


} gobj_t;


uint8_t boundaryCheck(uint8_t w, uint8_t h, uint16_t x, uint16_t y);
void spawnLaser(gobj_t *player, gobj_t *laser);
void updatePlayer(gobj_t *player, gobj_t *laser);
void updateLaser(gobj_t *laser);
void initObj(gobj_t *obj, uint16_t startx, uint16_t starty, int16_t speed, uint8_t img, uint8_t active,
             uint16_t boxX1, uint16_t boxY1, uint16_t boxX2, uint16_t boxY2);

void writeToUpdateBuffer(gobj_t *obj, uint8_t upBuffer[WIDTH_PF][HEIGHT_PF]);
void writeBgToBuffer(uint8_t img, uint8_t x, uint8_t y, uint8_t flip, uint8_t upBuffer[WIDTH_PF][HEIGHT_PF]);
void drawBackground(uint8_t upBuffer[WIDTH_PF][HEIGHT_PF]);
void drawFromBuffer(uint8_t upBuffer[WIDTH_PF][HEIGHT_PF], uint8_t scrBuffer[WIDTH_PF][HEIGHT_PF]);
uint8_t checkCollision(gobj_t *obj1, gobj_t *obj2);

void updateEnemy(gobj_t enemy[]);
void enemyHandler(gobj_t enemy[], uint8_t difficulty);

#endif
