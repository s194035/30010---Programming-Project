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
         updateLCD = 0;
         if (updateLCD >= 100){
         lcd_scroll_left(buffer);
         lcd_push_buffer(buffer);
         updateLCD = 0;
     }
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

void lcd_health_bar(uint8_t *buffer){
    char filledHeart[] = {127, '\0'};
    char emptyHeart[] = {128, '\0'};
    memset(buffer, 0x00, 512);
    lcd_write_string(buffer, filledHeart,0,0);
    lcd_write_string(buffer, emptyHeart,6,0);
}

// Normal face
void lcd_face_one(uint8_t *buffer){
    char leftHelm[] = {129, '\0'};
    char midHelm[] = {130, '\0'};
    char middHelm[] = {131, '\0'};
    char rightHelm[] = {132, '\0'};
    char leftFace[] = {133, '\0'};
    char leftEye[] = {134, '\0'};
    char rightEye[] = {135, '\0'};
    char rightFace[] = {136, '\0'};
    char leftChin[] = {137, '\0'};
    char midChin[] = {138, '\0'};
    char middChin[] = {139, '\0'};
    char rightChin[] = {140, '\0'};
    lcd_write_string(buffer, leftHelm, 53, 0);
    lcd_write_string(buffer, midHelm, 58, 0);
    lcd_write_string(buffer, middHelm, 63, 0);
    lcd_write_string(buffer, rightHelm, 68, 0);
    lcd_write_string(buffer, leftFace, 53, 1);
    lcd_write_string(buffer, leftEye, 58, 1);
    lcd_write_string(buffer, rightEye, 63, 1);
    lcd_write_string(buffer, rightFace, 68, 1);
    lcd_write_string(buffer, leftChin, 53, 2);
    lcd_write_string(buffer, midChin, 58, 2);
    lcd_write_string(buffer, middChin, 63, 2);
    lcd_write_string(buffer, rightChin, 68, 2);
}

// Normal face looking right
void lcd_face_two(uint8_t *buffer){
    char leftHelm[] = {129, '\0'};
    char midHelm[] = {130, '\0'};
    char middHelm[] = {131, '\0'};
    char rightHelm[] = {132, '\0'};
    char leftFace[] = {133, '\0'};
    char leftEye[] = {141, '\0'};
    char rightEye[] = {141, '\0'};
    char rightFace[] = {136, '\0'};
    char leftChin[] = {137, '\0'};
    char midChin[] = {138, '\0'};
    char middChin[] = {139, '\0'};
    char rightChin[] = {140, '\0'};
    lcd_write_string(buffer, leftHelm, 53, 0);
    lcd_write_string(buffer, midHelm, 58, 0);
    lcd_write_string(buffer, middHelm, 63, 0);
    lcd_write_string(buffer, rightHelm, 68, 0);
    lcd_write_string(buffer, leftFace, 53, 1);
    lcd_write_string(buffer, leftEye, 58, 1);
    lcd_write_string(buffer, rightEye, 63, 1);
    lcd_write_string(buffer, rightFace, 68, 1);
    lcd_write_string(buffer, leftChin, 53, 2);
    lcd_write_string(buffer, midChin, 58, 2);
    lcd_write_string(buffer, middChin, 63, 2);
    lcd_write_string(buffer, rightChin, 68, 2);
}

// Normal face looking left
void lcd_face_three(uint8_t *buffer){
    char leftHelm[] = {129, '\0'};
    char midHelm[] = {130, '\0'};
    char middHelm[] = {131, '\0'};
    char rightHelm[] = {132, '\0'};
    char leftFace[] = {133, '\0'};
    char leftEye[] = {142, '\0'};
    char rightEye[] = {142, '\0'};
    char rightFace[] = {136, '\0'};
    char leftChin[] = {137, '\0'};
    char midChin[] = {138, '\0'};
    char middChin[] = {139, '\0'};
    char rightChin[] = {140, '\0'};
    lcd_write_string(buffer, leftHelm, 53, 0);
    lcd_write_string(buffer, midHelm, 58, 0);
    lcd_write_string(buffer, middHelm, 63, 0);
    lcd_write_string(buffer, rightHelm, 68, 0);
    lcd_write_string(buffer, leftFace, 53, 1);
    lcd_write_string(buffer, leftEye, 58, 1);
    lcd_write_string(buffer, rightEye, 63, 1);
    lcd_write_string(buffer, rightFace, 68, 1);
    lcd_write_string(buffer, leftChin, 53, 2);
    lcd_write_string(buffer, midChin, 58, 2);
    lcd_write_string(buffer, middChin, 63, 2);
    lcd_write_string(buffer, rightChin, 68, 2);
}

// Angry face
void lcd_face_four(uint8_t *buffer){
    char leftHelm[] = {129, '\0'};
    char midHelm[] = {130, '\0'};
    char middHelm[] = {131, '\0'};
    char rightHelm[] = {132, '\0'};
    char leftFace[] = {133, '\0'};
    char leftEye[] = {145, '\0'};
    char rightEye[] = {146, '\0'};
    char rightFace[] = {136, '\0'};
    char leftChin[] = {137, '\0'};
    char midChin[] = {147, '\0'};
    char middChin[] = {148, '\0'};
    char rightChin[] = {140, '\0'};
    lcd_write_string(buffer, leftHelm, 53, 0);
    lcd_write_string(buffer, midHelm, 58, 0);
    lcd_write_string(buffer, middHelm, 63, 0);
    lcd_write_string(buffer, rightHelm, 68, 0);
    lcd_write_string(buffer, leftFace, 53, 1);
    lcd_write_string(buffer, leftEye, 58, 1);
    lcd_write_string(buffer, rightEye, 63, 1);
    lcd_write_string(buffer, rightFace, 68, 1);
    lcd_write_string(buffer, leftChin, 53, 2);
    lcd_write_string(buffer, midChin, 58, 2);
    lcd_write_string(buffer, middChin, 63, 2);
    lcd_write_string(buffer, rightChin, 68, 2);
}

// Happy face
void lcd_face_five(uint8_t *buffer){
    char leftHelm[] = {129, '\0'};
    char midHelm[] = {130, '\0'};
    char middHelm[] = {131, '\0'};
    char rightHelm[] = {132, '\0'};
    char leftFace[] = {133, '\0'};
    char leftEye[] = {143, '\0'};
    char rightEye[] = {143, '\0'};
    char rightFace[] = {136, '\0'};
    char leftChin[] = {137, '\0'};
    char midChin[] = {149, '\0'};
    char middChin[] = {150, '\0'};
    char rightChin[] = {140, '\0'};
    lcd_write_string(buffer, leftHelm, 53, 0);
    lcd_write_string(buffer, midHelm, 58, 0);
    lcd_write_string(buffer, middHelm, 63, 0);
    lcd_write_string(buffer, rightHelm, 68, 0);
    lcd_write_string(buffer, leftFace, 53, 1);
    lcd_write_string(buffer, leftEye, 58, 1);
    lcd_write_string(buffer, rightEye, 63, 1);
    lcd_write_string(buffer, rightFace, 68, 1);
    lcd_write_string(buffer, leftChin, 53, 2);
    lcd_write_string(buffer, midChin, 58, 2);
    lcd_write_string(buffer, middChin, 63, 2);
    lcd_write_string(buffer, rightChin, 68, 2);
}

// Dead face
void lcd_face_six(uint8_t *buffer){
    char leftHelm[] = {129, '\0'};
    char midHelm[] = {130, '\0'};
    char middHelm[] = {131, '\0'};
    char rightHelm[] = {132, '\0'};
    char leftFace[] = {133, '\0'};
    char leftEye[] = {144, '\0'};
    char rightEye[] = {144, '\0'};
    char rightFace[] = {136, '\0'};
    char leftChin[] = {151, '\0'};
    char midChin[] = {152, '\0'};
    char middChin[] = {153, '\0'};
    char rightChin[] = {154, '\0'};
    lcd_write_string(buffer, leftHelm, 53, 0);
    lcd_write_string(buffer, midHelm, 58, 0);
    lcd_write_string(buffer, middHelm, 63, 0);
    lcd_write_string(buffer, rightHelm, 68, 0);
    lcd_write_string(buffer, leftFace, 53, 1);
    lcd_write_string(buffer, leftEye, 58, 1);
    lcd_write_string(buffer, rightEye, 63, 1);
    lcd_write_string(buffer, rightFace, 68, 1);
    lcd_write_string(buffer, leftChin, 53, 2);
    lcd_write_string(buffer, midChin, 58, 2);
    lcd_write_string(buffer, middChin, 63, 2);
    lcd_write_string(buffer, rightChin, 68, 2);
}
