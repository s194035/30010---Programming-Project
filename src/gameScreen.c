#include "gameScreen.h"
#include "ansi.h"
#include "updateships.h"
#include <stdio.h>

#define WIDTH 168
#define HEIGHT 44


uint8_t mainMenu(uint16_t *highScore){
    uint8_t startPoint = 0;
    uint8_t menuPoint = 0;
    uint8_t difficultyPoint = 1;
    printMainMenu();
    char controlChar;
    uint8_t settingsPoint = 0;

    // Loop to control cursor movement and select different menus
    while(1){
        controlChar = uart_get_char();

        // Cursor is on Play Game
        if(startPoint == 0){
            if(controlChar == 's'){
                moveCursorDown(95,13);
                startPoint = 1;
            }
             else if(controlChar == 13){
                box(WIDTH, HEIGHT);
                menuPoint = 1;
                startPoint = 6;
                printPlayer();
                gotoxy(95,13);
                printf("O");
            }
            controlChar = 0;
        }

            if(menuPoint == 1){
                if(controlChar == 's'){
                    startPoint = 6;
                    moveCursorDown(95,13);
                    menuPoint = 2;
                    }
            }
            if(menuPoint == 2){
                if(controlChar == 'w'){
                    startPoint = 6;
                    moveCursorUp(95,15);
                    menuPoint = 1;
                }
            }

            if(controlChar == 13 && (menuPoint == 1 || menuPoint == 2)){
            gotoxy(20,20);
            printf("%d, %d", difficultyPoint, menuPoint);
            return difficultyPoint + (menuPoint << 4);
        }

        // Cursor is on High Score
        if(startPoint == 1){
            if(controlChar == 'w'){
                moveCursorUp(95,15);
                startPoint = 0;
            }
            else if(controlChar == 's'){
                moveCursorDown(95,15);
                startPoint = 2;
            }
            else if(controlChar == 13){
                printHighScore(highScore);
                startPoint = 6;
            }
            controlChar = 0;
        }

        // Cursor is on Settings
        if(startPoint == 2){
            if(controlChar == 'w'){
                moveCursorUp(95,17);
                startPoint = 1;
            }
            if(controlChar == 's'){
                moveCursorDown(95,17);
                startPoint = 3;
            }

            else if(controlChar == 13){
                box(WIDTH, HEIGHT);
                settingsPoint = 1;
                startPoint = 4;
                printSettings();
                gotoxy(95,13);
                printf("O");
            }
            controlChar = 0;
        }

        if(settingsPoint == 1 && startPoint == 4){
            if(controlChar == 's'){
                startPoint = 4;
                difficultyPoint = 2;
                moveCursorDown(95,13);
                settingsPoint = 2;
                controlChar = 0;
            }
        }

        if(settingsPoint == 2 && startPoint == 4){
            if(controlChar == 'w'){
                startPoint = 4;
                moveCursorUp(95,15);
                settingsPoint = 1;
            }
            else if(controlChar == 's'){
                startPoint = 4;
                difficultyPoint = 3;
                moveCursorDown(95,15);
                settingsPoint = 3;
            }
        }

        if(settingsPoint == 3 && startPoint == 4){
            if(controlChar == 'w'){
                startPoint = 4;
                difficultyPoint = 2;
                moveCursorUp(95,17);
                settingsPoint = 2;
                controlChar = 0;
            }
        }


        // Cursor is on Help
        if(startPoint == 3){
            if(controlChar == 'w'){
                moveCursorUp(95,19);
                startPoint = 2;
            }

            else if(controlChar == 13){
                printHelp();
                startPoint = 6;
                }
            controlChar = 0;
        }
        if(startPoint == 6){
            gotoxy(95,40);
            printf("Press ESC");
            if(controlChar == 27){
            printMainMenu();
            startPoint = 0;
            menuPoint = 0;
            }
            controlChar = 0;
        }

        if(startPoint == 4){
            gotoxy(95,40);
            printf("Press Enter to select difficulty");
            if(controlChar == 13){
                printMainMenu();
                startPoint = 0;
            }
            controlChar = 0;
        }
    }
}

void moveCursorDown(uint8_t x0, uint8_t y0){
    gotoxy(x0,y0);
    printf("%c",32);
    gotoxy(x0,y0+2);
    printf("O");
}

void moveCursorUp(uint8_t x0, uint8_t y0){
    gotoxy(x0,y0);
    printf("%c",32);
    gotoxy(x0,y0-2);
    printf("O");
}

void printMainMenu(){
    clrscr();
    box(WIDTH, HEIGHT);
    gotoxy(80,13);
    printf("Play Game");
    gotoxy(80, 15);
    printf("High Score");
    gotoxy(80, 17);
    printf("Settings");
    gotoxy(80,19);
    printf("Help");
    gotoxy(95, 13);
    printf("O");
}

void printHelp(){
    clrscr();
    box(WIDTH, HEIGHT);
    gotoxy(40,13);
    printf("Hello and welcome to Space Force, the game where you battle against evil aliens.");
    gotoxy(40,15);
    printf("The objective of Space Force is to shoot the enemies approaching from the top");
    gotoxy(40,17);
    printf("of the screen. You must not get hit by the enemies or their projectiles. You");
    gotoxy(40,19);
    printf("move your spaceship with the WASD-keys and shoot with Q. You have three lives");
    gotoxy(40,21);
    printf("and a face indicating your mental state, both are shown on the LCD screen.");
    gotoxy(40,23);
    printf("If you want more games like this consider supporting us on Patreon. But enough");
    gotoxy(40,25);
    printf("talk, let's play.");
}

void printHighScore(uint16_t *highScore){
    uint8_t i, j;
    uint8_t temp;
    for (i = 0; i < 10; i++){
		for (j = i + 1; j < 10; j++){
			if(highScore[i] < highScore[j]){

				temp = highScore[i];
				highScore[i] = highScore[j];
				highScore[j] = temp;
			}
		}
	}

    clrscr();
    gotoxy(20,13);
    printf("1: %d", highScore[0]);
    gotoxy(20,15);
    printf("2: %d", highScore[1]);
    gotoxy(20,17);
    printf("3: %d", highScore[2]);
    gotoxy(20,19);
    printf("4: %d", highScore[3]);
    gotoxy(20,21);
    printf("5: %d", highScore[4]);
}

void printGameOver(){
    gotoxy(80,13);
    printf("Game Over");
    gotoxy(80,15);
    printf("You have lost all your lives.");
    gotoxy(80,17);
    printf("Your final score was: ");
}

void printPlayer(){
    gotoxy(80,13);
    printf("1 Player");
    gotoxy(80,15);
    printf("2 Player");
}

void printSettings(){
    gotoxy(80,13);
    printf("Easy");
    gotoxy(80,15);
    printf("Medium");
    gotoxy(80,17);
    printf("Hard");
}

void printPauseScreen(){
    gotoxy(80,80);
    printf("Continue");
    gotoxy(80,82);
    printf("Back to main menu");
    gotoxy(100,80);
    printf("O");
}
