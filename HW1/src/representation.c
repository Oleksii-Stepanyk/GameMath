#include "representation.h"

uint32_t f_to_bits(float value)
{
    union float_bits temp;
    temp.value = value;
    return temp.bits;
}

uint64_t d_to_bits(double value)
{
    union double_bits temp;
    temp.value = value;
    return temp.bits;
}

float to_float(uint32_t bits, bool littleEndian)
{
    if (littleEndian)
    {
        bits = f_big_little_endian(bits);
    }
    union float_bits temp;
    temp.bits = bits;
    return temp.value;
}

double to_double(uint64_t bits, bool littleEndian)
{
    if (littleEndian)
    {
        bits = d_big_little_endian(bits);
    }
    union double_bits temp;
    temp.bits = bits;
    return temp.value;
}

uint32_t f_big_little_endian(uint32_t bits)
{
    // initialize union memory
    union float_bits temp;
    temp.bits = bits;

    // backup first two bits of little endian for swap
    char first_bit = temp.c_bits[0];
    char second_bit = temp.c_bits[1];

    // swap bits
    // 4 3 2 1 -> 1 2 3 4
    temp.c_bits[0] = temp.c_bits[3];
    temp.c_bits[1] = temp.c_bits[2];
    temp.c_bits[2] = second_bit;
    temp.c_bits[3] = first_bit;

    return temp.bits;
}

uint64_t d_big_little_endian(uint64_t bits)
{
    // initialize union memory
    union double_bits temp;
    temp.bits = bits;

    // backup first four bits of little endian for swap
    char first_bit = temp.c_bits[0];
    char second_bit = temp.c_bits[1];
    char third_bit = temp.c_bits[2];
    char fourth_bit = temp.c_bits[3];

    // swap bits
    // 8 7 6 5 4 3 2 1 -> 1 2 3 4 5 6 7 8
    temp.c_bits[0] = temp.c_bits[7];
    temp.c_bits[1] = temp.c_bits[6];
    temp.c_bits[2] = temp.c_bits[5];
    temp.c_bits[3] = temp.c_bits[4];
    temp.c_bits[4] = fourth_bit;
    temp.c_bits[5] = third_bit;
    temp.c_bits[6] = second_bit;
    temp.c_bits[7] = first_bit;

    return temp.bits;
}