#include <stdio.h>

#include "float_representation.h"

int main(void)
{
    uint64_t bits = 0b0011111100011001100110011001101000111111000110011001100110011010;
    double num = to_double(bits, true);
    printf("%e", num);
    return 0;
}