#ifndef FLOAT_REPRESENTATION_H
#define FLOAT_REPRESENTATION_H

#include <inttypes.h>
#include <stdbool.h>

union float_bits
{
    char c_bits[4];
    uint32_t bits;
    float value;
};

uint32_t to_bits(float value);
float to_float(uint32_t bits, bool littleEndian);

uint32_t big_little_endian(uint32_t value);

#endif // FLOAT_REPRESENTATION_H