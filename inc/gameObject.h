#ifndef GOBJ_H
#define GOBJ_H
#include "30010_io.h" // Input/output library for this course


typedef struct gobj_t{
    uint16_t x; // x position in floating point 8.8 (remember to shift >> 4 when using this number!)
    uint16_t y; // y position in floating point 8.8
    int16_t speed; // speed in floating point 8.8 *IMPORTANT* must be signed

    // graphic
    uint8_t img;

    //flags
    uint8_t active;

    int8_t health; // set to a signed value to allow a small buffer to prevent overflow

    //Collison bounds:
    uint16_t boxX1;
    uint16_t boxY1;
    uint16_t boxX2;
    uint16_t boxY2;


} gobj_t;

#endif
