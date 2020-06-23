#ifndef LCD_H
#define LCD_H

#include "30010_io.h"
#include "stm32f30x_conf.h"
#include "charset.h"
#include "string.h"

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
void lcd_animate_face(uint8_t *buffer);
void lcd_health_bar_zero(uint8_t *buffer);
void lcd_health_bar_one(uint8_t *buffer);
void lcd_health_bar_two(uint8_t *buffer);
void lcd_health_bar_three(uint8_t *buffer);
void lcd_health_bar_four(uint8_t *buffer);
void lcd_health_bar_five(uint8_t *buffer);
void lcd_controller(uint8_t *buffer, int8_t lives, uint8_t face);
void lcd_face_anim(uint8_t setface, uint8_t *faceAnim, uint8_t *faceCount);
#endif
