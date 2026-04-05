#include <iostream>
#include <cmath>
#include <cassert>
#include "vector.hpp"

// Helper function to handle floating point inaccuracies
bool nearly_equal(float a, float b, float epsilon = 1e-4f) {
    return std::abs(a - b) < epsilon;
}

// Helper function to verify all 4 components of the vector
bool check_vec(const vector4& v, float exp_x, float exp_y, float exp_z, float exp_w) {
    return nearly_equal(v.x(), exp_x) &&
           nearly_equal(v.y(), exp_y) &&
           nearly_equal(v.z(), exp_z) &&
           nearly_equal(v.w(), exp_w);
}

void test_constructors() {
    vector4 v1(1.0f, 2.0f, 3.0f);
    assert(check_vec(v1, 1.0f, 2.0f, 3.0f, 0.0f) && "3-param constructor failed");

    vector4 v2(1.0f, 2.0f, 3.0f, 4.0f);
    assert(check_vec(v2, 1.0f, 2.0f, 3.0f, 4.0f) && "4-param constructor failed");
    
    std::cout << "[PASS] Constructors and Accessors\n";
}

void test_addition() {
    vector4 v1(1.0f, 2.0f, 3.0f, 4.0f);
    vector4 v2(5.0f, 6.0f, 7.0f, 8.0f);
    
    v1.add(v2);
    assert(check_vec(v1, 6.0f, 8.0f, 10.0f, 12.0f) && "add(const vector4&) failed");

    v1.add(1.0f, 1.0f, 1.0f); // Note: w should not change here if treated as +0 in the implementation
    assert(check_vec(v1, 7.0f, 9.0f, 11.0f, 12.0f) && "add(float, float, float) failed");

    std::cout << "[PASS] Addition\n";
}

void test_subtraction() {
    vector4 v1(10.0f, 10.0f, 10.0f, 10.0f);
    vector4 v2(2.0f, 3.0f, 4.0f, 5.0f);
    
    v1.sub(v2);
    assert(check_vec(v1, 8.0f, 7.0f, 6.0f, 5.0f) && "sub(const vector4&) failed");

    v1.sub(1.0f, 2.0f, 3.0f);
    assert(check_vec(v1, 7.0f, 5.0f, 3.0f, 5.0f) && "sub(float, float, float) failed");

    std::cout << "[PASS] Subtraction\n";
}

void test_multiplication() {
    vector4 v1(2.0f, 3.0f, 4.0f, 5.0f);
    
    v1.mul(2.0f);
    assert(check_vec(v1, 4.0f, 6.0f, 8.0f, 10.0f) && "mul(float) failed");

    vector4 v2(2.0f, 3.0f, 4.0f, 1.0f);
    v2.mul(3.0f, 1.0f); // Scale xyz by 3, but leave w alone
    assert(check_vec(v2, 6.0f, 9.0f, 12.0f, 1.0f) && "mul(float, float) failed");

    std::cout << "[PASS] Multiplication\n";
}

void test_division() {
    vector4 v1(10.0f, 20.0f, 30.0f, 40.0f);
    
    v1.div(2.0f);
    assert(check_vec(v1, 5.0f, 10.0f, 15.0f, 20.0f) && "div(float) failed");

    vector4 v2(9.0f, 12.0f, 15.0f, 1.0f);
    v2.div(3.0f, 1.0f); // Divide xyz by 3, but leave w alone
    assert(check_vec(v2, 3.0f, 4.0f, 5.0f, 1.0f) && "div(float, float) failed");

    std::cout << "[PASS] Division\n";
}

void test_dot_product() {
    vector4 v1(1.0f, 2.0f, 3.0f, 4.0f);
    vector4 v2(5.0f, 6.0f, 7.0f, 8.0f);
    
    // Dot product: (1*5) + (2*6) + (3*7) + (4*8) = 5 + 12 + 21 + 32 = 70
    // The result should be broadcasted to all 4 slots.
    v1.dot(v2);
    assert(check_vec(v1, 70.0f, 70.0f, 70.0f, 70.0f) && "dot(const vector4&) failed");

    vector4 v3(1.0f, 2.0f, 3.0f, 0.0f);
    // Dot product with (2, 2, 2, 0): (1*2) + (2*2) + (3*2) + (0*0) = 2 + 4 + 6 = 12
    v3.dot(2.0f, 2.0f, 2.0f);
    assert(check_vec(v3, 12.0f, 12.0f, 12.0f, 12.0f) && "dot(float, float, float) failed");

    std::cout << "[PASS] Dot Product\n";
}

void test_magnitude_and_normalization() {
    // We use a known vector (3, 4, 0, 0) because its magnitude is exactly 5
    vector4 v1(3.0f, 4.0f, 0.0f, 0.0f);
    
    float mag_sq = v1.magnitude_square();
    assert(nearly_equal(mag_sq, 25.0f) && "magnitude_square() failed");

    float mag = v1.magnitude();
    assert(nearly_equal(mag, 5.0f) && "magnitude() failed");

    // Normalize should result in (3/5, 4/5, 0, 0) -> (0.6, 0.8, 0, 0)
    v1.normalize();
    assert(check_vec(v1, 0.6f, 0.8f, 0.0f, 0.0f) && "normalize() failed");

    std::cout << "[PASS] Magnitude and Normalization\n";
}

void test_chain_calls() {
    vector4 v1(1.0f, 2.0f, 3.0f, 4.0f);
    vector4 delta(1.0f, 1.0f, 1.0f, 1.0f);

    vector4& ref = v1.add(delta)
                    .sub(0.5f, 1.0f, 1.5f)
                    .mul(2.0f, 0.5f)
                    .div(2.0f, 0.5f);

    assert(&ref == &v1 && "chained call should return self reference");
    assert(check_vec(v1, 1.5f, 2.0f, 2.5f, 5.0f) && "chained arithmetic operations failed");

    vector4 v2(1.0f, 2.0f, 3.0f, 1.0f);
    vector4 dot_other(2.0f, 0.5f, 1.0f, 4.0f);

    v2.mul(2.0f)
      .dot(dot_other)
      .add(1.0f, 1.0f, 1.0f);

    assert(check_vec(v2, 21.0f, 21.0f, 21.0f, 20.0f) && "chained dot + add operations failed");

    std::cout << "[PASS] Chain Calls\n";
}

int main() {
    std::cout << "--- Starting SIMD Vector4 Tests ---\n";
    
    test_constructors();
    test_addition();
    test_subtraction();
    test_multiplication();
    test_division();
    test_dot_product();
    test_magnitude_and_normalization();
    test_chain_calls();
    
    std::cout << "--- All Tests Passed! ---\n";
    
    return 0;
}