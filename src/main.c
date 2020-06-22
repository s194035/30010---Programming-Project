#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "ansi.h"
#include "pin_io.h"
#include "lcd.h"
#include "time.h"
#include "updateships.h"
#include <string.h>
#include "charset.h"
#include "gameLoop.h"


int main()
{
    uart_init(115200);
    ioConfig();
    ledsetup();
    // temp variable
    uint8_t settings = 1;

    gameLoop(settings);

    while(1){};

}
