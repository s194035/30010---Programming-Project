#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "Sine_lookup_table.h"
#include "ball.h"
#include "ansi.h"
#include "pin_io.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "charset.h"
#include "lcd.h"


int main(void)
{
 ioConfig();
 uint8_t a;
 ledsetup();


 while(1) {
    a = readJoystick();
    printf("%d\n",a);
    ledJoystick();
}
}
