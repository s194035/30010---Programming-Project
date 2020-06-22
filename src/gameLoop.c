#include "gameLoop.h"

uint32_t checkCount = 0;

//Interrupt handler
void TIM2_IRQHandler(void){

    checkCount ++;
    TIM2->SR &= ~0x0001; // Clear interrupt bit
}

// the biggest, meanest function
// main game loop
void gameLoop(uint8_t settings){

    ///////////////////////////// initialize everything /////////////////////////////////
    uint8_t i;
    uint8_t j;
    // variables to save a point in time.
    uint32_t midTime1 = 0;
    uint32_t midTime2 = 0;

    // Handles graphic drawing in the playfield
    uint8_t pfBuffer[WIDTH_PF][HEIGHT_PF];
    uint8_t pfUpdate[WIDTH_PF][HEIGHT_PF];
    // reset playfield buffers - sets all chars to space (32), which clears playfield.
    memset(pfBuffer, 00, sizeof(pfBuffer));
    memset(pfUpdate, 32, sizeof(pfUpdate));

    setupTimer();
    startTimer();

    // create a pool of gameobject structs for use in the game
    gobj_t player;
    gobj_t enemy0, enemy1, enemy2, enemy3, enemy4, enemy5, enemy6, enemy7,
           enemy8, enemy9, enemy10, enemy11, enemy12, enemy13, enemy14, enemy15;
    gobj_t enemyArray[ENEMY_POOL] = {enemy0, enemy1, enemy2, enemy3, enemy4, enemy5, enemy6, enemy7,
                                     enemy8, enemy9, enemy10, enemy11, enemy12, enemy13, enemy14, enemy15};
    gobj_t laser0, laser1, laser2, laser3, laser4, laser5;
    gobj_t laserArray[LASER_POOL] = {laser0, laser1, laser2, laser3, laser4, laser5};

    initObj(&player, WIDTH_PF/2, HEIGHT_PF/2, 1, 0, 1, 1, 1, 4, 4); // initialize player. TODO: for the love of god, define par's as constants!

    for (i = 0; i < LASER_POOL; i++){
            initObj(&laserArray[i], 0, 0, 0, 1, 0, 2, 0, 3, 4); // initialize all lasers
    }
    for (i = 0; i < ENEMY_POOL; i++){
            initObj(&enemyArray[i], 0, 0, 0, 2, 0, 1, 1, 4, 4); // initialize all lasers
    }

    ////////////////////////////////////////// Game loop ///////////////////////////////////////////////

    //draw border
    box2(PF_OFF_X-1, PF_OFF_Y-1, PF_OFF_X + WIDTH_PF, PF_OFF_Y + HEIGHT_PF);

    while(1){

        // Timer to update logic
        if ((checkCount - midTime1) > MAX_C_UPDATERATE){

            enemyHandler(enemyArray, settings);

            //updates all gameobjects:
            updatePlayer(&player, laserArray);
            updateLaser(laserArray);
            updateEnemy(enemyArray);
            // check for collision:


            for (i=0; i < LASER_POOL; i++){
                for (j=0; j < ENEMY_POOL; j++){
                    if (checkCollision(&laserArray[i], &enemyArray[j])){
                        enemyArray[j].active = 0;
                        laserArray[i].active = 0;
                    }
                }
            }

            //sets new relative point
            midTime1 = checkCount;
        }

        //////////////////// timer to update graphics ///////////////////////
        if (checkCount - midTime2 > MAX_C_GRAPH){

            // draw bg:
            drawBackground(pfUpdate);
            // draw player
            writeToUpdateBuffer(&player,pfUpdate);
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

            //Sets new relative point
            midTime2 = checkCount;
        }
    }
}
