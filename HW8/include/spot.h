#ifndef SPOT_H
#define SPOT_H

#include "raylib.h"

typedef struct Spot {
    float x;
    float y;
    Color euclidean_color;
    Color manhattan_color;
    Color chebyshev_color;
} Spot;

Spot SpotCreate(float x, float y, Color euclidean_color, Color manhattan_color, Color chebyshev_color);

#endif
