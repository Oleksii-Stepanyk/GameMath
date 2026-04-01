#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vector2
{
    float x, y;
} Vector2;

Vector2 vector2_add(Vector2 lhs, Vector2 rhs);
Vector2 vector2_scale(Vector2 vector, float scalar);
float vector2_dot(Vector2 lhs, Vector2 rhs);
float vector2_length(Vector2 vector);
Vector2 vector2_normalize(Vector2 vector);

typedef struct Vector3
{
    float x, y, z;
} Vector3;

Vector3 vector3_add(Vector3 lhs, Vector3 rhs);
Vector3 vector3_scale(Vector3 vector, float scalar);
float vector3_dot(Vector3 lhs, Vector3 rhs);
float vector3_length(Vector3 vector);
Vector3 vector3_normalize(Vector3 vector);

#endif // VECTOR_H