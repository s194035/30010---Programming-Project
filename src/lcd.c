#include "30010_io.h"
#include "stm32f30x_conf.h"
#include "charset.h"


void lcd_write_string(uint8_t *buffer, char * s, uint16_t slice, uint16_t line){
    uint8_t j = 0;
    while(s[j] != 0x00){
        uint8_t i = 0;
        for(i = 0; i < 5; i++){
            buffer[slice + (128*line) + i + 5 *j] = character_data[s[j] - 0x20][i];
        }
        j++;
    }
}

void lcd_update(){
   ;
}
