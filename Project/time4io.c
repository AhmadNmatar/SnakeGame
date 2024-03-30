#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h" 

// Code in this file is by Ahmad.

int getsw(void){
     return (PORTD >> 8) & 0xF;
   
}

int getbtns(void){
    return (PORTD >> 4) & 0xf;
}
