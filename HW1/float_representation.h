#ifndef FLOAT_REPRESENTATION_H
#define FLOAT_REPRESENTATION_H

#include <inttypes.h>

union float_bits
{
    uint32_t bits;
    float value;
};

uint32_t to_bits(float value);
float to_float(uint32_t bits);

#endif // FLOAT_REPRESENTATION_H