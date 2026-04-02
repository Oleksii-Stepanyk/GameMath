#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vector
{
    double x, y, z, w;
} Vector;

Vector matrix_vector_multiply(double matrix[4][4], Vector vector);

#endif // VECTOR_H