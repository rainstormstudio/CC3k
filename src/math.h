#ifndef MATH_H
#define MATH_H

#include <stdlib.h>

namespace Math{
    int random(int min, int max) {
        return min + rand() % ((max + 1) - min);
    }
}

#endif
