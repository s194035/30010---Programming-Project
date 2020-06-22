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
void box(int width, int height){
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



// This functions draws a window with a title and 2 different styles.
void window(int x1, int y1, int x2, int y2, char text[], char style){
    int i;
    inverse(0);
    clrscr();

    bgcolor(6);
    fgcolor(0);

    // Defining the window corners.
    char upLeft = (style == 1) ? 218 : 201;
    char downLeft = (style == 1) ? 192 : 200;
    char upRight = (style == 1) ? 191 : 187;
    char downRight = (style == 1) ? 217 : 188;
    char titleRight = (style == 1) ? 195 : 204;
    char titleLeft = (style == 1) ? 180 : 185;


    // Drawing the window corners.
    gotoxy(x1,y1);
    printf("%c",upLeft);
    gotoxy(x1,y2);
    printf("%c",downLeft);
    gotoxy(x2,y2);
    printf("%c",downRight);
    gotoxy(x2,y1);
    printf("%c",upRight);


    // Choosing between 2 different styles of window borders.
    if(style != 1){
        for(i = x1+1; i<x2; i++){
            gotoxy(i,y1);
            printf("%c",205);
            gotoxy(i,y2);
            printf("%c", 205);
        }
        for(i = y1+1; i<y2; i++){
            gotoxy(x1,i);
            printf("%c",186);
            gotoxy(x2,i);
            printf("%c",186);
        }
    }
    else{
        for(i = x1+1; i<x2; i++){
            gotoxy(i,y1);
            printf("%c",196);
            gotoxy(i,y2);
            printf("%c", 196);
        }
        for(i = y1+1; i<y2; i++){
            gotoxy(x1,i);
            printf("%c",179);
            gotoxy(x2,i);
            printf("%c",179);
        }
    }
    fgcolor(0);
    gotoxy(x1+1, y1);
    printf("%c",titleLeft);
    gotoxy(x2-1,y1);
    printf("%c",titleRight);


    // Printing the title
    inverse(1);
    int j = 0;
    fgcolor(0);
    for(i = x1+2; i<x2-1; i++){
        gotoxy(i,y1);
        printf("%c",(j<strlen(text)) ? text[j] : 32);
        j++;
    }
    inverse(0);
    gotoxy(x2+1,y2+1);
}
}
