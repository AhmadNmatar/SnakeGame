// sanke.c

//The code in this file is mostly written by Gustav,
//with some debugging help from Ahmad.

#include "snake.h"
#include "constant.h"
#include "vector.h"

bool waitingToGrow = false;
/*
    snake.c

    the snake can head up, 
*/


void snake_setDirection(Snake* snake, int direction) {
    switch (direction) {
        case 0:
            player_snake.movementDirection = DIRECTION_DOWN;
            break;
        case 1:
            player_snake.movementDirection = DIRECTION_LEFT;
            break;
        case 2:
           player_snake.movementDirection = DIRECTION_UP;
            break;
        case 3:
            player_snake.movementDirection = DIRECTION_RIGHT;
            break;
        default:
            break;
    }
    return;
}



  void snake_initialize(Snake* snake) {
    // Set initial direction
    snake_setDirection(snake, 3); // Assuming RIGHT is a valid direction defined elsewhere
    // Set initial position
    const Vector spawn = {63, 15}; // Assuming Vector type is defined elsewhere
    player_snake.parts[0] = spawn;
    player_snake.size = 2; // Initialize snake size

    // No need to handle tail initialization here since size is 1
}


// Attempts to change the size of the snake, but the snake size is clamped to [1, SNAKESIZE).
void snake_grow(Snake* snake, int n) {
    int newSize = player_snake.size + 1;
    if (newSize > SNAKESIZE)
        return;
     else {
        queued_tail = player_snake.parts[newSize - 2];
        waitingToGrow = true;
     };
}



// Move the snake one step according to it's stored movement diretion
void snake_move(Snake* snake) {
    // Calculate new head position
    Vector newHeadPosition = {
        player_snake.parts[0].x + player_snake.movementDirection.x,
        player_snake.parts[0].y + player_snake.movementDirection.y
    };

    // Shift the tail positions
     int i;
    for ( i = player_snake.size - 1; i > 0; --i) {
        player_snake.parts[i] = player_snake.parts[i - 1];
    }

    // Update the head position
    player_snake.parts[0] = newHeadPosition;

    if (waitingToGrow == true) {
        player_snake.size++;
        player_snake.parts[player_snake.size - 1] = queued_tail;
        waitingToGrow = false;
    } 
}



// draw the snake on screen
void snake_draw( Snake* snake) {
    int i;
    for (i = 0; i < (*snake).size; i++) {
        DisplayBuffer_setPixel((*snake).parts[i].x, (*snake).parts[i].y, 1);
    }
    return;
}


// we could also make this just use the global variable.
int snake_isKill( Snake* snake) {
    int size = (*snake).size;
    // check if snake has entered walls 

    // note: (*snake).parts[size - 1] addresses the head of the snake

    if (!(((*snake).parts[size - 1].x >= 1) && ((*snake).parts[size - 1].x <= 126)))
        return 1;
    if (!(((*snake).parts[size - 1].y >= 1) && ((*snake).parts[size - 1].y <= 30)))
        return 1;
    // check if snake has entered itself
    if (size > 2) {
        int i;
        for (i = size - 2; i > 1; i--) {
            if (Vector_isEquivalentto(&(*snake).parts[size - 1], &(*snake).parts[i])) return 1;
        }
    }
    return 0;
}
