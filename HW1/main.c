#include <stdio.h>

#include "float_representation.h"

int main(void)
{
    uint32_t bits = 0b00111111000110011001100110011010;
    float num = to_float(bits, true);
    printf("%e", num);
    return 0;
}
