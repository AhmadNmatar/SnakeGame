// vector.c
// Code in this file is by Gustav.

// Various constants.
#include "vector.h"


// return 1 if equivalent, 0 if false.
int Vector_isEquivalentto(Vector* first, Vector* other) {
    if (((*first).x == (*other).x) && ((*first).y == (*other).y))
        return 1;
    else
        return 0;
}
