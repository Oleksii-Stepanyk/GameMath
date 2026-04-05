#ifndef QUATERNION_H
#define QUATERNION_H

typedef struct Vector
{
    double x, y, z;
} Vector;

typedef struct Quaternion
{
    double w, x, y, z;
} Quaternion;

double quaternionMagnitude(Quaternion q);
Quaternion normalizeQuaternion(Quaternion q);
Vector rotateVector(Vector v, Quaternion q);

#endif // QUATERNION_H