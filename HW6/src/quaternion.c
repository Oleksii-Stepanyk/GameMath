#include <math.h>
#include <float.h>
#include <stdbool.h>

#include "quaternion.h"

double quaternionMagnitude(Quaternion q)
{
    return sqrt((q.w * q.w) + (q.x * q.x) + (q.y * q.y) + (q.z * q.z));
}

Quaternion normalizeQuaternion(Quaternion q)
{
    double magnitude = quaternionMagnitude(q);
    q.w = q.w / magnitude;
    q.x = q.x / magnitude;
    q.y = q.y / magnitude;
    q.z = q.z / magnitude;
    return q;
}

Vector rotateVector(Vector v, Quaternion q)
{
    q = normalizeQuaternion(q);

    Vector t;
    t.x = 2 * (q.y * v.z - q.z * v.y);
    t.y = 2 * (q.z * v.x - q.x * v.z);
    t.z = 2 * (q.x * v.y - q.y * v.x);

    Vector newVector;
    newVector.x = v.x + q.w * t.x + (q.y * t.z - q.z * t.y);
    newVector.y = v.y + q.w * t.y + (q.z * t.x - q.x * t.z);
    newVector.z = v.z + q.w * t.z + (q.x * t.y - q.y * t.x);

    return newVector;
}