#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <immintrin.h>

struct vector4
{
public:
    vector4(float x, float y, float z);
    vector4(float x, float y, float z, float w);

private:
    union
    {
        __m128 data_;
        struct
        {
            float x_, y_, z_, w_;
        };
    };

public:
    float x() const;
    float y() const;
    float z() const;
    float w() const;

    vector4 &add(const vector4 &other);
    vector4 &add(float x, float y, float z);

    vector4 &sub(const vector4 &other);
    vector4 &sub(float x, float y, float z);

    vector4 &mul(float scale);
    vector4 &mul(float scale, float w_scale);

    vector4 &div(float scale);
    vector4 &div(float scale, float w_scale);

    vector4 &dot(const vector4 &other);
    vector4 &dot(float x, float y, float z);

    float magnitude() const;
    float magnitude_square() const;

    vector4 &normalize();
};

#endif // VECTOR_HPP