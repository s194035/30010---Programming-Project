#ifndef ANSI_H
#define ANSI_H
#define ESC 0x1B
#include "stm32f30x_conf.h"
#include "30010_io.h"
#include "string.h"

void fgcolor(uint8_t foreground);

void bgcolor(uint8_t background);

void color(uint8_t foreground, uint8_t background);

void resetbgcolor();

void clrscr();

void clreol();

void gotoxy(int x, int y);

void underline(uint8_t on);

void blink(uint8_t on);

void inverse(uint8_t on);

void title(int x, int y, char text[]);

//void box(int x1, int y1, int x2, int y2);

void window(int x1, int y1, int x2, int y2, char text[], char style);

#endif // ANSI_H
