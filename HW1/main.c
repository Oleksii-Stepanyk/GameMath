#include <stdio.h>

#include "float_representation.h"

int main(void) {
    uint32_t bits = 0b10011010100110010001100100111111; // Converted to Big Endian manually
    float num = to_float(bits);
    printf("%e", num);
    return 0;
}
