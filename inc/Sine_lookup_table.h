#include "30010_io.h"

#ifndef SINE_LOOKUP_TABLE_H
#define SINE_LOOKUP_TABLE_H
#define FIX14_SHIFT 14
#define FIX14_MULT(a, b) ( (a)*(b) >> FIX14_SHIFT )
#define FIX14_DIV(a, b) ( ((a) << FIX14_SHIFT) / b )

// === LUT SIZES ===
#define SIN_SIZE 512

// === LUT DECLARATIONS ===
extern const signed short SIN[512];

typedef struct {
    int32_t x,y;
} vector_t;

void printFix(int32_t i);

int32_t expand(int32_t i);

int sinn(int i);

int coss(int i);

void initVector(vector_t *v, int32_t x, int32_t y);

void rotate(vector_t *v, int32_t angle);

#endif	// SINE_LOOKUP_TABLE_H
