#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "30010_io.h"
#include "stm32f30x_conf.h"
#include "ansi.h"
#include "Sine_lookup_table.h"

typedef struct{
    vector_t pos;
    uint8_t speed;
} SpaceShip_t;

#endif
