#include <stdio.h>

#include "representation.h"

int main(void)
{
    uint64_t bits_1 = 0b00111111000110011001100110011010;
    double num_1 = to_double(bits_1, true);
    uint64_t bits_2 = 0b01000010111101110011100110010011;
    double num_2 = to_double(bits_2, true);
    uint64_t bits_3 = 0b11000011010111101001110011001010;
    double num_3 = to_double(bits_3, true);
    printf("%e", num_1);
    printf("%e", num_2);
    printf("%e", num_3);
    return 0;
}