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


} player_t;

void spawnLaser(player_t *player, player_t *laser);
void updatePlayer(player_t *player, player_t *laser);
void updateLaser(player_t *laser);
void initPlayer(player_t *player);
void drawPlayer(player_t *player);


#endif
