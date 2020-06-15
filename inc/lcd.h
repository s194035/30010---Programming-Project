#ifndef LCD_H
#define LCD_H

#include "stm32f30x_conf.h"
#include "30010_io.h"

uint8_t updateLCD;
void lcd_write_string(uint8_t *buffer, char *s, uint16_t slice, uint16_t line);
void lcd_update(uint8_t *buffer);
void lcd_scroll_left(uint8_t *buffer);
void lcd_face_one(uint8_t *buffer);
void lcd_face_two(uint8_t *buffer);
void lcd_face_three(uint8_t *buffer);
void lcd_face_four(uint8_t *buffer);
void lcd_face_five(uint8_t *buffer);
void lcd_face_six(uint8_t *buffer);


#endif
