#include "updateships.h"

uint8_t boundaryCheck(uint8_t w, uint8_t h, uint8_t x, uint8_t y){

    if (x < 0 || WIDTH - GRAPH_SIZE < x || y < 0 || HEIGHT - GRAPH_SIZE < y){
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

void updatePlayer(gobj_t *player, gobj_t laser[]){

    // TODO: split this function up in a inputmanager() and a playerupdate()

    uint8_t tempx = player->x;
    uint8_t tempy = player->y;
    int8_t tempspeed = player->speed;

    char controlChar = uart_get_char();

    // x position
    if (controlChar == 'd'){

            if (!boundaryCheck(WIDTH, HEIGHT, tempx + tempspeed, tempy)){
                tempx += tempspeed;
            }
    }
    if (controlChar == 'a'){

            if(!(boundaryCheck(WIDTH, HEIGHT, tempx - tempspeed, tempy)))
            tempx -= tempspeed;
    }

    // y position
    if (controlChar == 'w'){

            if(!boundaryCheck(WIDTH, HEIGHT, tempx, tempy - tempspeed))
            tempy -= tempspeed;
    }
    if (controlChar == 's'){

            if(!boundaryCheck(WIDTH, HEIGHT, tempx, tempy+tempspeed))
            tempy += tempspeed;
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

            // Checks if laser is out of bounds
            if(!boundaryCheck(WIDTH, HEIGHT, laser[i].x, laser[i].y + laser[i].speed)) {
                laser[i].y += laser[i].speed;
            } else {
            // if its out of bounds, set it to inactive
            laser[i].active = 0;
            }
        }
    }
}

// general
void initObj(gobj_t *obj, uint8_t startx, uint8_t starty, int8_t speed, uint8_t img, uint8_t active,
             uint8_t boxX1, uint8_t boxY1, uint8_t boxX2, uint8_t boxY2){

    // start position and speed
    obj->x = startx;
    obj->y = starty;
    obj->speed = speed;

    // img
    obj->img = img;

    // active
    obj->active = active;

    // set bounding box
    obj->boxX1 = boxX1;
    obj->boxY1 = boxY1;
    obj->boxX2 = boxX2;
    obj->boxY2 = boxY2;

}

// Old draw code - maybe useful somewhere else? Main game loop uses new code
void drawObj(gobj_t *player){
    uint8_t i;
    uint8_t j;

    // before we do anything, we check if the object is active:
    if (player->active){

        // go to origin
        gotoxy(player->x, player->y);

        for (i = 0; i < GRAPH_SIZE; i++){
            for (j = 0; j < GRAPH_SIZE; j++){

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

void writeToUpdateBuffer(gobj_t *obj, uint8_t upBuffer[WIDTH][HEIGHT]){
   uint8_t i;
   uint8_t j;

    // Should be called every time we update the logic
    // The contents of this buffer is what we want to draw to screen (or the "playfield").
    // We update it with graphics from the sheet relative to structs placement on the playfield
    // If the struct somehow moves outside the playfield, ugly things will happen!
    // TODO: (Maybe make security checks then?)

    if (obj->active){

        for (i = 0; i < GRAPH_SIZE; i++){
            for (j = 0; j < GRAPH_SIZE; j++){

                // First index in sheet is the player image value
                // the two others are for the 2d graphics
                if (graph[obj->img][j][i] != 0){

                    // The graphics in the graphicssheet is rotated by 90 degrees
                    // Thats why we rotate it back by switching i and j
                    upBuffer[i + obj->x][j + obj->y] = graph[obj->img][j][i];
                }
            }
        }
    }
}

void drawFromBuffer(uint8_t upBuffer[WIDTH][HEIGHT], uint8_t scrBuffer[WIDTH][HEIGHT]){

   uint8_t i;
   uint8_t j;
    // Should only be called when drawing graphics!
    //We compare what we want to draw to the screen/playfield (upBuffer) with what is already
    //drawn to the screen (scrBuffer). If there is a difference, then call gotoxy and update scrBuffer
    //with contents of upBuffer

    for (i = 0; i < WIDTH; i++){
            for (j = 0; j < HEIGHT; j++){

                // Compares if there is a difference
                if(!(upBuffer[i][j] == scrBuffer[i][j])){
                        // If yes, then draw.
                        //I have added a offset to Gotoxy to control where on screen
                        //we want to draw the playfield.
                        gotoxy(i + 8, j + 8);
                        printf("%c", upBuffer[i][j]);
                        // Update scrBuffer:
                        scrBuffer[i][j] = upBuffer[i][j];
                }
            }
    }
}

uint8_t checkCollision(gobj_t *obj1, gobj_t *obj2){

    if (obj1->active && obj2->active){
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
    }
    // else return false:
    return(0);
}

void updateEnemy(gobj_t enemy[]){
    uint8_t i;

    for (i = 0; i < ENEMY_POOL; i++){
        if(enemy[i].active){

            // Checks if laser is out of bounds
            if(!boundaryCheck(WIDTH, HEIGHT, enemy[i].x, enemy[i].y + enemy[i].speed)) {
                enemy[i].y += enemy[i].speed;
            } else {
            // if its out of bounds, set it to inactive
            enemy[i].active = 0;
            }
        }
    }
}

void enemyHandler(gobj_t enemy[]){
    if (!(enemy[0].active)){
            initObj(&enemy[0], 10, 2, 1, 2, 1, 1, 1, 4, 4);
    }
}

