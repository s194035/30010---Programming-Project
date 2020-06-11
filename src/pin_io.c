#include "stm32f30x_conf.h"


/*
*** moder:
********* 0 Input
********* 1 Output

*** puder:
********* 0 no-pull
********* 1 Pull-up
********* 2 Pull-down
*/
void pinSetup(uint16_t port, char portName, uint32_t moder, uint32_t puder){
    if(portName == 'A'){
        GPIOA->MODER &= ~(0x00000003 << (port * 2)); // Clear mode register
        GPIOA->MODER |= (moder << (port * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
        GPIOA->PUPDR &= ~(0x00000003 << (port * 2)); // Clear push/pull register
        GPIOA->PUPDR |= (puder << (port * 2)); // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)

        if(moder == 1){
            GPIOA->MODER &= ~(0x00000003 << (port * 2)); // Clear mode register
            GPIOA->MODER |=  (0x00000001 << (port * 2)); // Set mode register to input
            GPIOA->OTYPER &= ~(0x0001 << (port)); // Clear otype register
            GPIOA->OTYPER |= (0x0000 << (port)); // Set otype to output
            GPIOA->OSPEEDR &= (0x0000003 << (port*2)); // Clear Speed register
            GPIOA->OSPEEDR |= (0x0000002 << (port *2)); // Set speed to 2MHz
        }
    }
    else if(portName == 'B'){
        GPIOB->MODER &= ~(0x00000003 << (port * 2));
        GPIOB->MODER |= (moder << (port * 2));
        GPIOB->PUPDR &= ~(0x00000003 << (port * 2));
        GPIOB->PUPDR |= (puder << (port * 2));

        if(moder == 1){
            GPIOB->MODER &= ~(0x00000003 << (port * 2));
            GPIOB->MODER |=  (0x00000001 << (port * 2));
            GPIOB->OTYPER &= ~(0x0001 << (port));
            GPIOB->OTYPER |= (0x0000 << (port));
            GPIOB->OSPEEDR &= (0x0000003 << (port*2));
            GPIOB->OSPEEDR |= (0x0000002 << (port *2));
        }
    }
    else if(portName == 'C'){
        GPIOC->MODER &= ~(0x00000003 << (port * 2));
        GPIOC->MODER |= (moder << (port * 2));
        GPIOC->PUPDR &= ~(0x00000003 << (port * 2));
        GPIOC->PUPDR |= (puder << (port * 2));

        if(moder == 1){
            GPIOC->MODER &= ~(0x00000003 << (port * 2));
            GPIOC->MODER |=  (0x00000001 << (port * 2));
            GPIOC->OTYPER &= ~(0x0001 << (port));
            GPIOC->OTYPER |= (0x0000 << (port));
            GPIOC->OSPEEDR &= (0x0000003 << (port*2));
            GPIOC->OSPEEDR |= (0x0000002 << (port *2));
        }
    }
}


void ioConfig(){
    RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
    RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B
    RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C

    RCC->CFGR2 &= ~RCC_CFGR2_ADCPRE12; // Clear ADC12 prescaler bits
    RCC->CFGR2 |= RCC_CFGR2_ADCPRE12_DIV6; // Set ADC12 prescaler to 6
    RCC->AHBENR |= RCC_AHBPeriph_ADC12; // Enable clock for ADC12

    ADC1->CR = 0x00000000; // Clear CR register
    ADC1->CFGR &= 0xFDFFC007; // Clear ADC1 config register
    ADC1->SQR1 &= ~ADC_SQR1_L; // Clear regular sequence register 1

    ADC1->CR |= 0x10000000; // Enable internal ADC voltage regulator
    for (int i = 0 ; i < 1000 ; i++) {} // Wait for about 16 microseconds

    ADC1->CR |= 0x80000000; // Start ADC1 calibration
    while (!(ADC1->CR & 0x80000000)); // Wait for calibration to finish
    for (int i = 0 ; i < 100 ; i++) {} // Wait for a little while

    ADC1->CR |= 0x00000001; // Enable ADC1 (0x01 - Enable, 0x02 - Disable)
    while (!(ADC1->ISR & 0x00000001)); // Wait until ready
}





/*
Bit 0: Up
Bit 1: Down
Bit 2: Left
Bit 3: Right
Bit 4: Center
Bit 5-7: 0
*/

uint8_t readJoystick(){
    uint8_t x = 0x0000;

    x |= (GPIOA->IDR & (0x0001 << 4)) >> 4; //Up
    x |= (GPIOB->IDR & (0x0001 << 0)) << 1; // Down
    x |= (GPIOC->IDR & (0x0001 << 1)) << 1; // Left
    x |= (GPIOC->IDR & (0x0001 << 0)) << 3; // Right
    x |= (GPIOB->IDR & (0x0001 << 5)) >> 1; // Center

    return x;
}
// Setting up joystick utilizing pinSetup function above
void JoystickSetup(){
 pinSetup(1, 'C', 0, 1);
 pinSetup(5, 'B', 0, 1);
 pinSetup(0, 'B', 0, 1);
 pinSetup(0, 'C', 0, 1);
 pinSetup(4, 'A', 0, 1);
}

// Setting up led pins to output
void LedPinSetup(uint8_t port, char portName, uint8_t value){

    if(portName == 'A'){
        if(value == 1)
            GPIOA->ODR |= (0x0001 << port);
        else
            GPIOA->ODR &= ~(0x0001 << port);
    }
    else if(portName == 'B'){
            if(value == 1)
                GPIOB->ODR |= (0x0001 << port);
            else
                GPIOB->ODR &= ~(0x0001 << port);

        }
        else if(portName == 'C'){
            if(value == 1)
                GPIOC->ODR |= (0x0001 << port);
            else
                GPIOC->ODR &= ~(0x0001 << port);
    }
}

void setLed(uint8_t r, uint8_t b, uint8_t g){
    r = (r > 0) ? 0 : 1;
    g = (g > 0) ? 0 : 1;
    b = (b > 0) ? 0 : 1;

    LedPinSetup(9,'A',b); // Blue
    LedPinSetup(7,'C',g); // Green
    LedPinSetup(4,'B',r); // Red
}

void ledsetup(){
    pinSetup(9, 'A', 1,0); // Blue
    pinSetup(7, 'C', 1,0); // Green
    pinSetup(4, 'B', 1,0); // Red
    setLed(0,0,0);         // Initially no light up
}


// Setup led such that it depends on the direction of the joystick
void ledJoystick(){
    if(readJoystick()== 1){
        setLed(0,0,0);
        LedPinSetup(9,'A',0);
    }
    else if(readJoystick() == 2){
            setLed(0,0,0);
            LedPinSetup(7,'C',0);
    }
    else if(readJoystick() == 4){
            setLed(0,0,0);
            LedPinSetup(4,'B',0);
    }
    else if(readJoystick() == 8){
            setLed(0,0,0);
            LedPinSetup(7,'C',0);
            LedPinSetup(4,'B',0);
    }
     else if (readJoystick() == 16){
            setLed(0,0,0);
            LedPinSetup(7,'C',0);
            LedPinSetup(4,'B',0);
            LedPinSetup(9,'A',0);
}
    else
        setLed(0,0,0);
}


uint8_t readADC1(){
    pinSetup(0,'A',0,1);

    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_1Cycles5);
    ADC_StartConversion(ADC1); // Start ADC read
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0); // Wait for ADC read
    return ADC_GetConversionValue(ADC1); // Read the ADC value
}

uint8_t readADC2(){
    pinSetup(1,'A',0,1);

    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_1Cycles5);
    ADC_StartConversion(ADC1); // Start ADC read
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0); // Wait for ADC read
    return ADC_GetConversionValue(ADC1); // Read the ADC value
}
