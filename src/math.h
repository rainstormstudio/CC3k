#ifndef MATH_H
#define MATH_H

#include <stdlib.h>

namespace Math{
    const int deltaX[8] = {0, 0, 1, -1, 1, -1, 1, -1};
    const int deltaY[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
    
    int random(int min, int max) {
        return min + rand() % ((max + 1) - min);
    }
}

#endif
