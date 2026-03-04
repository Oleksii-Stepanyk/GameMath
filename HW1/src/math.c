#include "math.h"
#include "checks.h"

float abs_f(float number)
{
    uint32_t bits = f_to_bits(number);
    bits &= 0x7FFFFFFF;
    return to_float(bits, false);
}

double abs_d(double number)
{
    uint64_t bits = d_to_bits(number);
    bits &= 0x7FFFFFFFFFFFFFFF;
    return to_double(bits, false);
}

float min_f(float a, float b)
{
        if (is_nan_f(a)){
            return b;
        }
        if (is_nan_f(b)){
            return a;
        }
        if (a == b){
            return is_neg_zero_f(a) ? a : b;
        }
        return (a < b) ? a : b;
}

double min_d(double a, double b)
{
    if (is_nan_d(a)){
        return b;
    }
    if (is_nan_d(b)){
        return a;
    }
    if (a == b){
        return is_neg_zero_d(a) ? a : b;
    }
    return (a < b) ? a : b;
}

float max_f(float a, float b)
{
    if (is_nan_f(a)){
        return b;
    }
    if (is_nan_f(b)){
        return a;
    }
    if (a == b){
        return is_neg_zero_f(a) ? a : b;
    }
    return (a > b) ? a : b;
}

double max_d(double a, double b)
{
    if (is_nan_d(a)){
        return b;
    }
    if (is_nan_d(b)){
        return a;
    }
    if (a == b){
        return is_neg_zero_d(a) ? a : b;
    }
    return (a > b) ? a : b;
}

float clamp_f(float number, float min, float max)
{
    return max_f(min, min_f(number, max));
}

double clamp_d(double number, double min, double max)
{
    return max_d(min, min_d(number, max));
}