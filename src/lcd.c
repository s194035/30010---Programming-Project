#include "30010_io.h"
#include "stm32f30x_conf.h"
#include "charset.h"
#include "lcd.h"


// Write a string into a buffer to display it on the LCD, utilizing charset.h
void lcd_write_string(uint8_t *buffer, char * s, uint16_t slice, uint16_t line){
    uint8_t j = 0;
    while(s[j] != 0){
        uint8_t i = 0;
        for(i = 0; i < 5; i++){
            buffer[slice + (128*line) + i + 5 *j] = character_data[s[j] - 0x20][i];
        }
        j++;
    }
}

// Updates the buffer
void lcd_update(uint8_t *buffer){
        lcd_push_buffer(buffer);
}


// Makes the text scroll left on the LCD
void lcd_scroll_left(uint8_t *buffer){
    uint8_t i, temp[4];
    temp[0] = buffer[0];
    temp[1] = buffer[128];
    temp[2] = buffer[256];
    temp[3] = buffer[384];
    for(i = 0; i <= 128; i++){
        buffer[i] = buffer[i+1];
        buffer[i+128] = buffer[i+129];
        buffer[i+256] = buffer[i+257];
        buffer[i+384] = buffer[i + 385];
    }
    buffer[127] = temp[0];
    buffer[255] = temp[1];
    buffer[383] = temp[2];
    buffer[511] = temp[3];
}
