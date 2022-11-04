#include "stm32f30x_conf.h"
#include "stm32f30x.h"
#include "30010_io.h"
#include "ansi.h"
#include "time.h"

// timer code with interrupt function

void setupTimer(){
    RCC->APB1ENR |= RCC_APB1Periph_TIM2; // Enable clock line to timer 2;
    TIM2->CR1 = 0x0001; // Configure timer 2
    TIM2->ARR = 0xF6FF; // Set reload value
    TIM2->PSC = 0x0000; // Set prescale value
    TIM2->DIER |= 0x0001; // Enable timer 2 interrupts
    NVIC_SetPriority(TIM2_IRQn, 0); // Set interrupt priority
    NVIC_EnableIRQ(TIM2_IRQn); // Enable interrupt
}

void startTimer(){
    TIM2->SR |= 0x0001;
}


