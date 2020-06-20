#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "ansi.h"
#include "pin_io.h"
#include "lcd.h"
#include "time.h"
#include "spaceShip.h"
#include "updateships.h"
#include <string.h>

#define MAX_C_GRAPH 40
#define MAX_C_UPDATERATE 20

static uint32_t checkCount = 0; //This counter will overflow after 44 hours! At that point, the gameloop breaks.

void TIM2_IRQHandler(void){

    checkCount ++;
    TIM2->SR &= ~0x0001; // Clear interrupt bit
}


int main()
{
    ///////////////////////////// initialize everything /////////////////////////////////
    uart_init(115200);
    uint8_t i;
    // variables to save a point in time.
    uint32_t midTime1 = 0;
    uint32_t midTime2 = 0;

    // Handles graphic drawing in the playfield
    uint8_t pfBuffer[WIDTH][HEIGHT];
    uint8_t pfUpdate[WIDTH][HEIGHT];
    // reset playfield buffers - sets all chars to space (32), which clears playfield.
    memset(pfBuffer, 00, sizeof(pfBuffer));
    memset(pfUpdate, 32, sizeof(pfUpdate));

    setupTimer();
    startTimer();

    // create a pool of gameobject structs for use in the game
    gobj_t player;
    gobj_t enemy0, enemy1, enemy2, enemy3, enemy4, enemy5;
    gobj_t enemyArray[ENEMY_POOL] = {enemy0, enemy1, enemy2, enemy3, enemy4, enemy5};
    gobj_t laser0, laser1, laser2, laser3, laser4, laser5;
    gobj_t laserArray[LASER_POOL] = {laser0, laser1, laser2, laser3, laser4, laser5};

    initObj(&player, WIDTH/2, HEIGHT/2, 1, 0, 1, 1, 1, 4, 4); // initialize player. TODO: for the love of god, define par's as constants!

    for (i = 0; i < LASER_POOL; i++){
            initObj(&laserArray[i], 0, 0, 0, 1, 0, 2, 0, 3, 4); // initialize all lasers
    }
    for (i = 0; i < ENEMY_POOL; i++){
            initObj(&enemyArray[i], 0, 0, 0, 2, 0, 1, 1, 4, 4); // initialize all lasers
    }

    ///////////// Game loop //////////////

    //draw border
    box(PF_OFF_X-1, PF_OFF_Y-1, PF_OFF_X + WIDTH, PF_OFF_Y + HEIGHT);

    while(1){

        // Timer to update logic
        if ((checkCount - midTime1) > MAX_C_UPDATERATE){

            enemyHandler(enemyArray);

            updatePlayer(&player, laserArray);
            updateLaser(laserArray);
            updateEnemy(enemyArray);

            //sets new relative point
            midTime1 = checkCount;
        }

        // timer to update graphics
        if (checkCount - midTime2 > MAX_C_GRAPH){

            // draw lasers and player
            writeToUpdateBuffer(&player,pfUpdate);
            writeToUpdateBuffer(&enemyArray[0], pfUpdate);

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
