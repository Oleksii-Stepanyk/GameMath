#include "vector.hpp"

vector4::vector4(float x, float y, float z)
{
    data_ = _mm_setr_ps(x, y, z, 0.0f);
}

vector4::vector4(float x, float y, float z, float w)
{
    data_ = _mm_setr_ps(x, y, z, w);
}

float vector4::x() const
{
    return x_;
}

float vector4::y() const
{
    return y_;
}

float vector4::z() const
{
    return z_;
}

float vector4::w() const
{
    return w_;
}

vector4 &vector4::add(const vector4 &other)
{
    this->data_ = _mm_add_ps(this->data_, other.data_);
    return *this;
}

vector4 &vector4::add(float x, float y, float z)
{
    __m128 temp = _mm_setr_ps(x, y, z, 0.0f);
    this->data_ = _mm_add_ps(this->data_, temp);
    return *this;
}

vector4 &vector4::sub(const vector4 &other)
{
    this->data_ = _mm_sub_ps(this->data_, other.data_);
    return *this;
}

vector4 &vector4::sub(float x, float y, float z)
{
    __m128 temp = _mm_setr_ps(x, y, z, 0.0f);
    this->data_ = _mm_sub_ps(this->data_, temp);
    return *this;
}

vector4 &vector4::mul(float scale)
{
    __m128 scale_vector = _mm_set1_ps(scale);
    this->data_ = _mm_mul_ps(this->data_, scale_vector);
    return *this;
}

vector4 &vector4::mul(float scale, float w_scale)
{
    __m128 scale_vector = _mm_setr_ps(scale, scale, scale, w_scale);
    this->data_ = _mm_mul_ps(this->data_, scale_vector);
    return *this;
}

vector4 &vector4::div(float scale)
{
    __m128 scale_vector = _mm_set1_ps(scale);
    this->data_ = _mm_div_ps(this->data_, scale_vector);
    return *this;
}

vector4 &vector4::div(float scale, float w_scale)
{
    __m128 scale_vector = _mm_setr_ps(scale, scale, scale, w_scale);
    this->data_ = _mm_div_ps(this->data_, scale_vector);
    return *this;
}

vector4 &vector4::dot(const vector4 &other)
{
    this->data_ = _mm_dp_ps(this->data_, other.data_, 0xFF);
    return *this;
}

vector4 &vector4::dot(float x, float y, float z)
{
    __m128 temp = _mm_setr_ps(x, y, z, 0.0f);
    this->data_ = _mm_dp_ps(this->data_, temp, 0xFF);
    return *this;
}

float vector4::magnitude() const
{
    __m128 res = _mm_sqrt_ps(_mm_dp_ps(this->data_, this->data_, 0xFF));
    return res[0];
}

float vector4::magnitude_square() const
{
    __m128 res = _mm_dp_ps(this->data_, this->data_, 0xFF);
    return res[0];
}

vector4 &vector4::normalize()
{
    __m128 temp = _mm_set1_ps(this->magnitude_square());
    __m128 inv_mag = _mm_rsqrt_ps(temp);
    this->data_ = _mm_mul_ps(this->data_, inv_mag);
    return *this;
}