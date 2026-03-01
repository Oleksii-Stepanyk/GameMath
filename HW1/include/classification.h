#ifndef CLASSIFICATION_H
#define CLASSIFICATION_H

#include "checks.h"

typedef enum FP_CLASSIFICATION
{
    FP_UNDEFINED = -2,
    FP_NAN = -1,
    FP_ZERO = 0,
    FP_NORMAL = 1,
    FP_SUBNORMAL = 2,
    FP_INFINITE = 3
} FP_CLASSIFICATION;

FP_CLASSIFICATION classify_f(float number);
FP_CLASSIFICATION classify_d(double number);

#endif // CLASSIFICATION_H