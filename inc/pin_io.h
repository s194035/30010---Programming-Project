#ifndef PIN_IO_H
#define PIN_IO_H

#include "stm32f30x_conf.h"
#include "30010_io.h"

uint8_t readJoystick();

void pinSetup(uint16_t port, char portName, uint32_t moder, uint32_t puder);

void ioConfig();

void setLed(uint8_t r, uint8_t b, uint8_t g);

void ledsetup();

void JoystickSetup();

void ledJoystick();

uint8_t readADC1();

uint8_t readADC2();

void LedPinSetup(uint8_t port, char portName, uint8_t value);
#endif // PIN_IO_H
