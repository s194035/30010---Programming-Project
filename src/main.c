#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "Sine_lookup_table.h"
#include "ball.h"
#include "ansi.h"
#include "pin_io.h"
#include "charset.h"
#include "lcd.h"
#include "time.h"
#include "spaceShip.h"


int main(void)
{
    uart_init(115200);
    lcd_init();

    uint8_t *buffer[512];
    memset(buffer, 0x00, 512);
    lcd_face_six(buffer);
    lcd_push_buffer(buffer);




 while(1) {}
}

