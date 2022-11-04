#include "ansi.h"

void fgcolor(uint8_t foreground) {
/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light GreenstartTimer()
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       WhitestartTimer()
*/
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%dm", ESC, type, foreground+30);
}

void bgcolor(uint8_t background) {
/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like that, but when the background color is first changed there is no
 	              way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.
    Value      Color
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
*/
  printf("%c[%dm", ESC, background+40);
}

void color(uint8_t foreground, uint8_t background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
}

void resetbgcolor() {
// gray on black text, no underline, no blink, no reverse
  printf("%c[m", ESC);
}


void clrscr(){
    printf("%c[2J", ESC); // Clear Putty terminal
}

void clreol(){
    printf("%c[2K", ESC); // Clear particular line in Putty terminal
}

void gotoxy(int x, int y){
    printf("%c[%d;%dH", ESC, y, x); // Go to coordinate (x,y) in Putty terminal
}

// Underline text in Putty terminal
void underline(uint8_t on){
    if(on == 1)
        printf("%c[4m", ESC);
    else
        printf("%c[24m", ESC);
}

// Makes text blink in Putty terminal
void blink(uint8_t on){
    printf("%c[%dm", ESC, (on == 1) ? 05 : 25);
}

// Inverts the colors of the foreground text and background.
void inverse(uint8_t on){
    printf("%c[%dm", ESC, (on == 1) ? 07 : 27);
}

// Makes title for game box.
void title(int x, int y, char text []) {
    gotoxy (x,y);
    printf("%c", 185);
    gotoxy(x+1,y);
    printf("%s", text);
    gotoxy ((x+strlen(text)+1),y);
    printf ("%c", 204);

}

// This function just draws a rectangular box.
void box(uint8_t width, uint8_t height){
    clrscr();
    int i;

    char upLeft = 201;
    char downLeft = 200;
    char upRight = 187;
    char downRight = 188;

    // Printing horizontal line
    for(i = 1; i<width; i++){
        gotoxy(i,0);
        printf("%c",205);
        gotoxy(i,height);
        printf("%c", 205);
    }
    // Printing vertical
    for(i = 1; i<height; i++){
        gotoxy(0,i);
        printf("%c",186);
        gotoxy(width,i);
        printf("%c",186);
    }

    // Printing the corners
    gotoxy(0,0);
    printf("%c",upLeft);
    gotoxy(0,height);
    printf("%c",downLeft);
    gotoxy(width,0);
    printf("%c",upRight);
    gotoxy(width, height);
    printf("%c",downRight);


}

void box2(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2){
    uint8_t i;

    // Drawing the horizontal lines
    for(i = y1+1; i<y2; i++){
            gotoxy(x1,i);
            printf("%c",186);
            gotoxy(x2,i);
            printf("%c", 186);
    }

    // Drawing the vertical lines
    for(i = x1+1; i<x2; i++){
            gotoxy(i,y1);
            printf("%c",205);
            gotoxy(i,y2);
            printf("%c",205);
    }

    // Drawing the corners of the window
    gotoxy(x1,y1);
    printf("%c\n", 201);
    gotoxy(x2,y1);
    printf("%c",187);
    gotoxy(x1,y2);
    printf("%c", 200);
    gotoxy(x2,y2);
    printf("%c", 188);
}
