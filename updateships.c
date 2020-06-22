#include "updateships.h"
#include "pin_io.h"

#define WIDTH 168
#define HEIGHT 44

uint8_t boundaryCheck(uint8_t w, uint8_t h, uint8_t x, uint8_t y){

    if (x < 1 || WIDTH - GRAPH_SIZE < x || y < 2 || HEIGHT - GRAPH_SIZE-1 < y){
            return 1; // graphics outside boundary
    }
    return 0; // else return 0
}



void spawnLaser(gobj_t *player, gobj_t *laser){

uint8_t i;

// Cycle the list for active objects
    for (i = 0; i < LASER_POOL; i++){
        if (!(laser[i].active)){
            laser[i].x = player->x;
            laser[i].y = player->y;
            laser[i].speed = LASER_SPEED;
            laser[i].active = 1;
            break;
        }
    }
    // if all lasers are active, then don't shoot any
}

void updatePlayer(gobj_t *player, gobj_t *laser){

    // TODO: split this function up in a inputmanager() and a playerupdate()

    uint8_t tempx = player->x;
    uint8_t tempy = player->y;
    int8_t tempspeed = player->speed;

    char controlChar = uart_get_char();

    // x position
    if (controlChar == 'd'){

            if (!boundaryCheck(WIDTH, HEIGHT, tempx + tempspeed, tempy)){
                tempx += tempspeed;
                        setLed(0,0,0);
                        LedPinSetup(9,'A',0);
            }
    }
    if (controlChar == 'a'){

            if(!(boundaryCheck(WIDTH, HEIGHT, tempx - tempspeed, tempy))){
            tempx -= tempspeed;
            setLed(0,0,0);
            LedPinSetup(7,'C',0);
            }
    }

    // y position
    if (controlChar == 'w'){

            if(!boundaryCheck(WIDTH, HEIGHT, tempx, tempy - tempspeed)){
            tempy -= tempspeed;
            setLed(0,0,0);
            LedPinSetup(4,'B',0);
            }
    }

    if (controlChar == 's'){

            if(!boundaryCheck(WIDTH, HEIGHT, tempx, tempy+tempspeed)){
            tempy += tempspeed;
            setLed(0,0,0);
            LedPinSetup(7,'C',0);
            LedPinSetup(4,'B',0);
            }
    }

    // shoot
    if (controlChar == 'q'){
            spawnLaser(player, laser);

    }
    player->x = tempx;
    player->y = tempy;
}


void updateLaser(gobj_t laser[]){
    uint8_t i;

    for (i = 0; i < LASER_POOL; i++){
        if(laser[i].active){
                laser[i].y -= laser[i].speed;
        }
    }
}

// all these inits should be one function!
void initPlayer(gobj_t *player){

    player->x = 10;
    player->y = 10;
    player->speed = 1;
    player->img = 0; // sets graphic
    player->active = 1; // sets active

    // sets collision box
    player->boxX1 = 1;
    player->boxY1 = 1;
    player->boxX2 = 3;
    player->boxY2 = 3;

}

void initLaser(gobj_t *laser){

    laser->x = 0;
    laser->y = 0;
    laser->speed = 0;
    laser->img = 1; // sets graphic.
    laser->active = 0; // sets active

}

void initEnemy(gobj_t *enemy){

    enemy->x = 16;
    enemy->y = 16;
    enemy->speed = 0;
    enemy->img = 2; // sets graphic
    enemy->active = 1; // sets active

    // sets collision box
    enemy->boxX1 = 1;
    enemy->boxY1 = 1;
    enemy->boxX2 = 5;
    enemy->boxY2 = 5;
}

void drawPlayer(gobj_t *player){
    uint8_t i;
    uint8_t j;

    // before we do anything, we check if the object is active:
    if (player->active){

        // go to origin
        gotoxy(player->x, player->y);

        for (i = 0; i < 6; i++){
            for (j = 0; j < 6; j++){

                // First index in sheet is the player image value
                // the two others are for the 2d graphics
                if (graph[player->img][j][i] != 0){
                    gotoxy(player->x + i, player->y + j);
                    printf("%c", graph[player->img][j][i]);
                }
            }
        }
        //gotoxy(3,3); // removes tail.
    }
}

void drawEnemy(gobj_t *enemy){
    uint8_t i;
    uint8_t j;

    if(enemy->active){
        gotoxy(enemy->x, enemy->y);

        for(i = 0; i<6; i++){
            for(j = 0; j < 6; j++){
                if(graph[enemy->img][j][i] !=0){
                    gotoxy(enemy->x + i, enemy->y + j);
                    printf("%c", graph[enemy->img][j][i]);
                }
            }
        }
    }
}

uint8_t checkCollision(gobj_t *obj1, gobj_t *obj2){

    // first we check for possible collision on x axis:
    // First statement is corner on each side of box
    // next two is each corner inside of box
    if ( (obj1->boxX1 + obj1->x <= obj2->boxX1 + obj2->x && obj2->boxX2 + obj2->x <= obj1->boxX2 + obj1->x) ||
         (obj2->boxX1 + obj2->x <= obj1->boxX1 + obj1->x && obj1->boxX1 + obj1->x <= obj2->boxX2 + obj2->x) ||
         (obj2->boxX1 + obj2->x <= obj1->boxX2 + obj1->x && obj1->boxX2 + obj1->x <= obj2->boxX2 + obj2->x) ){

        // Then we check for possible collision on y axis:
        if ( (obj1->boxY1 + obj1->y <= obj2->boxY1 + obj2->y && obj2->boxY2 + obj2->y <= obj1->boxY2 + obj1->y) ||
             (obj2->boxY1 + obj2->y <= obj1->boxY1 + obj1->y && obj1->boxY1 + obj1->y <= obj2->boxY2 + obj2->y) ||
             (obj2->boxY1 + obj2->y <= obj1->boxY2 + obj1->y && obj1->boxY2 + obj1->y <= obj2->boxY2 + obj2->y) ){

                // there is a collision! Return true:
                return(1);
             }

    }
    // else return false:
    return(0);
}
