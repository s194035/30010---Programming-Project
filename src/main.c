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
#include "time.h"

static uint16_t updateLCD;

void TIM2_IRQHandler(void){

    updateLCD++;
    TIM2->SR &= ~0x0001; // Clear interrupt bit
}

int main(void)
{
 uart_init( 115200 );



 setupTimer();
 startTimer();

    updateLCD = 0;
 uint8_t buffer[512];
 memset(buffer, 0x00, 512);
 lcd_init();
 lcd_write_string(buffer, "Goddag og jfdkslafdsafdasklfdjskal", 1, 1);


 while(1) {


     if (updateLCD >= 100){
         lcd_scroll_left(buffer);
         lcd_update(buffer);
         updateLCD = 0;
     }


     printf("%d\n",updateLCD);
    }
}

