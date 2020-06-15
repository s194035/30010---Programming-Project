#include "spaceShip.h"

void initSpaceShip(SpaceShip_t *ship, uint8_t speed, uint8_t x0, uint8_t y0){
    ship->pos.x = x0;
    ship->pos.y = y0;
    ship->speed = speed;
}

void drawSpaceShip(SpaceShip_t *ship){
    char solidBox = 219;
    char str[10];
    int i;
    for(i = 0; i < 9; i++){
        str[i] = solidBox;
    }
    str[9] = 0;
    gotoxy(ship->pos.x, ship->pos.y);
    printf("%s",str);
}
