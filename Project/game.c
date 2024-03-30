
// Code in this file is written by Ahmad.

//#include "snake.h"
#include "mipslab.h"
#include <stdio.h>
#include <string.h>

// generating the start screen of the game
void game_start(){
    display_string(0, "   SNAKE GAME");
    display_string(2, " PRESS BTN4 TO");
    display_string(3, "     START");
    display_update();    
      while(1){
         int btn4 = getbtns() & 0x8;
         if(btn4 == 8){
            break;
      }
   }
}

// a helper function that add two string
void add_str(char* str1, char* str2){
    while (*str1 != '\0')
        str1++;
    while(*str2 != '\0'){
        *str1 = *str2;
        str1++;
        str2++;
    }
    *str1 = '\0';
}
// generate gome over screen, and display the score
void gameOver(int score){
    display_string(0, "   GAME OVER");
    char score_str[10] = "SCORE:  ";
    char* scr =  itoaconv(score);
    add_str(score_str, scr);
    display_string(1, score_str);
    display_string(2, " PRESS BTN4 TO");
    display_string(3, "    RESTART");
    display_update();    
      while(1){
         int btn4 = getbtns() & 0x8;
         if(btn4 == 8){
            break;
      }
   }
} 

//this functio draw the game boarder, a rectangular around the screen
void draw_Board(void){
    DisplayBuffer_initialize();
int x, y;
for(y = 0; y < 2; y++){
    for(x = 0; x < 128; x++){
        DisplayBuffer_setPixel(x,y,1);
    }
}

for(y = 30; y < 32; y++){
    for(x = 0; x < 128; x++){
        DisplayBuffer_setPixel(x,y,1);
    }
}

for(y = 2; y < 30; y++){
    for(x = 0; x < 2; x++){
        DisplayBuffer_setPixel(x,y,1);
    }
    for(x = 126; x < 128; x++){
        DisplayBuffer_setPixel(x,y,1);
    }
}
}

