#include "spot.h"
    
Spot SpotCreate(float x, float y, Color euclidean_color, Color manhattan_color, Color chebyshev_color)
{
    Spot spot = { x, y, euclidean_color, manhattan_color, chebyshev_color };
    return spot;
}
