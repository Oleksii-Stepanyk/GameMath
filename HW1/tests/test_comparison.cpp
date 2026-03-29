// test_comparison.cpp – unit tests for comparison.h / comparison.c
#include <gtest/gtest.h>
#include <limits>

extern "C"
{
#include "comparison.h"
}

static constexpr float F_INF = std::numeric_limits<float>::infinity();
static constexpr float F_NEG_INF = -std::numeric_limits<float>::infinity();
static constexpr double D_INF = std::numeric_limits<double>::infinity();
static constexpr double D_NEG_INF = -std::numeric_limits<double>::infinity();

static float f_nan() { return std::numeric_limits<float>::quiet_NaN(); }
static double d_nan() { return std::numeric_limits<double>::quiet_NaN(); }

// ═══════════════════════════════════════════════════════════════════════════════
// equal_f / equal_d – exact equality
// ═══════════════════════════════════════════════════════════════════════════════
TEST(EqualFloat, SameValue) { EXPECT_TRUE(equal_f(1.0f, 1.0f)); }
TEST(EqualFloat, DifferentValues) { EXPECT_FALSE(equal_f(1.0f, 2.0f)); }
TEST(EqualFloat, BothPosZero) { EXPECT_TRUE(equal_f(0.0f, 0.0f)); }
TEST(EqualFloat, BothNegZero) { EXPECT_TRUE(equal_f(-0.0f, -0.0f)); }
TEST(EqualFloat, PosNegZero) { EXPECT_TRUE(equal_f(0.0f, -0.0f)); }
TEST(EqualFloat, BothPosInf) { EXPECT_TRUE(equal_f(F_INF, F_INF)); }
TEST(EqualFloat, BothNegInf) { EXPECT_TRUE(equal_f(F_NEG_INF, F_NEG_INF)); }
TEST(EqualFloat, PosNegInf) { EXPECT_FALSE(equal_f(F_INF, F_NEG_INF)); }
TEST(EqualFloat, NaNLeft) { EXPECT_FALSE(equal_f(f_nan(), 1.0f)); }
TEST(EqualFloat, NaNRight) { EXPECT_FALSE(equal_f(1.0f, f_nan())); }
TEST(EqualFloat, BothNaN) { EXPECT_FALSE(equal_f(f_nan(), f_nan())); }

TEST(EqualDouble, SameValue) { EXPECT_TRUE(equal_d(1.0, 1.0)); }
TEST(EqualDouble, DifferentValues) { EXPECT_FALSE(equal_d(1.0, 2.0)); }
TEST(EqualDouble, BothPosZero) { EXPECT_TRUE(equal_d(0.0, 0.0)); }
TEST(EqualDouble, PosNegZero) { EXPECT_TRUE(equal_d(0.0, -0.0)); }
TEST(EqualDouble, BothPosInf) { EXPECT_TRUE(equal_d(D_INF, D_INF)); }
TEST(EqualDouble, NaNLeft) { EXPECT_FALSE(equal_d(d_nan(), 1.0)); }
TEST(EqualDouble, BothNaN) { EXPECT_FALSE(equal_d(d_nan(), d_nan())); }

// ═══════════════════════════════════════════════════════════════════════════════
// equal_eps_f / equal_eps_d – epsilon equality
// ═══════════════════════════════════════════════════════════════════════════════
TEST(EqualEpsFloat, ExactEqual) { EXPECT_TRUE(equal_eps_f(1.0f, 1.0f, 1e-6f)); }
TEST(EqualEpsFloat, WithinEps) { EXPECT_TRUE(equal_eps_f(1.0f, 1.0f + 1e-7f, 1e-6f)); }
TEST(EqualEpsFloat, OutsideEps) { EXPECT_FALSE(equal_eps_f(1.0f, 1.0f + 0.1f, 1e-6f)); }
TEST(EqualEpsFloat, BothZero) { EXPECT_TRUE(equal_eps_f(0.0f, -0.0f, 1e-6f)); }
TEST(EqualEpsFloat, BothPosInf) { EXPECT_TRUE(equal_eps_f(F_INF, F_INF, 1e-6f)); }
TEST(EqualEpsFloat, InfVsNormal) { EXPECT_FALSE(equal_eps_f(F_INF, 1.0f, 1e-6f)); }
TEST(EqualEpsFloat, NaN) { EXPECT_FALSE(equal_eps_f(f_nan(), 1.0f, 1e-6f)); }

TEST(EqualEpsDouble, ExactEqual) { EXPECT_TRUE(equal_eps_d(1.0, 1.0, 1e-9)); }
TEST(EqualEpsDouble, WithinEps) { EXPECT_TRUE(equal_eps_d(1.0, 1.0 + 1e-10, 1e-9)); }
TEST(EqualEpsDouble, OutsideEps) { EXPECT_FALSE(equal_eps_d(1.0, 1.0 + 0.1, 1e-9)); }
TEST(EqualEpsDouble, BothZero) { EXPECT_TRUE(equal_eps_d(0.0, -0.0, 1e-9)); }
TEST(EqualEpsDouble, BothPosInf) { EXPECT_TRUE(equal_eps_d(D_INF, D_INF, 1e-9)); }
TEST(EqualEpsDouble, NaN) { EXPECT_FALSE(equal_eps_d(d_nan(), 1.0, 1e-9)); }

// ═══════════════════════════════════════════════════════════════════════════════
// less_f / less_d
// ═══════════════════════════════════════════════════════════════════════════════
TEST(LessFloat, Smaller) { EXPECT_TRUE(less_f(1.0f, 2.0f)); }
TEST(LessFloat, Equal) { EXPECT_FALSE(less_f(1.0f, 1.0f)); }
TEST(LessFloat, Larger) { EXPECT_FALSE(less_f(2.0f, 1.0f)); }
TEST(LessFloat, NegToPos) { EXPECT_TRUE(less_f(-1.0f, 1.0f)); }
TEST(LessFloat, NegInfToNegOne) { EXPECT_TRUE(less_f(F_NEG_INF, -1.0f)); }
TEST(LessFloat, OneToInf) { EXPECT_TRUE(less_f(1.0f, F_INF)); }
TEST(LessFloat, NaNLeft) { EXPECT_FALSE(less_f(f_nan(), 1.0f)); }
TEST(LessFloat, NaNRight) { EXPECT_FALSE(less_f(1.0f, f_nan())); }

TEST(LessDouble, Smaller) { EXPECT_TRUE(less_d(1.0, 2.0)); }
TEST(LessDouble, Equal) { EXPECT_FALSE(less_d(1.0, 1.0)); }
TEST(LessDouble, NaNLeft) { EXPECT_FALSE(less_d(d_nan(), 1.0)); }
TEST(LessDouble, NaNRight) { EXPECT_FALSE(less_d(1.0, d_nan())); }

// ═══════════════════════════════════════════════════════════════════════════════
// less_eps_f / less_eps_d
// ═══════════════════════════════════════════════════════════════════════════════
TEST(LessEpsFloat, ClearlyLess) { EXPECT_TRUE(less_eps_f(1.0f, 2.0f, 1e-6f)); }
TEST(LessEpsFloat, WithinEps) { EXPECT_FALSE(less_eps_f(1.0f, 1.0f + 1e-7f, 1e-6f)); }
TEST(LessEpsFloat, OutsideEps) { EXPECT_TRUE(less_eps_f(1.0f, 1.0f + 0.1f, 1e-6f)); }
TEST(LessEpsFloat, Equal) { EXPECT_FALSE(less_eps_f(1.0f, 1.0f, 1e-6f)); }
TEST(LessEpsFloat, NaN) { EXPECT_FALSE(less_eps_f(f_nan(), 1.0f, 1e-6f)); }
TEST(LessEpsFloat, NegInfToInf) { EXPECT_TRUE(less_eps_f(F_NEG_INF, F_INF, 1e-6f)); }

TEST(LessEpsDouble, ClearlyLess) { EXPECT_TRUE(less_eps_d(1.0, 2.0, 1e-9)); }
TEST(LessEpsDouble, WithinEps) { EXPECT_FALSE(less_eps_d(1.0, 1.0 + 1e-10, 1e-9)); }
TEST(LessEpsDouble, OutsideEps) { EXPECT_TRUE(less_eps_d(1.0, 1.0 + 0.1, 1e-9)); }
TEST(LessEpsDouble, NaN) { EXPECT_FALSE(less_eps_d(d_nan(), 1.0, 1e-9)); }

// ═══════════════════════════════════════════════════════════════════════════════
// greater_f / greater_d
// ═══════════════════════════════════════════════════════════════════════════════
TEST(GreaterFloat, Larger) { EXPECT_TRUE(greater_f(2.0f, 1.0f)); }
TEST(GreaterFloat, Equal) { EXPECT_FALSE(greater_f(1.0f, 1.0f)); }
TEST(GreaterFloat, Smaller) { EXPECT_FALSE(greater_f(1.0f, 2.0f)); }
TEST(GreaterFloat, PosToNeg) { EXPECT_TRUE(greater_f(1.0f, -1.0f)); }
TEST(GreaterFloat, InfToOne) { EXPECT_TRUE(greater_f(F_INF, 1.0f)); }
TEST(GreaterFloat, NegInfToVal) { EXPECT_FALSE(greater_f(F_NEG_INF, -1e30f)); }
TEST(GreaterFloat, NaNLeft) { EXPECT_FALSE(greater_f(f_nan(), 1.0f)); }
TEST(GreaterFloat, NaNRight) { EXPECT_FALSE(greater_f(1.0f, f_nan())); }

TEST(GreaterDouble, Larger) { EXPECT_TRUE(greater_d(2.0, 1.0)); }
TEST(GreaterDouble, Equal) { EXPECT_FALSE(greater_d(1.0, 1.0)); }
TEST(GreaterDouble, NaNLeft) { EXPECT_FALSE(greater_d(d_nan(), 1.0)); }
TEST(GreaterDouble, NaNRight) { EXPECT_FALSE(greater_d(1.0, d_nan())); }

// ═══════════════════════════════════════════════════════════════════════════════
// greater_eps_f / greater_eps_d
// ═══════════════════════════════════════════════════════════════════════════════
TEST(GreaterEpsFloat, ClearlyGtr) { EXPECT_TRUE(greater_eps_f(2.0f, 1.0f, 1e-6f)); }
TEST(GreaterEpsFloat, WithinEps) { EXPECT_FALSE(greater_eps_f(1.0f + 1e-7f, 1.0f, 1e-6f)); }
TEST(GreaterEpsFloat, OutsideEps) { EXPECT_TRUE(greater_eps_f(1.0f + 0.1f, 1.0f, 1e-6f)); }
TEST(GreaterEpsFloat, Equal) { EXPECT_FALSE(greater_eps_f(1.0f, 1.0f, 1e-6f)); }
TEST(GreaterEpsFloat, NaN) { EXPECT_FALSE(greater_eps_f(f_nan(), 1.0f, 1e-6f)); }
TEST(GreaterEpsFloat, InfToNegInf) { EXPECT_TRUE(greater_eps_f(F_INF, F_NEG_INF, 1e-6f)); }

TEST(GreaterEpsDouble, ClearlyGtr) { EXPECT_TRUE(greater_eps_d(2.0, 1.0, 1e-9)); }
TEST(GreaterEpsDouble, WithinEps) { EXPECT_FALSE(greater_eps_d(1.0 + 1e-10, 1.0, 1e-9)); }
TEST(GreaterEpsDouble, OutsideEps) { EXPECT_TRUE(greater_eps_d(1.0 + 0.1, 1.0, 1e-9)); }
TEST(GreaterEpsDouble, NaN) { EXPECT_FALSE(greater_eps_d(d_nan(), 1.0, 1e-9)); }
