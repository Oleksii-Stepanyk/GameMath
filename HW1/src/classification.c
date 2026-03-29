#include "classification.h"

FP_CLASSIFICATION classify_f(float number)
{
    if (is_zero_f(number))
        return FP_ZERO;
    if (is_inf_f(number))
        return FP_INFINITE;
    if (is_nan_f(number))
        return FP_NAN;
    if (is_subnormal_f(number))
        return FP_SUBNORMAL;
    if (is_normal_f(number))
        return FP_NORMAL;
    return FP_UNDEFINED;
}

FP_CLASSIFICATION classify_d(double number)
{
    if (is_zero_d(number))
        return FP_ZERO;
    if (is_inf_d(number))
        return FP_INFINITE;
    if (is_nan_d(number))
        return FP_NAN;
    if (is_subnormal_d(number))
        return FP_SUBNORMAL;
    if (is_normal_d(number))
        return FP_NORMAL;
    return FP_UNDEFINED;
}