#include "updateships.h"

void spawnLaser(gobj_t *player, gobj_t *laser){

int32_t spawnPx = player->x;
int32_t spawnPy = player->y;

laser->x = spawnPx;
laser->y = spawnPy;

laser->speed = 1;

}

void updatePlayer(gobj_t *player, gobj_t *laser){

    int32_t tempx = player->x;
    int32_t tempy = player->y;
    int8_t tempspeed = player->speed;

    char controlChar = uart_get_char();

    // x position
    if (controlChar == 'd'){
            tempx += tempspeed;
    }
    if (controlChar == 'a'){
            tempx -= tempspeed;
    }

    // y position
    if (controlChar == 'w'){
            tempy -= tempspeed;
    }
    if (controlChar == 's'){
            tempy += tempspeed;
    }

    // shoot
    if (controlChar == 'q'){
            spawnLaser(player, laser);
    }

    player->x = tempx;
    player->y = tempy;
}

void updateLaser(gobj_t *laser){
    int32_t tempx = laser->x;
    int32_t tempy = laser->y;
    int8_t tempspeed = laser->speed;

    // update speed
    tempy -= tempspeed;

    laser->y = tempy;
    laser->x = tempx;
}

void initPlayer(gobj_t *player){

    int8_t imgTemp[6][6] = {
    {219, 219, 219, 219, 219, 219},
    {219,   0,   0,   0,   0, 219},
    {219,   0,   0,   0,   0, 219},
    {219,   0,   0,   0,   0, 219},
    {219,   0,   0,   0,   0, 219},
    {219,   0,   0,   0,   0, 219},
    };

    player->x = 4;
    player->y = 4;
    player->speed = 2;

    //copy over in struct:
    memcpy(player->img, imgTemp, 6*6*sizeof(int8_t));

}

void initLaser(gobj_t *laser){

    int8_t imgTemp[6][6] = {
    {0,   0, 219, 219,   0,   0},
    {0,   0, 219, 219,   0,   0},
    {0,   0, 219, 219,   0,   0},
    {0,   0, 219, 219,   0,   0},
    {0,   0, 219, 219,   0,   0},
    {0,   0, 219, 219,   0,   0},
    };

    memcpy(laser->img, imgTemp, 6*6*sizeof(int8_t));

}

void drawObj(gobj_t *player){
    int i;
    int j;

    gotoxy(player->x, player->y);

    for (i = 0; i < 6; i++){
        for (j = 0; j < 6; j++){

            if (player->img[i][j] != 0){
                gotoxy(player->x + i, player->y + j);
                printf("%c", player->img[i][j]);
            }
        }
    }
}


