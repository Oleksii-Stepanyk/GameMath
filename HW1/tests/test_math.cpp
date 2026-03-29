// test_math.cpp – unit tests for math.h / math.c
#include <gtest/gtest.h>
#include <limits>

extern "C"
{
#include "math.h"   // project math.h (abs_f, min_f, max_f, clamp_f …)
#include "checks.h" // is_neg_zero_f, is_nan_f …
}

static constexpr float F_INF = std::numeric_limits<float>::infinity();
static constexpr float F_NEG_INF = -std::numeric_limits<float>::infinity();
static constexpr double D_INF = std::numeric_limits<double>::infinity();
static constexpr double D_NEG_INF = -std::numeric_limits<double>::infinity();

static float f_nan() { return std::numeric_limits<float>::quiet_NaN(); }
static double d_nan() { return std::numeric_limits<double>::quiet_NaN(); }

// ═══════════════════════════════════════════════════════════════════════════════
// abs_f / abs_d
// ═══════════════════════════════════════════════════════════════════════════════
TEST(AbsFloat, Positive) { EXPECT_EQ(1.0f, abs_f(1.0f)); }
TEST(AbsFloat, Negative) { EXPECT_EQ(1.0f, abs_f(-1.0f)); }
TEST(AbsFloat, PosZero) { EXPECT_EQ(0.0f, abs_f(0.0f)); }
TEST(AbsFloat, NegZero) { EXPECT_EQ(0.0f, abs_f(-0.0f)); }
TEST(AbsFloat, PosInf) { EXPECT_EQ(F_INF, abs_f(F_INF)); }
TEST(AbsFloat, NegInf) { EXPECT_EQ(F_INF, abs_f(F_NEG_INF)); }
TEST(AbsFloat, NaN) { EXPECT_TRUE(is_nan_f(abs_f(f_nan()))); }
TEST(AbsFloat, Large) { EXPECT_FLOAT_EQ(1e30f, abs_f(-1e30f)); }

TEST(AbsDouble, Positive) { EXPECT_EQ(1.0, abs_d(1.0)); }
TEST(AbsDouble, Negative) { EXPECT_EQ(1.0, abs_d(-1.0)); }
TEST(AbsDouble, PosZero) { EXPECT_EQ(0.0, abs_d(0.0)); }
TEST(AbsDouble, NegZero) { EXPECT_EQ(0.0, abs_d(-0.0)); }
TEST(AbsDouble, PosInf) { EXPECT_EQ(D_INF, abs_d(D_INF)); }
TEST(AbsDouble, NegInf) { EXPECT_EQ(D_INF, abs_d(D_NEG_INF)); }
TEST(AbsDouble, NaN) { EXPECT_TRUE(is_nan_d(abs_d(d_nan()))); }
TEST(AbsDouble, Large) { EXPECT_DOUBLE_EQ(1e300, abs_d(-1e300)); }

// ═══════════════════════════════════════════════════════════════════════════════
// min_f / min_d
// ═══════════════════════════════════════════════════════════════════════════════
TEST(MinFloat, Smaller) { EXPECT_EQ(-1.0f, min_f(-1.0f, 1.0f)); }
TEST(MinFloat, Larger) { EXPECT_EQ(-1.0f, min_f(1.0f, -1.0f)); }
TEST(MinFloat, Equal) { EXPECT_EQ(1.0f, min_f(1.0f, 1.0f)); }
TEST(MinFloat, NegZeroNegZero) { EXPECT_TRUE(is_neg_zero_f(min_f(-0.0f, -0.0f))); }
TEST(MinFloat, NaNLeft) { EXPECT_EQ(2.0f, min_f(f_nan(), 2.0f)); }
TEST(MinFloat, NaNRight) { EXPECT_EQ(2.0f, min_f(2.0f, f_nan())); }
TEST(MinFloat, NegInf) { EXPECT_EQ(F_NEG_INF, min_f(F_NEG_INF, 1.0f)); }
TEST(MinFloat, PosInf) { EXPECT_EQ(1.0f, min_f(F_INF, 1.0f)); }

TEST(MinDouble, Smaller) { EXPECT_EQ(-1.0, min_d(-1.0, 1.0)); }
TEST(MinDouble, Larger) { EXPECT_EQ(-1.0, min_d(1.0, -1.0)); }
TEST(MinDouble, Equal) { EXPECT_EQ(1.0, min_d(1.0, 1.0)); }
TEST(MinDouble, NaNLeft) { EXPECT_EQ(2.0, min_d(d_nan(), 2.0)); }
TEST(MinDouble, NaNRight) { EXPECT_EQ(2.0, min_d(2.0, d_nan())); }
TEST(MinDouble, NegInf) { EXPECT_EQ(D_NEG_INF, min_d(D_NEG_INF, 1.0)); }
TEST(MinDouble, PosInf) { EXPECT_EQ(1.0, min_d(D_INF, 1.0)); }

// ═══════════════════════════════════════════════════════════════════════════════
// max_f / max_d
// ═══════════════════════════════════════════════════════════════════════════════
TEST(MaxFloat, Larger) { EXPECT_EQ(2.0f, max_f(2.0f, 1.0f)); }
TEST(MaxFloat, Smaller) { EXPECT_EQ(2.0f, max_f(1.0f, 2.0f)); }
TEST(MaxFloat, Equal) { EXPECT_EQ(1.0f, max_f(1.0f, 1.0f)); }
TEST(MaxFloat, NaNLeft) { EXPECT_EQ(2.0f, max_f(f_nan(), 2.0f)); }
TEST(MaxFloat, NaNRight) { EXPECT_EQ(2.0f, max_f(2.0f, f_nan())); }
TEST(MaxFloat, PosInf) { EXPECT_EQ(F_INF, max_f(F_INF, 1.0f)); }
TEST(MaxFloat, NegInf) { EXPECT_EQ(1.0f, max_f(F_NEG_INF, 1.0f)); }

TEST(MaxDouble, Larger) { EXPECT_EQ(2.0, max_d(2.0, 1.0)); }
TEST(MaxDouble, Smaller) { EXPECT_EQ(2.0, max_d(1.0, 2.0)); }
TEST(MaxDouble, Equal) { EXPECT_EQ(1.0, max_d(1.0, 1.0)); }
TEST(MaxDouble, NaNLeft) { EXPECT_EQ(2.0, max_d(d_nan(), 2.0)); }
TEST(MaxDouble, NaNRight) { EXPECT_EQ(2.0, max_d(2.0, d_nan())); }
TEST(MaxDouble, PosInf) { EXPECT_EQ(D_INF, max_d(D_INF, 1.0)); }
TEST(MaxDouble, NegInf) { EXPECT_EQ(1.0, max_d(D_NEG_INF, 1.0)); }

// ═══════════════════════════════════════════════════════════════════════════════
// clamp_f / clamp_d
// ═══════════════════════════════════════════════════════════════════════════════
TEST(ClampFloat, WithinRange) { EXPECT_EQ(0.5f, clamp_f(0.5f, 0.0f, 1.0f)); }
TEST(ClampFloat, BelowMin) { EXPECT_EQ(0.0f, clamp_f(-1.0f, 0.0f, 1.0f)); }
TEST(ClampFloat, AboveMax) { EXPECT_EQ(1.0f, clamp_f(2.0f, 0.0f, 1.0f)); }
TEST(ClampFloat, AtMin) { EXPECT_EQ(0.0f, clamp_f(0.0f, 0.0f, 1.0f)); }
TEST(ClampFloat, AtMax) { EXPECT_EQ(1.0f, clamp_f(1.0f, 0.0f, 1.0f)); }
TEST(ClampFloat, NegRange) { EXPECT_EQ(-1.0f, clamp_f(-1.0f, -5.0f, -1.0f)); }
TEST(ClampFloat, InfMax) { EXPECT_EQ(100.0f, clamp_f(100.0f, 0.0f, F_INF)); }
TEST(ClampFloat, NegInfMin) { EXPECT_EQ(-100.0f, clamp_f(-100.0f, F_NEG_INF, 0.0f)); }

TEST(ClampDouble, WithinRange) { EXPECT_EQ(0.5, clamp_d(0.5, 0.0, 1.0)); }
TEST(ClampDouble, BelowMin) { EXPECT_EQ(0.0, clamp_d(-1.0, 0.0, 1.0)); }
TEST(ClampDouble, AboveMax) { EXPECT_EQ(1.0, clamp_d(2.0, 0.0, 1.0)); }
TEST(ClampDouble, AtMin) { EXPECT_EQ(0.0, clamp_d(0.0, 0.0, 1.0)); }
TEST(ClampDouble, AtMax) { EXPECT_EQ(1.0, clamp_d(1.0, 0.0, 1.0)); }
TEST(ClampDouble, InfMax) { EXPECT_EQ(100.0, clamp_d(100.0, 0.0, D_INF)); }
TEST(ClampDouble, NegInfMin) { EXPECT_EQ(-100.0, clamp_d(-100.0, D_NEG_INF, 0.0)); }
