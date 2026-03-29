// test_representation.cpp – unit tests for representation.h / representation.c
#include <gtest/gtest.h>
#include <cstdint>
#include <limits>

extern "C"
{
#include "representation.h"
}

// ═══════════════════════════════════════════════════════════════════════════════
// f_to_bits
// ═══════════════════════════════════════════════════════════════════════════════
TEST(FToBits, PosZero) { EXPECT_EQ(0x00000000u, f_to_bits(0.0f)); }
TEST(FToBits, NegZero) { EXPECT_EQ(0x80000000u, f_to_bits(-0.0f)); }
TEST(FToBits, One) { EXPECT_EQ(0x3F800000u, f_to_bits(1.0f)); }
TEST(FToBits, NegOne) { EXPECT_EQ(0xBF800000u, f_to_bits(-1.0f)); }
TEST(FToBits, PosInf) { EXPECT_EQ(0x7F800000u, f_to_bits(std::numeric_limits<float>::infinity())); }
TEST(FToBits, NegInf) { EXPECT_EQ(0xFF800000u, f_to_bits(-std::numeric_limits<float>::infinity())); }
TEST(FToBits, NaN)
{
    uint32_t bits = f_to_bits(std::numeric_limits<float>::quiet_NaN());
    // exponent all-ones, mantissa != 0
    EXPECT_EQ(0x7F800000u, bits & 0x7F800000u);
    EXPECT_NE(0u, bits & 0x007FFFFFu);
}
TEST(FToBits, RoundTrip)
{
    float val = 3.14159265f;
    EXPECT_EQ(val, to_float(f_to_bits(val), false));
}

// ═══════════════════════════════════════════════════════════════════════════════
// d_to_bits
// ═══════════════════════════════════════════════════════════════════════════════
TEST(DToBits, PosZero) { EXPECT_EQ(0x0000000000000000ull, d_to_bits(0.0)); }
TEST(DToBits, NegZero) { EXPECT_EQ(0x8000000000000000ull, d_to_bits(-0.0)); }
TEST(DToBits, One) { EXPECT_EQ(0x3FF0000000000000ull, d_to_bits(1.0)); }
TEST(DToBits, NegOne) { EXPECT_EQ(0xBFF0000000000000ull, d_to_bits(-1.0)); }
TEST(DToBits, PosInf) { EXPECT_EQ(0x7FF0000000000000ull, d_to_bits(std::numeric_limits<double>::infinity())); }
TEST(DToBits, NegInf) { EXPECT_EQ(0xFFF0000000000000ull, d_to_bits(-std::numeric_limits<double>::infinity())); }
TEST(DToBits, NaN)
{
    uint64_t bits = d_to_bits(std::numeric_limits<double>::quiet_NaN());
    EXPECT_EQ(0x7FF0000000000000ull, bits & 0x7FF0000000000000ull);
    EXPECT_NE(0ull, bits & 0x000FFFFFFFFFFFFFull);
}
TEST(DToBits, RoundTrip)
{
    double val = 3.14159265358979;
    EXPECT_EQ(val, to_double(d_to_bits(val), false));
}

// ═══════════════════════════════════════════════════════════════════════════════
// to_float / to_double  (littleEndian = false → identity)
// ═══════════════════════════════════════════════════════════════════════════════
TEST(ToFloat, PosZero) { EXPECT_EQ(0.0f, to_float(0x00000000u, false)); }
TEST(ToFloat, NegZero) { EXPECT_EQ(-0.0f, to_float(0x80000000u, false)); }
TEST(ToFloat, One) { EXPECT_EQ(1.0f, to_float(0x3F800000u, false)); }
TEST(ToFloat, NegOne) { EXPECT_EQ(-1.0f, to_float(0xBF800000u, false)); }
TEST(ToFloat, PosInf) { EXPECT_EQ(std::numeric_limits<float>::infinity(), to_float(0x7F800000u, false)); }

TEST(ToDouble, PosZero) { EXPECT_EQ(0.0, to_double(0x0000000000000000ull, false)); }
TEST(ToDouble, NegZero) { EXPECT_EQ(-0.0, to_double(0x8000000000000000ull, false)); }
TEST(ToDouble, One) { EXPECT_EQ(1.0, to_double(0x3FF0000000000000ull, false)); }
TEST(ToDouble, NegOne) { EXPECT_EQ(-1.0, to_double(0xBFF0000000000000ull, false)); }
TEST(ToDouble, PosInf) { EXPECT_EQ(std::numeric_limits<double>::infinity(), to_double(0x7FF0000000000000ull, false)); }

// ═══════════════════════════════════════════════════════════════════════════════
// f_big_little_endian  (byte reversal: applying twice → identity)
// ═══════════════════════════════════════════════════════════════════════════════
TEST(FEndian, KnownSwap)
{
    // 0x12345678 → 0x78563412
    EXPECT_EQ(0x78563412u, f_big_little_endian(0x12345678u));
}
TEST(FEndian, DoubleSwapIsIdentity)
{
    uint32_t original = 0xDEADBEEFu;
    EXPECT_EQ(original, f_big_little_endian(f_big_little_endian(original)));
}
TEST(FEndian, AllZeros) { EXPECT_EQ(0x00000000u, f_big_little_endian(0x00000000u)); }
TEST(FEndian, AllOnes) { EXPECT_EQ(0xFFFFFFFFu, f_big_little_endian(0xFFFFFFFFu)); }

// ═══════════════════════════════════════════════════════════════════════════════
// d_big_little_endian  (byte reversal: applying twice → identity)
// ═══════════════════════════════════════════════════════════════════════════════
TEST(DEndian, KnownSwap)
{
    // 0x0102030405060708 → 0x0807060504030201
    EXPECT_EQ(0x0807060504030201ull, d_big_little_endian(0x0102030405060708ull));
}
TEST(DEndian, DoubleSwapIsIdentity)
{
    uint64_t original = 0xDEADBEEFCAFEBABEull;
    EXPECT_EQ(original, d_big_little_endian(d_big_little_endian(original)));
}
TEST(DEndian, AllZeros) { EXPECT_EQ(0x0000000000000000ull, d_big_little_endian(0x0000000000000000ull)); }
TEST(DEndian, AllOnes) { EXPECT_EQ(0xFFFFFFFFFFFFFFFFull, d_big_little_endian(0xFFFFFFFFFFFFFFFFull)); }

// ═══════════════════════════════════════════════════════════════════════════════
// to_float / to_double  (littleEndian = true → apply byte swap then convert)
// ═══════════════════════════════════════════════════════════════════════════════
TEST(ToFloatLE, RoundTrip)
{
    // Store 1.0f as big-endian bits → feeding that to to_float with little-endian
    // flag should undo the swap and give 1.0f back.
    uint32_t swapped = f_big_little_endian(0x3F800000u); // big→little
    EXPECT_EQ(1.0f, to_float(swapped, true));
}

TEST(ToDoubleLE, RoundTrip)
{
    uint64_t swapped = d_big_little_endian(0x3FF0000000000000ull);
    EXPECT_EQ(1.0, to_double(swapped, true));
}
