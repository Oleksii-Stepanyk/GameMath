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

bool is_inf_f(float number)
{
    uint32_t bits = f_to_bits(number);
    return (bits & 0x7FFFFFFF) == 0x7F800000;
}

bool is_inf_d(double number)
{
    uint64_t bits = d_to_bits(number);
    return (bits & 0x7FFFFFFFFFFFFFFF) == 0x7FF0000000000000;
}

bool is_pos_inf_f(float number)
{
    return is_inf_f(number) && !is_signed_f(number);
}

bool is_pos_inf_d(double number)
{
    return is_inf_d(number) && !is_signed_d(number);
}

bool is_neg_inf_f(float number)
{
    return is_inf_f(number) && is_signed_f(number);
}

bool is_neg_inf_d(double number)
{
    return is_inf_d(number) && is_signed_d(number);
}

bool is_nan_f(float number)
{
    uint32_t bits = f_to_bits(number);
    return (bits & 0x7FFFFFFF) > 0x7F800000;
}

bool is_nan_d(double number)
{
    uint64_t bits = d_to_bits(number);
    return (bits & 0x7FFFFFFFFFFFFFFF) > 0x7FF0000000000000;
}

bool is_finite_f(float number)
{
    uint32_t bits = f_to_bits(number);
    return (bits & 0x7F800000) != 0x7F800000;
}

bool is_finite_d(double number)
{
    uint64_t bits = d_to_bits(number);
    return (bits & 0x7FF0000000000000) != 0x7FF0000000000000;
}

bool is_subnormal_f(float number)
{
    uint32_t bits = f_to_bits(number);
    return (bits & 0x7F800000) == 0 && (bits & 0x007FFFFF) != 0;
}

bool is_subnormal_d(double number)
{
    uint64_t bits = d_to_bits(number);
    return (bits & 0x7FF0000000000000) == 0 && (bits & 0x000FFFFFFFFFFFFF) != 0;
}

bool is_normal_f(float number)
{
    uint32_t bits = f_to_bits(number);
    uint32_t exp = bits & 0x7F800000;
    return exp != 0 && exp != 0x7F800000;
}

bool is_normal_d(double number)
{
    uint64_t bits = d_to_bits(number);
    uint64_t exp = bits & 0x7FF0000000000000;
    return exp != 0 && exp != 0x7FF0000000000000;
}
