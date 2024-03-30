#ifndef APPLE_H
#define APPLE_H

// Apple.h 
// Code in this file is mostly by Ahmad.

#include "vector.h"
    typedef struct Apple {
        Vector position;
    } Apple;

Apple apple;

void apple_init(Apple*);

void generate_position(int* x, int* y);
void apple_draw(Apple* apple);

#endif