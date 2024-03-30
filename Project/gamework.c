/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file was modified 2017-04-31 by Ture Teknolog 
   
   Code in this file has been altered by Gustav Landberg and 
   Ahmad Nabil Matar 2024-02-29

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
#include <stdbool.h> 
#include "apple.h"



const int snake_grow_count = 1;
unsigned int direction = 3;
int score = 0;
int snake_move_counter = 0;


/* Interrupt Service Routine */
void user_isr( void )
{
   if(IFS(0) & 0x100){ 
      int btns = getbtns() & 0xE; // btn
    // read input
    if(btns){
           if (btns & 0x8){ // BTN4 pressed
               if (direction == 3) direction = 0;
               else direction++;
           }
           if (btns & 0x4){ // BTN3 pressed
               if (direction == 0) direction = 3;
               else direction--;
            }
           snake_setDirection(&player_snake, direction);
   }
      IFS(0) &= ~0x100; 
   }
}

/* Lab-specific initialization goes here */
void game_init( void )
{
    volatile unsigned* trisE = (volatile unsigned*) 0xbf886100;
    *trisE &= 0x00ff;
    
      // 1111 0000 0000
    TRISDSET = 0xF00;
    TRISGSET = 0x004;
    TRISFSET = 0x2;
    
    T2CON = 0;
    PR2 = 31250; // 0xBB6 100 ms = 0.1 sec -> (0.1 * 80 *e6) / 256 =
    TMR2 = 0xFFFF;
    // enable interrupt for bit 8 in IFS(0)?
    IEC(0) = 0x100;
     
    // set interrupt priority
    // priority: bits 4-2, subpriority: 1-0
    // 0001 1100
    IPC(2) = 0x1F;
    
    T2CONSET = 0x8000; // enable timer 2 set bit 15 to 1
    T2CON   |= 0x070; // set bit 5 ,6  and 7 to 111, presacle 256:1
    enable_interrupt();
    DisplayBuffer_initialize();
    apple_init(&apple);
    snake_initialize(&player_snake);

   return;
}


/* This function is called repetitively from the main program */

void game_process( void ) {
   DisplayBuffer_initialize(); // start drawing a new frame
   draw_Board();
   snake_draw(&player_snake);
   apple_draw(&apple);

	if (snake_isKill(&player_snake)) {
      // if the snake dies, reset the snake
      gameOver(score);
      score = 0;
      snake_initialize(&player_snake);
      apple_init(&apple);
      apple_draw(&apple);
   }
   if (Vector_isEquivalentto(&player_snake.parts[0],&apple.position)) {
      score++;
      snake_grow(&player_snake, snake_grow_count);
      apple_init(&apple);
      apple_draw(&apple);
   }
   else
   {
   apple_draw(&apple);
   //DisplayBuffer_send(); // send the frame
   }	
	snake_move_counter = (snake_move_counter + 1) % 10;
   if (snake_move_counter == 0){
         snake_move(&player_snake);
      }
   
   DisplayBuffer_send();
}