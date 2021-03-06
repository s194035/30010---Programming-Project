#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ansi.h"
#include "pin_io.h"
#include "lcd.h"
#include "gameLoop.h"
#include "gameScreen.h"

int main()
{
    uart_init(115200);
    ioConfig();
    ledsetup();
    lcd_init();
    JoystickSetup();
    // temp variable
    uint8_t settings;
    uint16_t highScore[10] = {0,0,0,0,0,0,0,0,0,0};

    while(1){
        settings = mainMenu(highScore);
        clrscr();
        highScore[9] = gameLoop(settings);
        clrscr();
    };
}
