#ifndef SNAKE_H
#define SNAKE_H

#include "vector.h"
#include <stdbool.h>

#define SNAKESIZE 128
#define GROWTHRATE 2;
// This file is written by Gustav 
/*
    Snake: 
        size - the current length of the snake. size - 1 is the last element.
        
    functions: 
        init - constructor
        draw: draw the snake to the display buffer
        isKill
            - check for collision between head and other parts (linear search)
        move - move the snake and move the tail
*/


typedef struct Snake {
    int size; // size - 1 also implicitly functions as the tail part of the snake
    Vector parts[SNAKESIZE]; //
    Vector movementDirection; // What direction is the snake moving? ( Change with buttons)
} Snake;

Snake player_snake; // the snake himself (initialize before game start)

Vector queued_tail;



void snake_initialize(Snake* snake);
void snake_grow(Snake* , int );
void snake_draw( Snake*);
void snake_setDirection(Snake* snake, int direction);
// Does not check collision: it would possibly be excessive
void snake_move( Snake* snake);
// Checks whether the snake has collided with a wall or itself.
// Return 1 if true. Return 0 if false.
int snake_isKill( Snake* );


#endif