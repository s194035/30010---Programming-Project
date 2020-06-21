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

    // clear input buffer to avoid sticky inputs
    uart_clear();
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

void writeBgToBuffer(uint8_t img, uint8_t x, uint8_t y, uint8_t flip, uint8_t upBuffer[WIDTH][HEIGHT]){
   int8_t i;
   int8_t j;

    // general way of drawing static graphic such as the background
    // supports flipping the image
    // flip = 0: normal, flip = 1: flip on x-axis, flip = 2: flip on y-axis, flip = 3: flipped on both axis.

    if (flip == 0){

        for (i = 0; i < GRAPH_SIZE; i++){
            for (j = 0; j < GRAPH_SIZE; j++){

                if (graph[img][j][i] != 0){

                    upBuffer[i + x][j + y] = graph[img][j][i];
                }
            }
        }
        return;
    }
    if (flip == 1){

        for (i = 0; i < GRAPH_SIZE; i++){
            for (j = 0; j < GRAPH_SIZE; j++){

                if (graph[img][j][GRAPH_SIZE - 1 - i] != 0){

                    upBuffer[i + x][j + y] = graph[img][j][GRAPH_SIZE - 1 - i];
                }
            }
        }
        return;
    }
    if (flip == 2){

        for (i = 0; i < GRAPH_SIZE; i++){
            for (j = 0; j < GRAPH_SIZE; j++){

                if (graph[img][GRAPH_SIZE - 1 - j][i] != 0){

                    upBuffer[i + x][j + y] = graph[img][GRAPH_SIZE - 1 - j][i];
                }
            }
        }
        return;
    }
    if (flip == 3){

        for (i = 0; i < GRAPH_SIZE; i++){
            for (j = 0; j < GRAPH_SIZE; j++){

                if (graph[img][i][j] != 0){

                    upBuffer[i + x][j + y] = graph[img][i][j];
                }
            }
        }
        return;
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

                        // read the last four bits
                       // fgcolor((upBuffer[i][j] & 0xf0) >> 4);

                        gotoxy(i + PF_OFF_X, j + PF_OFF_Y);
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
    static uint8_t timer = 0;
    uint8_t i;

    for(i=0; i < ENEMY_POOL; i++){
        if (!(enemy[i].active) && timer % i == 0){
            initObj(&enemy[i], 10 + i*2, 2, 1, 2, 1, 1, 1, 4, 4);
            break;
        }
    timer++;
    }
}
