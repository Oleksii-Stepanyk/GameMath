#include "float_representation.h"

uint32_t to_bits(float value)
{
    union float_bits temp;
    temp.value = value;
    return temp.bits;
}

float to_float(uint32_t bits, bool littleEndian)
{
    if (littleEndian)
    {
        bits = big_little_endian(bits);
    }
    union float_bits temp;
    temp.bits = bits;
    return temp.value;
}

uint32_t big_little_endian(uint32_t bits)
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