#include "checks.h"
#include "representation.h"

static const uint32_t F_SIGN_MASK = 0x7FFFFFFF;
static const uint32_t F_EXP_MASK  = 0x7F800000;
static const uint32_t F_MANT_MASK = 0x007FFFFF;

static const uint64_t D_SIGN_MASK = 0x7FFFFFFFFFFFFFFF;
static const uint64_t D_EXP_MASK  = 0x7FF0000000000000;
static const uint64_t D_MANT_MASK = 0x000FFFFFFFFFFFFF;

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
    return (bits & F_SIGN_MASK) == 0;
}

bool is_zero_d(double number)
{
    uint64_t bits = d_to_bits(number);
    return (bits & D_SIGN_MASK) == 0;
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
    return (bits & F_SIGN_MASK) == F_EXP_MASK;
}

bool is_inf_d(double number)
{
    uint64_t bits = d_to_bits(number);
    return (bits & D_SIGN_MASK) == D_EXP_MASK;
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
    return (bits & F_SIGN_MASK) > F_EXP_MASK;
}

bool is_nan_d(double number)
{
    uint64_t bits = d_to_bits(number);
    return (bits & D_SIGN_MASK) > D_EXP_MASK;
}

bool is_finite_f(float number)
{
    uint32_t bits = f_to_bits(number);
    return (bits & F_EXP_MASK) != F_EXP_MASK;
}

bool is_finite_d(double number)
{
    uint64_t bits = d_to_bits(number);
    return (bits & D_EXP_MASK) != D_EXP_MASK;
}

bool is_subnormal_f(float number)
{
    uint32_t bits = f_to_bits(number);
    return (bits & F_EXP_MASK) == 0 && (bits & F_MANT_MASK) != 0;
}

bool is_subnormal_d(double number)
{
    uint64_t bits = d_to_bits(number);
    return (bits & D_EXP_MASK) == 0 && (bits & D_MANT_MASK) != 0;
}

bool is_normal_f(float number)
{
    uint32_t bits = f_to_bits(number);
    uint32_t exp = bits & F_EXP_MASK;
    return exp != 0 && exp != F_EXP_MASK;
}

bool is_normal_d(double number)
{
    uint64_t bits = d_to_bits(number);
    uint64_t exp = bits & D_EXP_MASK;
    return exp != 0 && exp != D_EXP_MASK;
}
