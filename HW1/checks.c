#include "checks.h"
#include "representation.h"

bool is_signed_f(float number)
{
    uint32_t bits = f_to_bits(number);
    return (bits >> 31) & 1;
}

bool is_signed_d(double number)
{
    uint64_t bits = d_to_bits(number);
    return (bits >> 63) & 1;
}

bool is_zero_f(float number)
{
    uint32_t bits = f_to_bits(number);
    return (bits & 0x7FFFFFFF) == 0;
}

bool is_zero_d(double number)
{
    uint64_t bits = d_to_bits(number);
    return (bits & 0x7FFFFFFFFFFFFFFF) == 0;
}

bool is_pos_zero_f(float number)
{
    return is_zero_f(number) && !is_signed_f(number);
}

bool is_pos_zero_d(double number)
{
    return is_zero_d(number) && !is_signed_d(number);
}

bool is_neg_zero_f(float number)
{
    return is_zero_f(number) && is_signed_f(number);
}

bool is_neg_zero_d(double number)
{
    return is_zero_d(number) && is_signed_d(number);
}
