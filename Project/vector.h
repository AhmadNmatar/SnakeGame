#ifndef VECTOR_C
#define VECTOR_C


// Vector.h
// Code in this file is by Gustav.

// Represents a two-dimensional integer vector. 
// More out of convenience than out of necessity.
typedef struct Vector {
    int x;
    int y;
} Vector;



int Vector_isEquivalentto(Vector* first, Vector* other);


#endif