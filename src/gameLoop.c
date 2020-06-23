#include "gameLoop.h"

//static uint32_t checkCount = 0;

//Interrupt handler
void TIM2_IRQHandler(void){

    checkCount ++;
    TIM2->SR &= ~0x0001; // Clear interrupt bit
}

uint8_t choice(){

    char controlChar;
    uint8_t choice = 1;

    while (1){

        controlChar = uart_get_char();
        switch(choice){

            case 0: // if end
                if (controlChar == 'w'){
                    choice++;
                    // print over choice
                    moveCursorUp(100, 82);
                }
                break;

            case 1: // if continue
                if (controlChar == 's'){
                    choice--;
                    // print over choice
                   moveCursorDown(100, 80);
                }
                break;
        }
        if (controlChar == 13){
            return(choice);
        }
    }
}

uint8_t pause(){
    // pauses the game and returns gameRunning as 0 or 1 based on the answer:
    printPauseScreen();
    return(choice());
}

uint8_t gameOver (gobj_t playerArray[], gobj_t enemyArray[], gobj_t laserArray[], uint16_t *score){

    uint8_t i;

    printGameOverScreen(score);

    if (choice()){
        // init player
        initObj(&playerArray[0], ((WIDTH_PF/2) << FIX8_shift), ((HEIGHT_PF-8) << FIX8_shift), PLAYER_SPEED, 0, SET_ACTIVE, PLAYER_START_HEALTH, PLAYER_BBOX_XY1, PLAYER_BBOX_XY1, PLAYER_BBOX_XY2, PLAYER_BBOX_XY2); // initialize player.
        initObj(&playerArray[1], ((WIDTH_PF/2) << FIX8_shift), ((HEIGHT_PF-16) << FIX8_shift), PLAYER_SPEED, 0, SET_INACTIVE, PLAYER_START_HEALTH, PLAYER_BBOX_XY1, PLAYER_BBOX_XY1, PLAYER_BBOX_XY2, PLAYER_BBOX_XY2);
        // set all objects to inactive
        // note: I now the biggest pool of all is the enemypool. Should probably check for biggest pool
        for (i=0; i < ENEMY_POOL; i++){
                if (i < LASER_POOL){
                        laserArray[i].active = 0;
                }
                if (i < ENEMY_POOL){
                        enemyArray[i].active = 0;
                }
        // reset score:
        *score = 0;
        }

        return(1);
    }

    // else end the game
    return(0);
}

uint8_t wonLevel(uint8_t *difficulty){

    printWinScreen(difficulty);
    if (choice()){
            // increment difficulty if you won the level
        if (*difficulty <= 3){
            *difficulty++;

            return(1);
        }
    }

    return(0);
}

// the biggest, meanest function
// main game loop
uint16_t gameLoop(uint8_t settings){

    ///////////////////////////// initialize everything /////////////////////////////////
    uint8_t i;
    uint8_t j;
    // variables to save a point in time and handle flow:
    uint32_t midTime1 = 0;
    uint32_t midTime2 = 0;
    uint16_t delay; // update dependent timer
    uint8_t gameRunning = 1; // whether the game should be running or not:
    uint8_t difficulty = (settings & 0x0f); // chosen difficulty
    uint8_t playerNum = (settings & 0xf0) >> 4; // number of players
    // score
    uint16_t score = 0;
    // Handles graphic drawing in the playfield
    uint8_t pfBuffer[WIDTH_PF][HEIGHT_PF];
    uint8_t pfUpdate[WIDTH_PF][HEIGHT_PF];
    // reset playfield buffers - sets all chars to space (32), which clears playfield.
    memset(pfBuffer, 00, sizeof(pfBuffer));
    memset(pfUpdate, 32, sizeof(pfUpdate));

    // Setup LCD
    uint8_t LCDbuffer[512];
    memset(LCDbuffer, 0x00, 512);
    // control the LCD face
    uint8_t faceAnim = 0; // face animation to play
    uint8_t faceCount = 0; // timer to keep count of face animation

    // setup interrupts
    setupTimer();
    startTimer();

    // create a pool of gameobject structs for use in the game

    gobj_t player0, player1;
    gobj_t playerArray[PLAYER_POOL] = {player0, player1};

    gobj_t enemy0, enemy1, enemy2, enemy3, enemy4, enemy5, enemy6, enemy7,
           enemy8, enemy9, enemy10, enemy11, enemy12, enemy13, enemy14, enemy15;
    gobj_t enemyArray[ENEMY_POOL] = {enemy0, enemy1, enemy2, enemy3, enemy4, enemy5, enemy6, enemy7,
                                     enemy8, enemy9, enemy10, enemy11, enemy12, enemy13, enemy14, enemy15};

    gobj_t laser0, laser1, laser2, laser3, laser4, laser5;
    gobj_t laserArray[LASER_POOL] = {laser0, laser1, laser2, laser3, laser4, laser5};

    // initialize all the gameobjects
    initObj(&playerArray[0], ((WIDTH_PF/2) << FIX8_shift), ((HEIGHT_PF-8) << FIX8_shift), PLAYER_SPEED, 0, SET_ACTIVE, PLAYER_START_HEALTH, PLAYER_BBOX_XY1, PLAYER_BBOX_XY1, PLAYER_BBOX_XY2, PLAYER_BBOX_XY2);
    initObj(&playerArray[1], ((WIDTH_PF/2) << FIX8_shift), ((HEIGHT_PF-16) << FIX8_shift), PLAYER_SPEED, 0, SET_INACTIVE, PLAYER_START_HEALTH, PLAYER_BBOX_XY1, PLAYER_BBOX_XY1, PLAYER_BBOX_XY2, PLAYER_BBOX_XY2);

    // if two players, then set player 2 to active:
    if (playerNum > 1){
        playerArray[1].active = 1;
    }

    for (i = 0; i < LASER_POOL; i++){
            initObj(&laserArray[i], 0, 0, 0, 1, SET_INACTIVE, LASER_HEALTH, LASER_BBOX_x1, LASER_BBOX_Y1, LASER_BBOX_X2, LASER_BBOX_Y2); // initialize all lasers
    }
    for (i = 0; i < ENEMY_POOL; i++){
            initObj(&enemyArray[i], 0, 0, 0, 2, SET_INACTIVE, ENEMY_HEALTH, ENEMY_BBOX_XY1, ENEMY_BBOX_XY1, ENEMY_BBOX_XY2, ENEMY_BBOX_XY2); // initialize all enemies
    }

    // just as a safety measure, we reset the enemy handler:
    enemyHandler(enemyArray, &difficulty, 1, &gameRunning);

     //draw border
    box2(PF_OFF_X-1, PF_OFF_Y-1, PF_OFF_X + WIDTH_PF, PF_OFF_Y + HEIGHT_PF);

    ////////////////////////////////////////// Game loop ///////////////////////////////////////////////
    while(gameRunning){

        // Timer to update logic
        if ((checkCount - midTime1) > MAX_C_UPDATERATE){

            enemyHandler(enemyArray, &difficulty, 0, &gameRunning);

            //updates all gameobjects:
            updatePlayer(&playerArray[0], laserArray, &gameRunning);
            updatePlayer2(&playerArray[1], laserArray);

            updateLaser(laserArray);
            updateEnemy(enemyArray);

            // check for collision between lasers and enemies
            for (i=0; i < LASER_POOL; i++){
                for (j=0; j < ENEMY_POOL; j++){
                    if (checkCollision(&laserArray[i], &enemyArray[j])){
                        enemyArray[j].active = 0;
                        laserArray[i].active = 0;
                        score += 100;
                    }
                }
            }
            // check for collision between players and enemies
            for (i=0; i < ENEMY_POOL; i++)
                for (j=0; j < PLAYER_POOL; j++){
                    if (checkCollision(&playerArray[j], &enemyArray[i])){
                        enemyArray[i].active = 0;
                        lcd_face_anim(1, &faceAnim, &faceCount);
                        // subtract life, but avoid underflow:
                        if (playerArray[0].health > 0){
                            playerArray[0].health--; // the two players share the same health pool
                        }
                }
            }

            // finally we check if we the players have any health yet:
            if (playerArray[0].health <= 0){
                // set both players to inactive
                playerArray[0].active = 0;
                playerArray[1].active = 0;
                delay++;
            }
            // if the gameover delay has run out, then call the function and reset enemyHandler
            if (delay >= 100 && !(playerArray[0].active) && !(playerArray[0].active)){
                enemyHandler(enemyArray, &difficulty, 1, &gameRunning);
                gameRunning = gameOver(playerArray,enemyArray, laserArray, &score);
                delay = 0;
            }

            //sets new relative point
            midTime1 = checkCount;
        }

        //////////////////// timer to update graphics ///////////////////////
        if (checkCount - midTime2 > MAX_C_GRAPH){

            // draw bg:
            drawBackground(pfUpdate);
            // draw players
            for (i = 0; i < (PLAYER_POOL); i++){
                writeToUpdateBuffer(&playerArray[i], pfUpdate);
            }
            // draw enemies
            for (i = 0; i < (ENEMY_POOL); i++){
                writeToUpdateBuffer(&enemyArray[i], pfUpdate);
            }
            // draw lasers
            for (i = 0; i < (LASER_POOL); i++){
                writeToUpdateBuffer(&laserArray[i], pfUpdate);
            }
            // draw contents of buffer
            drawFromBuffer(pfUpdate, pfBuffer);
            // Finally, reset the updateBuffer
            memset(pfUpdate, 32, sizeof(pfUpdate));
            // update LCD screen
            lcd_face_anim(0, &faceAnim, &faceCount);
            lcd_controller(LCDbuffer, playerArray[0].health, faceAnim);
            faceCount++;
            //Sets new relative point
            midTime2 = checkCount;
        }
    }
    return(score);
}

