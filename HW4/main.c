#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include "vector.h"

void print_vector(Vector v, const char label[])
{
    printf("%s ", label);
    printf("(x = %.4f, y = %.4f, z = %.4f, w = %.4f)\n", v.x, v.y, v.z, v.w);
}

void get_cofactor_2d(double mat[3][3], double temp[2][2], int p, int q)
{
    int i = 0, j = 0;

    // Looping for each element of the matrix
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            // Copying into temporary matrix
            // only those element which are
            // not in given row and column
            if (row != p && col != q)
            {
                temp[i][j++] = mat[row][col];

                // Row is filled, so increase row
                // index and reset col index
                if (j == 2)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

void get_cofactor_3d(double mat[4][4], double temp[3][3], int p, int q)
{
    int i = 0, j = 0;

    // Looping for each element of the matrix
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            // Copying into temporary matrix
            // only those element which are
            // not in given row and column
            if (row != p && col != q)
            {
                temp[i][j++] = mat[row][col];

                // Row is filled, so increase row
                // index and reset col index
                if (j == 3)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

/* a b
   c d */
double matrix_determinant_2d(double m[2][2])
{
    // a * d - b * c
    return (m[0][0] * m[1][1]) - (m[0][1] * m[1][0]);
}

double matrix_determinant_3d(double m[3][3])
{
    double det = 0.0f;
    for (int i = 0; i < 3; i++)
    {
        double num = m[i][0];
        double multiplier = (i % 2 != 0) ? -num : num;
        double matrix[2][2];
        get_cofactor_2d(m, matrix, i, 0);
        det += multiplier * matrix_determinant_2d(matrix);
    }
    return det;
}

double matrix_determinant_4d(double m[4][4])
{
    double det = 0.0f;
    for (int i = 0; i < 4; i++)
    {
        double num = m[i][0];
        double multiplier = (i % 2 != 0) ? -num : num;
        double matrix[3][3];
        get_cofactor_3d(m, matrix, i, 0);
        det += multiplier * matrix_determinant_3d(matrix);
    }
    return det;
}

int main()
{

    Vector a = {+2, +1, +5, 0}; // Used in all 4 tasks
    Vector b = {+2, +1, +5, +1}; // Used in all 4 tasks
 
    // Task 1
    printf("-- Task 1 -- \n");
    double A_1[4][4] = {
        {1, 0, 0, 4},
        {0, 1, 0, 2},
        {0, 0, 1, 6},
        {0, 0, 0, 1}};

    Vector Aa_1 = matrix_vector_multiply(A_1, a);
    Vector Ab_1 = matrix_vector_multiply(A_1, b);

    print_vector(Aa_1, "Aa_1");
    print_vector(Ab_1, "Ab_1");

    double det_A_1 = matrix_determinant_4d(A_1);
    printf("Det(A_1) = %f\n\n", det_A_1);

    // Task 2
    printf("-- Task 2 -- \n");
    double A_2[4][4] = {
        {-1, 0, 0, 4},
        {0, -1, 0, 2},
        {0, 0, -1, 6},
        {0, 0, 0, 1}};

    Vector Aa_2 = matrix_vector_multiply(A_2, a);
    Vector Ab_2 = matrix_vector_multiply(A_2, b);

    print_vector(Aa_2, "Aa_2");
    print_vector(Ab_2, "Ab_2");

    double det_A_2 = matrix_determinant_4d(A_2);
    printf("Det(A_2) = %f\n\n", det_A_2);

    // Task 3
    printf("-- Task 3 -- \n");
    double A_3[4][4] = {
        {sqrt(2.0) / 2.0, -sqrt(2.0) / 2.0, 0, 4},
        {sqrt(2.0) / 2.0, sqrt(2.0) / 2.0, 0, 2},
        {0, 0, 1, 6},
        {0, 0, 0, 1}};

    Vector Aa_3 = matrix_vector_multiply(A_3, a);
    Vector Ab_3 = matrix_vector_multiply(A_3, b);

    print_vector(Aa_3, "Aa_3");
    print_vector(Ab_3, "Ab_3");

    double det_A_3 = matrix_determinant_4d(A_3);
    printf("Det(A_3) = %f\n\n", det_A_3);

    // Task 4
    printf("-- Task 4 -- \n");
    double A_4[4][4] = {
        {0.5, 0, 0, 4},
        {0, 1.5, 0, 2},
        {0, 0, 1, 6},
        {0, 0, 0, 1}
    };

    Vector Aa_4 = matrix_vector_multiply(A_4, a);
    Vector Ab_4 = matrix_vector_multiply(A_4, b);

    print_vector(Aa_4, "Aa_4");
    print_vector(Ab_4, "Ab_4");

    double det_A_4 = matrix_determinant_4d(A_4);
    printf("Det(A_4) = %f\n\n", det_A_4);

    return 0;
}