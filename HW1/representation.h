#ifndef REPRESENTATION_H
#define REPRESENTATION_H

#include <inttypes.h>
#include <stdbool.h>

union float_bits
{
    char c_bits[4];
    uint32_t bits;
    float value;
};

union double_bits
{
    char c_bits[8];
    uint64_t bits;
    double value;
};

uint32_t f_to_bits(float value);
uint64_t d_to_bits(double value);
float to_float(uint32_t bits, bool littleEndian);
double to_double(uint64_t bits, bool littleEndian);
uint32_t f_big_little_endian(uint32_t value);
uint64_t d_big_little_endian(uint64_t value);

#endif // REPRESENTATION_H