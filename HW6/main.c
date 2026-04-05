#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include "quaternion.h"

void print_vector(Vector v, const char label[])
{
    printf("%s ", label);
    printf("(x = %.4f, y = %.4f, z = %.4f)\n", v.x, v.y, v.z);
}

int main()
{
    Vector v = {1.0f, 1.0f, 1.0f};
    Quaternion q1 = {0.808f, 0.492f, -0.015f, 0.325f};
    Quaternion q2 = {0.271f, 0.271f, 0.653f, 0.653f};

    Vector v1 = rotateVector(v, q1);
    Vector v2 = rotateVector(v, q2);

    print_vector(v1, "v_1");
    print_vector(v2, "v_2");

    return 0;
}