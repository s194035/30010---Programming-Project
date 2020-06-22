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

void lcd_health_bar_zero(uint8_t *buffer){
    char filledHeart[] = {127, '\0'};
    char emptyHeart[] = {128, '\0'};
    memset(buffer, 0x00, 512);
    lcd_write_string(buffer, emptyHeart,0,0);
    lcd_write_string(buffer, emptyHeart,6,0);
    lcd_write_string(buffer, emptyHeart,12,0);
    lcd_write_string(buffer, emptyHeart, 18,0);
    lcd_write_string(buffer, emptyHeart, 24,0);
}

void lcd_health_bar_one(uint8_t *buffer){
    char filledHeart[] = {127, '\0'};
    char emptyHeart[] = {128, '\0'};
    memset(buffer, 0x00, 512);
    lcd_write_string(buffer, filledHeart,0,0);
    lcd_write_string(buffer, emptyHeart,6,0);
    lcd_write_string(buffer, emptyHeart,12,0);
    lcd_write_string(buffer, emptyHeart, 18,0);
    lcd_write_string(buffer, emptyHeart, 24,0);
}

void lcd_health_bar_two(uint8_t *buffer){
    char filledHeart[] = {127, '\0'};
    char emptyHeart[] = {128, '\0'};
    memset(buffer, 0x00, 512);
    lcd_write_string(buffer, filledHeart,0,0);
    lcd_write_string(buffer, filledHeart,6,0);
    lcd_write_string(buffer, emptyHeart,12,0);
    lcd_write_string(buffer, emptyHeart, 18,0);
    lcd_write_string(buffer, emptyHeart, 24,0);
}

void lcd_health_bar_three(uint8_t *buffer){
    char filledHeart[] = {127, '\0'};
    char emptyHeart[] = {128, '\0'};
    memset(buffer, 0x00, 512);
    lcd_write_string(buffer, filledHeart,0,0);
    lcd_write_string(buffer, filledHeart,6,0);
    lcd_write_string(buffer, filledHeart,12,0);
    lcd_write_string(buffer, emptyHeart, 18,0);
    lcd_write_string(buffer, emptyHeart, 24,0);
}

void lcd_health_bar_four(uint8_t *buffer){
    char filledHeart[] = {127, '\0'};
    char emptyHeart[] = {128, '\0'};
    memset(buffer, 0x00, 512);
    lcd_write_string(buffer, filledHeart,0,0);
    lcd_write_string(buffer, filledHeart,6,0);
    lcd_write_string(buffer, filledHeart,12,0);
    lcd_write_string(buffer, filledHeart, 18,0);
    lcd_write_string(buffer, emptyHeart, 24,0);
}

void lcd_health_bar_five(uint8_t *buffer){
    char filledHeart[] = {127, '\0'};
    char emptyHeart[] = {128, '\0'};
    memset(buffer, 0x00, 512);
    lcd_write_string(buffer, filledHeart,0,0);
    lcd_write_string(buffer, filledHeart,6,0);
    lcd_write_string(buffer, filledHeart,12,0);
    lcd_write_string(buffer, filledHeart, 18,0);
    lcd_write_string(buffer, filledHeart, 24,0);
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
    lcd_write_string(buffer, leftHelm, 103, 0);
    lcd_write_string(buffer, midHelm, 108, 0);
    lcd_write_string(buffer, middHelm, 113, 0);
    lcd_write_string(buffer, rightHelm, 118, 0);
    lcd_write_string(buffer, leftFace, 103, 1);
    lcd_write_string(buffer, leftEye, 108, 1);
    lcd_write_string(buffer, rightEye, 113, 1);
    lcd_write_string(buffer, rightFace, 118, 1);
    lcd_write_string(buffer, leftChin, 103, 2);
    lcd_write_string(buffer, midChin, 108, 2);
    lcd_write_string(buffer, middChin, 113, 2);
    lcd_write_string(buffer, rightChin, 118, 2);
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
    lcd_write_string(buffer, leftHelm, 103, 0);
    lcd_write_string(buffer, midHelm, 108, 0);
    lcd_write_string(buffer, middHelm, 113, 0);
    lcd_write_string(buffer, rightHelm, 118, 0);
    lcd_write_string(buffer, leftFace, 103, 1);
    lcd_write_string(buffer, leftEye, 108, 1);
    lcd_write_string(buffer, rightEye, 113, 1);
    lcd_write_string(buffer, rightFace, 118, 1);
    lcd_write_string(buffer, leftChin, 103, 2);
    lcd_write_string(buffer, midChin, 108, 2);
    lcd_write_string(buffer, middChin, 113, 2);
    lcd_write_string(buffer, rightChin, 118, 2);
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
    lcd_write_string(buffer, leftHelm, 103, 0);
    lcd_write_string(buffer, midHelm, 108, 0);
    lcd_write_string(buffer, middHelm, 113, 0);
    lcd_write_string(buffer, rightHelm, 118, 0);
    lcd_write_string(buffer, leftFace, 103, 1);
    lcd_write_string(buffer, leftEye, 108, 1);
    lcd_write_string(buffer, rightEye, 113, 1);
    lcd_write_string(buffer, rightFace, 118, 1);
    lcd_write_string(buffer, leftChin, 103, 2);
    lcd_write_string(buffer, midChin, 108, 2);
    lcd_write_string(buffer, middChin, 113, 2);
    lcd_write_string(buffer, rightChin, 118, 2);
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
    lcd_write_string(buffer, leftHelm, 103, 0);
    lcd_write_string(buffer, midHelm, 108, 0);
    lcd_write_string(buffer, middHelm, 113, 0);
    lcd_write_string(buffer, rightHelm, 118, 0);
    lcd_write_string(buffer, leftFace, 103, 1);
    lcd_write_string(buffer, leftEye, 108, 1);
    lcd_write_string(buffer, rightEye, 113, 1);
    lcd_write_string(buffer, rightFace, 118, 1);
    lcd_write_string(buffer, leftChin, 103, 2);
    lcd_write_string(buffer, midChin, 108, 2);
    lcd_write_string(buffer, middChin, 113, 2);
    lcd_write_string(buffer, rightChin, 118, 2);
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
    lcd_write_string(buffer, leftHelm, 103, 0);
    lcd_write_string(buffer, midHelm, 108, 0);
    lcd_write_string(buffer, middHelm, 113, 0);
    lcd_write_string(buffer, rightHelm, 118, 0);
    lcd_write_string(buffer, leftFace, 103, 1);
    lcd_write_string(buffer, leftEye, 108, 1);
    lcd_write_string(buffer, rightEye, 113, 1);
    lcd_write_string(buffer, rightFace, 118, 1);
    lcd_write_string(buffer, leftChin, 103, 2);
    lcd_write_string(buffer, midChin, 108, 2);
    lcd_write_string(buffer, middChin, 113, 2);
    lcd_write_string(buffer, rightChin, 118, 2);
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
    lcd_write_string(buffer, leftHelm, 103, 0);
    lcd_write_string(buffer, midHelm, 108, 0);
    lcd_write_string(buffer, middHelm, 113, 0);
    lcd_write_string(buffer, rightHelm, 118, 0);
    lcd_write_string(buffer, leftFace, 103, 1);
    lcd_write_string(buffer, leftEye, 108, 1);
    lcd_write_string(buffer, rightEye, 113, 1);
    lcd_write_string(buffer, rightFace, 118, 1);
    lcd_write_string(buffer, leftChin, 103, 2);
    lcd_write_string(buffer, midChin, 108, 2);
    lcd_write_string(buffer, middChin, 113, 2);
    lcd_write_string(buffer, rightChin, 118, 2);
}

void lcd_controller(uint8_t *buffer, uint8_t lives, uint8_t face){

    if(face == 0){
        lcd_face_one(buffer);
    }
    if(face == 1){
        lcd_face_four(buffer);
    }

    if(face == 2){
        lcd_face_five(buffer);
    }

    if(lives == 0){
        lcd_health_bar_zero(buffer);
        lcd_face_six(buffer);
    }

    if(lives == 1){
        lcd_health_bar_one(buffer);
    }

    if(lives == 2){
        lcd_health_bar_two(buffer);
    }

    if(lives == 3){
    lcd_health_bar_three(buffer);
    }

    if(lives == 4){
        lcd_health_bar_four(buffer);
    }

    if(lives == 5){
        lcd_health_bar_five(buffer);
    }
    lcd_push_buffer(buffer);
}




void lcd_animate_face(uint8_t *buffer){
    int i, j;
    lcd_face_one(buffer);
    lcd_push_buffer(buffer);
    for(i = 0; i<2000; i++){
        for(j = 0; j<2000; j++){}
    }
    lcd_face_two(buffer);
    lcd_push_buffer(buffer);
    for(i = 0; i<2000; i++){
        for(j = 0; j<2000; j++){}
    }
    lcd_face_three(buffer);
    lcd_push_buffer(buffer);
    for(i = 0; i<2000; i++){
        for(j = 0; j<2000; j++){}
    }
}
