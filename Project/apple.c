#include <pic32mx.h> 
#include "apple.h" 
#include "mipslab.h"

// apple.c
// Code in this file is mostly by Ahmad.


// this function use the value of timer 2 to generate a random corrdinate for apple
void generate_position(int* x, int* y){
    *x = (TMR2 % 100) + 10;
    *y = (TMR2 % 20 ) + 5; 
}

void apple_init(Apple* apple){
    generate_position(&(*apple).position.x,&(*apple).position.y);

}

void apple_draw(Apple* apple) {
    DisplayBuffer_setPixel((*apple).position.x, (*apple).position.y, 1);
}
