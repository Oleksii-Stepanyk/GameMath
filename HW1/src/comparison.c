#include "comparison.h"
#include "checks.h"
#include "math.h"

bool equal_f(float a, float b)
{
    if (is_nan_f(a) || is_nan_f(b)) return false;
    if (is_zero_f(a) && is_zero_f(b)) return true;
    return a == b;
}

bool equal_d(double a, double b)
{
    if (is_nan_d(a) || is_nan_d(b)) return false;
    if (is_zero_d(a) && is_zero_d(b)) return true;
    return a == b;
}

bool equal_eps_f(float a, float b, float epsilon)
{
    if (is_nan_f(a) || is_nan_f(b)) return false;
    if (is_zero_f(a) && is_zero_f(b)) return true;
    if (is_inf_f(a) || is_inf_f(b)) return a == b;
    return abs_f(a - b) <= epsilon;
}

bool equal_eps_d(double a, double b, double epsilon)
{
    if (is_nan_d(a) || is_nan_d(b)) return false;
    if (is_zero_d(a) && is_zero_d(b)) return true;
    if (is_inf_d(a) || is_inf_d(b)) return a == b;
    return abs_d(a - b) <= epsilon;
}

bool less_f(float a, float b)
{
    if (is_nan_f(a) || is_nan_f(b)) return false;
    return a < b;
}

bool less_d(double a, double b)
{
    if (is_nan_d(a) || is_nan_d(b)) return false;
    return a < b;
}

bool less_eps_f(float a, float b, float epsilon)
{
    if (is_nan_f(a) || is_nan_f(b)) return false;
    if (is_inf_f(a) || is_inf_f(b)) return a < b;
    return (b - a) > epsilon;
}

bool less_eps_d(double a, double b, double epsilon)
{
    if (is_nan_d(a) || is_nan_d(b)) return false;
    if (is_inf_d(a) || is_inf_d(b)) return a < b;
    return (b - a) > epsilon;
}

bool greater_f(float a, float b)
{
    if (is_nan_f(a) || is_nan_f(b)) return false;
    return a > b;
}

bool greater_d(double a, double b)
{
    if (is_nan_d(a) || is_nan_d(b)) return false;
    return a > b;
}

bool greater_eps_f(float a, float b, float epsilon)
{
    if (is_nan_f(a) || is_nan_f(b)) return false;
    if (is_inf_f(a) || is_inf_f(b)) return a > b;
    return (a - b) > epsilon;
}

bool greater_eps_d(double a, double b, double epsilon)
{
    if (is_nan_d(a) || is_nan_d(b)) return false;
    if (is_inf_d(a) || is_inf_d(b)) return a > b;
    return (a - b) > epsilon;
}