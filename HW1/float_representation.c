#include "float_representation.h"

uint32_t to_bits(float value) {
    union float_bits temp;
    temp.value = value;
    return temp.bits;
}

float to_float(uint32_t bits) {
    union float_bits temp;
    temp.bits = bits;
    return temp.value;
}