#include <math.h>

#include "vector.h"

Vector2 vector2_add(Vector2 lhs, Vector2 rhs)
{
    return (Vector2){
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y,
    };
}

Vector2 vector2_scale(Vector2 vector, float scalar)
{
    return (Vector2){
        .x = vector.x * scalar,
        .y = vector.y * scalar,
    };
}

float vector2_dot(Vector2 lhs, Vector2 rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

float vector2_length(Vector2 vector)
{
    return sqrtf(vector2_dot(vector, vector));
}

Vector2 vector2_normalize(Vector2 vector)
{
    float length = vector2_length(vector);
    if (length == 0.0f)
    {
        return (Vector2){0.0f, 0.0f};
    }

    return vector2_scale(vector, 1.0f / length);
}

Vector3 vector3_add(Vector3 lhs, Vector3 rhs)
{
    return (Vector3){
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y,
        .z = lhs.z + rhs.z,
    };
}

Vector3 vector3_scale(Vector3 vector, float scalar)
{
    return (Vector3){
        .x = vector.x * scalar,
        .y = vector.y * scalar,
        .z = vector.z * scalar,
    };
}

float vector3_dot(Vector3 lhs, Vector3 rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

float vector3_length(Vector3 vector)
{
    return sqrtf(vector3_dot(vector, vector));
}

Vector3 vector3_normalize(Vector3 vector)
{
    float length = vector3_length(vector);
    if (length == 0.0f)
    {
        return (Vector3){0.0f, 0.0f, 0.0f};
    }

    return vector3_scale(vector, 1.0f / length);
}
