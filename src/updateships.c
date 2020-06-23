#include "updateships.h"

uint8_t boundaryCheck(uint8_t w, uint8_t h, uint16_t x, uint16_t y){

    // since all x,y coordinates are in 8.8, we have to remember to shift to the right:
    if ((x >> FIX8_shift)  < 0 || WIDTH_PF - GRAPH_SIZE < (x >> FIX8_shift) || (y >> FIX8_shift) < 0 || HEIGHT_PF - GRAPH_SIZE < (y >> FIX8_shift)){
            return 1; // graphics outside boundary
    }
    return 0; // else return 0
}

void spawnLaser(gobj_t *player, gobj_t *laser){

uint8_t i;

// Cycle the list for active objects
    for (i = 0; i < LASER_POOL; i++){
        if (!(laser[i].active)){
            laser[i].x = player->x; // fixed point to fixed point, so no bitshift required
            laser[i].y = player->y;
            laser[i].speed = LASER_SPEED;
            laser[i].active = 1;
            break;
        }
    }
    // if all lasers are active, then don't shoot any
}

void updatePlayer(gobj_t *player, gobj_t laser[]){

    if (player->active){

        uint16_t tempx = player->x;
        uint16_t tempy = player->y;
        int16_t tempspeed = player->speed;

        char controlChar = uart_get_char();

        // x position
        if (controlChar == 'd'){

                if (!boundaryCheck(WIDTH_PF, HEIGHT_PF, (tempx + tempspeed), tempy)){
                    tempx += tempspeed;
                    setLed(0,0,0);
                    LedPinSetup(9,'A',0);
                }
        }
        if (controlChar == 'a'){

                if(!(boundaryCheck(WIDTH_PF, HEIGHT_PF, tempx - tempspeed, tempy)))
                tempx -= tempspeed;
                setLed(0,0,0);
                LedPinSetup(7,'C',0);
        }

        // y position
        if (controlChar == 'w'){

                if(!boundaryCheck(WIDTH_PF, HEIGHT_PF, tempx, tempy - tempspeed))
                tempy -= tempspeed;
                setLed(0,0,0);
                LedPinSetup(4,'B',0);
        }
        if (controlChar == 's'){

                if(!boundaryCheck(WIDTH_PF, HEIGHT_PF, tempx, tempy+tempspeed))
                tempy += tempspeed;
                LedPinSetup(7,'C',0);
                LedPinSetup(4,'B',0);
        }

        // shoot
        if (controlChar == 32){
                spawnLaser(player, laser);
        }
        player->x = tempx;
        player->y = tempy;

        // clear input buffer to avoid sticky inputs
        uart_clear();
    }
}

void updateLaser(gobj_t laser[]){
    uint8_t i;

    for (i = 0; i < LASER_POOL; i++){
        if(laser[i].active){

            // Checks if laser is out of bounds
            if(!boundaryCheck(WIDTH_PF, HEIGHT_PF, laser[i].x, laser[i].y + laser[i].speed)) {
                laser[i].y += laser[i].speed;
            } else {
            // if its out of bounds, set it to inactive
            laser[i].active = 0;
            }
        }
    }
}

void initObj(gobj_t *obj, uint16_t startx, uint16_t starty, int16_t speed, uint8_t img, uint8_t active, int8_t health,
             uint16_t boxX1, uint16_t boxY1, uint16_t boxX2, uint16_t boxY2){

    // start position and speed
    obj->x = startx;
    obj->y = starty;
    obj->speed = speed;

    // img
    obj->img = img;

    // active
    obj->active = active;
    obj->health = health;

    // set bounding box
    obj->boxX1 = boxX1;
    obj->boxY1 = boxY1;
    obj->boxX2 = boxX2;
    obj->boxY2 = boxY2;

}

void writeToUpdateBuffer(gobj_t *obj, uint8_t upBuffer[WIDTH_PF][HEIGHT_PF]){
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
                    // remember fixed point notation! shift by 8 to the right
                    upBuffer[i + (obj->x >> FIX8_shift)][j + (obj->y >> FIX8_shift)] = graph[obj->img][j][i];
                }
            }
        }
    }
}

void writeBgToBuffer(uint8_t img, uint8_t x, uint8_t y, uint8_t flip, uint8_t upBuffer[WIDTH_PF][HEIGHT_PF]){
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

void drawBackground(uint8_t upBuffer[WIDTH_PF][HEIGHT_PF]){
// Function to collect all calls to WriteBgToBuffer, so it doesn't clutter the gameloop:

            writeBgToBuffer(13, 0, 0, 2, upBuffer);
            writeBgToBuffer(13, 5, 0, 3, upBuffer);
            writeBgToBuffer(13, 10, 0, 0, upBuffer);
            writeBgToBuffer(14, 0, 5, 0, upBuffer);
            writeBgToBuffer(13, 5, 5, 1, upBuffer);
            writeBgToBuffer(13, 10, 5, 3, upBuffer);
            writeBgToBuffer(15, 15, 5, 1, upBuffer);
            writeBgToBuffer(13, 15, 0, 1, upBuffer);
            writeBgToBuffer(14, 20, 0, 3, upBuffer);
            writeBgToBuffer(14, 24, 0, 3, upBuffer);
            writeBgToBuffer(14, 24, 5, 1, upBuffer);
            writeBgToBuffer(13, 28, 0, 3, upBuffer);
            writeBgToBuffer(14, 33, 0, 3, upBuffer);
            writeBgToBuffer(14, 37, 0, 3, upBuffer);
            writeBgToBuffer(15, 37, 5, 0, upBuffer);
            writeBgToBuffer(13, 41, 0, 0, upBuffer);
            writeBgToBuffer(13, 41, 5, 1, upBuffer);
            writeBgToBuffer(14, 41, 10, 0, upBuffer);
            writeBgToBuffer(13, 45, 0, 0, upBuffer);
            writeBgToBuffer(14, 45, 5, 0, upBuffer);
            writeBgToBuffer(14, 7, 10, 0, upBuffer);
            writeBgToBuffer(14, 7, 10, 0, upBuffer);

            writeBgToBuffer(13, 45, 33, 0, upBuffer);
            writeBgToBuffer(14, 45, 38, 0, upBuffer);
            writeBgToBuffer(14, 41, 33, 2, upBuffer);
            writeBgToBuffer(14, 41, 29, 2, upBuffer);
            writeBgToBuffer(14, 0, 65, 3, upBuffer);
            writeBgToBuffer(14, 4, 65, 3, upBuffer);
            writeBgToBuffer(14, 0, 61, 3, upBuffer);
            writeBgToBuffer(14, 8, 68, 3, upBuffer);
            //Stars
            writeBgToBuffer(12, 31, 11, 0, upBuffer);
            writeBgToBuffer(12, 3, 17, 1, upBuffer);
            writeBgToBuffer(12, 46, 15, 0, upBuffer);
            writeBgToBuffer(12, 14, 28, 2, upBuffer);
            writeBgToBuffer(12, 36, 49, 3, upBuffer);
            writeBgToBuffer(12, 1, 40, 3, upBuffer);
            writeBgToBuffer(12, 37, 25, 2, upBuffer);

}

void drawFromBuffer(uint8_t upBuffer[WIDTH_PF][HEIGHT_PF], uint8_t scrBuffer[WIDTH_PF][HEIGHT_PF]){

   uint8_t i;
   uint8_t j;
    // Should only be called when drawing graphics!
    //We compare what we want to draw to the screen/playfield (upBuffer) with what is already
    //drawn to the screen (scrBuffer). If there is a difference, then call gotoxy and update scrBuffer
    //with contents of upBuffer

    for (i = 0; i < WIDTH_PF; i++){
            for (j = 0; j < HEIGHT_PF; j++){

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

    uint16_t obj1_boxX1 = (obj1->boxX1 << FIX8_shift);
    uint16_t obj1_boxY1 = (obj1->boxY1 << FIX8_shift);
    uint16_t obj1_boxX2 = (obj1->boxX2 << FIX8_shift);
    uint16_t obj1_boxY2 = (obj1->boxY2 << FIX8_shift);

    uint16_t obj2_boxX1 = (obj2->boxX1 << FIX8_shift);
    uint16_t obj2_boxY1 = (obj2->boxY1 << FIX8_shift);
    uint16_t obj2_boxX2 = (obj2->boxX2 << FIX8_shift);
    uint16_t obj2_boxY2 = (obj2->boxY2 << FIX8_shift);

    if (obj1->active && obj2->active){
        // first we check for possible collision on x axis:
        // First statement is corner on each side of box
        // next two is each corner inside of box
        if ( (obj1_boxX1 + obj1->x <= obj2_boxX1 + obj2->x && obj2_boxX2 + obj2->x <= obj1_boxX2 + obj1->x) ||
             (obj2_boxX1 + obj2->x <= obj1_boxX1 + obj1->x && obj1_boxX1 + obj1->x <= obj2_boxX2 + obj2->x) ||
             (obj2_boxX1 + obj2->x <= obj1_boxX2 + obj1->x && obj1_boxX2 + obj1->x <= obj2_boxX2 + obj2->x) ){

            // Then we check for possible collision on y axis:
            if ( (obj1_boxY1 + obj1->y <= obj2_boxY1 + obj2->y && obj2_boxY2 + obj2->y <= obj1_boxY2 + obj1->y) ||
                 (obj2_boxY1 + obj2->y <= obj1_boxY1 + obj1->y && obj1_boxY1 + obj1->y <= obj2_boxY2 + obj2->y) ||
                 (obj2_boxY1 + obj2->y <= obj1_boxY2 + obj1->y && obj1_boxY2 + obj1->y <= obj2_boxY2 + obj2->y) ){

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
            if(!boundaryCheck(WIDTH_PF, HEIGHT_PF, enemy[i].x, enemy[i].y + enemy[i].speed)) {
                enemy[i].y += enemy[i].speed;
            } else {
            // if its out of bounds, set it to inactive
            enemy[i].active = 0;
            }
        }
    }
}

void enemyHandler(gobj_t enemy[], uint8_t difficulty){
    static uint8_t timeline_index = 0;
    static uint8_t formation_index = 0;
    static uint8_t timer = 0;
    uint8_t i;
    uint8_t flag_breakloop;
    uint8_t *formptr; // for ref the formation
    uint8_t formlength; // represents formation length
    uint8_t pos; // position in formation
    uint16_t time = 0; // wait time in formation
    uint8_t offsetPos; //set by the timeline to offset formations

    ////////////////////////////////////// timeline decelerations ///////////////////////////////
    uint8_t time0Length = 7;
    uint16_t timeline0[7] = {0x0004, 0x0002, 0x0005, 0x0005, 0x0002, 0x0304, 0x0000};

    ///////////////////////////////////// formations decelerations ////////////////////////////////
    uint8_t form1[1] = {0x10}; // wait till screen is clear;
    uint8_t form2[1] = {0x04}; // wait till half the screen is clear;
    uint8_t form3[1] = {0x40}; // single enemy at pos 0;
    uint8_t form4[5] = {0x41, 0x01, 0x40, 0x42, 0x01}; // triangle formation of 3;
    uint8_t form5[8] = {0x42, 0x01, 0x41, 0x43, 0x01, 0x40, 0x44, 0x01}; // triangle formation of 5;
    uint8_t form6[7] = {0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x01}; // horizontal line formation of 5;
    uint8_t form7[10] = {0x40, 0x01, 0x40, 0x01, 0x40, 0x01, 0x40, 0x01, 0x40, 0x01}; // vertical line formation of 5
    // first we read parameters from the timeline entry:
    // Offset position [11:8]: offset the formation by this much:
    offsetPos = ((timeline0[timeline_index] & 0x0F00) >> 8);
    offsetPos *= GRAPH_SIZE;
    // then we choose which formation to create from bits [7:0]
    // if bits [7:0] = 0x00 then the timeline will always stop reading and return to gameloop
    switch(timeline0[timeline_index] & 0x00FF){

        case 0:
            return;

        case 1:
            formptr = form1;
            formlength = sizeof(form1)/sizeof(form1[0]);
            break;

        case 2:
            formptr = form2;
            formlength = sizeof(form2)/sizeof(form2[0]);
            break;

        case 3:
            formptr = form3;
            formlength = sizeof(form3)/sizeof(form3[0]);
            break;

        case 4:
            formptr = form4;
            formlength = sizeof(form4)/sizeof(form4[0]);
            break;

        case 5:
            formptr = form5;
            formlength = sizeof(form5)/sizeof(form5[0]);
            break;

        case 6:
            formptr = form6;
            formlength = sizeof(form6)/sizeof(form6[0]);
            break;

        case 7:
            formptr = form7;
            formlength = sizeof(form7)/sizeof(form7[0]);
            break;
        }

    // when that is done, we can work with the contents of the formation:
    while(formation_index < formlength) {

            // read this as a time event [7:6] = 00
            if((formptr[formation_index] & 0xC0) >> 6 == 0){
                // read wait time from [5:0]. The wait time have been multiplied by graphic size
                // So enemies are spaced out by sprite size;
                time = (formptr[formation_index] & 0x3F);
                time *= GRAPH_SIZE;

                if(time > timer){
                    // if the wait requirement hasent been met, then return.
                    timer++;
                    return;

                } else {
                    //reset timer and continue
                    timer = 0;
                }

            // read this as a spawn event [7:6] = 01
            } else if((formptr[formation_index] & 0xC0) >> 6 == 1){

                // read position from bits [3:0]
                // the position increments by graphic size (5);
                pos = (formptr[formation_index] & 0x0F);
                pos *= GRAPH_SIZE;
                // read enemy ship type form bits [5:4];
                // there is only one type, so the bits is never read is never used :,(

                // look for ship to spawn
                flag_breakloop = 1; // this flag breaks the for-loop early when 0
                for (i=0; i < ENEMY_POOL && flag_breakloop; i++){

                        if (!enemy[i].active){
                            // remember x and y are in fixed point so shift to the LEFT to get fixed point 8.8
                            initObj(&enemy[i], (pos + offsetPos) << FIX8_shift, 0, ENEMY_SPEED, 2, SET_ACTIVE, ENEMY_HEALTH, ENEMY_BBOX_XY1, ENEMY_BBOX_XY1, ENEMY_BBOX_XY2, ENEMY_BBOX_XY2);
                            flag_breakloop = 0;
                    }
                }
            }
            formation_index++;
        }
        // finally we check if we are finished reading the formation, and increments
        // timeline index (but only if it doesnt overflow the timeline!)
        if ((formation_index <= formlength) && (timeline_index < time0Length)){
            timeline_index++;
            formation_index = 0; // reset formation index when we are done
            timer = 0;
        }
}
