// test_checks.cpp – unit tests for checks.h / checks.c
#include <gtest/gtest.h>
#include <limits>

extern "C"
{
#include "checks.h"
}

// ─────────────────────────── helpers ─────────────────────────────────────────
static constexpr float F_INF = std::numeric_limits<float>::infinity();
static constexpr float F_NEG_INF = -std::numeric_limits<float>::infinity();
static constexpr double D_INF = std::numeric_limits<double>::infinity();
static constexpr double D_NEG_INF = -std::numeric_limits<double>::infinity();

static float f_nan() { return std::numeric_limits<float>::quiet_NaN(); }
static double d_nan() { return std::numeric_limits<double>::quiet_NaN(); }

// smallest positive subnormal
static constexpr float F_SUBNORM = std::numeric_limits<float>::denorm_min();
static constexpr double D_SUBNORM = std::numeric_limits<double>::denorm_min();

// smallest positive normal
static constexpr float F_NORM_MIN = std::numeric_limits<float>::min();
static constexpr double D_NORM_MIN = std::numeric_limits<double>::min();

// ═══════════════════════════════════════════════════════════════════════════════
// is_signed
// ═══════════════════════════════════════════════════════════════════════════════
TEST(IsSignedFloat, Positive) { EXPECT_FALSE(is_signed_f(1.0f)); }
TEST(IsSignedFloat, Negative) { EXPECT_TRUE(is_signed_f(-1.0f)); }
TEST(IsSignedFloat, PosZero) { EXPECT_FALSE(is_signed_f(0.0f)); }
TEST(IsSignedFloat, NegZero) { EXPECT_TRUE(is_signed_f(-0.0f)); }
TEST(IsSignedFloat, PosInf) { EXPECT_FALSE(is_signed_f(F_INF)); }
TEST(IsSignedFloat, NegInf) { EXPECT_TRUE(is_signed_f(F_NEG_INF)); }

TEST(IsSignedDouble, Positive) { EXPECT_FALSE(is_signed_d(1.0)); }
TEST(IsSignedDouble, Negative) { EXPECT_TRUE(is_signed_d(-1.0)); }
TEST(IsSignedDouble, PosZero) { EXPECT_FALSE(is_signed_d(0.0)); }
TEST(IsSignedDouble, NegZero) { EXPECT_TRUE(is_signed_d(-0.0)); }
TEST(IsSignedDouble, PosInf) { EXPECT_FALSE(is_signed_d(D_INF)); }
TEST(IsSignedDouble, NegInf) { EXPECT_TRUE(is_signed_d(D_NEG_INF)); }

// ═══════════════════════════════════════════════════════════════════════════════
// is_zero
// ═══════════════════════════════════════════════════════════════════════════════
TEST(IsZeroFloat, PosZero) { EXPECT_TRUE(is_zero_f(0.0f)); }
TEST(IsZeroFloat, NegZero) { EXPECT_TRUE(is_zero_f(-0.0f)); }
TEST(IsZeroFloat, Positive) { EXPECT_FALSE(is_zero_f(1.0f)); }
TEST(IsZeroFloat, Negative) { EXPECT_FALSE(is_zero_f(-1.0f)); }
TEST(IsZeroFloat, PosInf) { EXPECT_FALSE(is_zero_f(F_INF)); }

TEST(IsZeroDouble, PosZero) { EXPECT_TRUE(is_zero_d(0.0)); }
TEST(IsZeroDouble, NegZero) { EXPECT_TRUE(is_zero_d(-0.0)); }
TEST(IsZeroDouble, Positive) { EXPECT_FALSE(is_zero_d(1.0)); }
TEST(IsZeroDouble, Negative) { EXPECT_FALSE(is_zero_d(-1.0)); }
TEST(IsZeroDouble, PosInf) { EXPECT_FALSE(is_zero_d(D_INF)); }

// ═══════════════════════════════════════════════════════════════════════════════
// is_pos_zero / is_neg_zero
// ═══════════════════════════════════════════════════════════════════════════════
TEST(IsPosZeroFloat, PosZero) { EXPECT_TRUE(is_pos_zero_f(0.0f)); }
TEST(IsPosZeroFloat, NegZero) { EXPECT_FALSE(is_pos_zero_f(-0.0f)); }
TEST(IsPosZeroFloat, Positive) { EXPECT_FALSE(is_pos_zero_f(1.0f)); }

TEST(IsPosZeroDouble, PosZero) { EXPECT_TRUE(is_pos_zero_d(0.0)); }
TEST(IsPosZeroDouble, NegZero) { EXPECT_FALSE(is_pos_zero_d(-0.0)); }
TEST(IsPosZeroDouble, Positive) { EXPECT_FALSE(is_pos_zero_d(1.0)); }

TEST(IsNegZeroFloat, NegZero) { EXPECT_TRUE(is_neg_zero_f(-0.0f)); }
TEST(IsNegZeroFloat, PosZero) { EXPECT_FALSE(is_neg_zero_f(0.0f)); }
TEST(IsNegZeroFloat, Negative) { EXPECT_FALSE(is_neg_zero_f(-1.0f)); }

TEST(IsNegZeroDouble, NegZero) { EXPECT_TRUE(is_neg_zero_d(-0.0)); }
TEST(IsNegZeroDouble, PosZero) { EXPECT_FALSE(is_neg_zero_d(0.0)); }
TEST(IsNegZeroDouble, Negative) { EXPECT_FALSE(is_neg_zero_d(-1.0)); }

// ═══════════════════════════════════════════════════════════════════════════════
// is_inf
// ═══════════════════════════════════════════════════════════════════════════════
TEST(IsInfFloat, PosInf) { EXPECT_TRUE(is_inf_f(F_INF)); }
TEST(IsInfFloat, NegInf) { EXPECT_TRUE(is_inf_f(F_NEG_INF)); }
TEST(IsInfFloat, Normal) { EXPECT_FALSE(is_inf_f(1.0f)); }
TEST(IsInfFloat, Zero) { EXPECT_FALSE(is_inf_f(0.0f)); }
TEST(IsInfFloat, NaN) { EXPECT_FALSE(is_inf_f(f_nan())); }

TEST(IsInfDouble, PosInf) { EXPECT_TRUE(is_inf_d(D_INF)); }
TEST(IsInfDouble, NegInf) { EXPECT_TRUE(is_inf_d(D_NEG_INF)); }
TEST(IsInfDouble, Normal) { EXPECT_FALSE(is_inf_d(1.0)); }
TEST(IsInfDouble, Zero) { EXPECT_FALSE(is_inf_d(0.0)); }
TEST(IsInfDouble, NaN) { EXPECT_FALSE(is_inf_d(d_nan())); }

TEST(IsPosInfFloat, PosInf) { EXPECT_TRUE(is_pos_inf_f(F_INF)); }
TEST(IsPosInfFloat, NegInf) { EXPECT_FALSE(is_pos_inf_f(F_NEG_INF)); }
TEST(IsPosInfFloat, Normal) { EXPECT_FALSE(is_pos_inf_f(1.0f)); }

TEST(IsPosInfDouble, PosInf) { EXPECT_TRUE(is_pos_inf_d(D_INF)); }
TEST(IsPosInfDouble, NegInf) { EXPECT_FALSE(is_pos_inf_d(D_NEG_INF)); }
TEST(IsPosInfDouble, Normal) { EXPECT_FALSE(is_pos_inf_d(1.0)); }

TEST(IsNegInfFloat, NegInf) { EXPECT_TRUE(is_neg_inf_f(F_NEG_INF)); }
TEST(IsNegInfFloat, PosInf) { EXPECT_FALSE(is_neg_inf_f(F_INF)); }
TEST(IsNegInfFloat, Normal) { EXPECT_FALSE(is_neg_inf_f(-1.0f)); }

TEST(IsNegInfDouble, NegInf) { EXPECT_TRUE(is_neg_inf_d(D_NEG_INF)); }
TEST(IsNegInfDouble, PosInf) { EXPECT_FALSE(is_neg_inf_d(D_INF)); }
TEST(IsNegInfDouble, Normal) { EXPECT_FALSE(is_neg_inf_d(-1.0)); }

// ═══════════════════════════════════════════════════════════════════════════════
// is_nan
// ═══════════════════════════════════════════════════════════════════════════════
TEST(IsNanFloat, NaN) { EXPECT_TRUE(is_nan_f(f_nan())); }
TEST(IsNanFloat, PosInf) { EXPECT_FALSE(is_nan_f(F_INF)); }
TEST(IsNanFloat, Normal) { EXPECT_FALSE(is_nan_f(1.0f)); }
TEST(IsNanFloat, Zero) { EXPECT_FALSE(is_nan_f(0.0f)); }

TEST(IsNanDouble, NaN) { EXPECT_TRUE(is_nan_d(d_nan())); }
TEST(IsNanDouble, PosInf) { EXPECT_FALSE(is_nan_d(D_INF)); }
TEST(IsNanDouble, Normal) { EXPECT_FALSE(is_nan_d(1.0)); }
TEST(IsNanDouble, Zero) { EXPECT_FALSE(is_nan_d(0.0)); }

// ═══════════════════════════════════════════════════════════════════════════════
// is_finite
// ═══════════════════════════════════════════════════════════════════════════════
TEST(IsFiniteFloat, Normal) { EXPECT_TRUE(is_finite_f(1.0f)); }
TEST(IsFiniteFloat, Zero) { EXPECT_TRUE(is_finite_f(0.0f)); }
TEST(IsFiniteFloat, Subnormal) { EXPECT_TRUE(is_finite_f(F_SUBNORM)); }
TEST(IsFiniteFloat, PosInf) { EXPECT_FALSE(is_finite_f(F_INF)); }
TEST(IsFiniteFloat, NegInf) { EXPECT_FALSE(is_finite_f(F_NEG_INF)); }
TEST(IsFiniteFloat, NaN) { EXPECT_FALSE(is_finite_f(f_nan())); }

TEST(IsFiniteDouble, Normal) { EXPECT_TRUE(is_finite_d(1.0)); }
TEST(IsFiniteDouble, Zero) { EXPECT_TRUE(is_finite_d(0.0)); }
TEST(IsFiniteDouble, Subnormal) { EXPECT_TRUE(is_finite_d(D_SUBNORM)); }
TEST(IsFiniteDouble, PosInf) { EXPECT_FALSE(is_finite_d(D_INF)); }
TEST(IsFiniteDouble, NegInf) { EXPECT_FALSE(is_finite_d(D_NEG_INF)); }
TEST(IsFiniteDouble, NaN) { EXPECT_FALSE(is_finite_d(d_nan())); }

// ═══════════════════════════════════════════════════════════════════════════════
// is_subnormal
// ═══════════════════════════════════════════════════════════════════════════════
TEST(IsSubnormalFloat, Subnormal) { EXPECT_TRUE(is_subnormal_f(F_SUBNORM)); }
TEST(IsSubnormalFloat, Normal) { EXPECT_FALSE(is_subnormal_f(F_NORM_MIN)); }
TEST(IsSubnormalFloat, Zero) { EXPECT_FALSE(is_subnormal_f(0.0f)); }
TEST(IsSubnormalFloat, PosInf) { EXPECT_FALSE(is_subnormal_f(F_INF)); }
TEST(IsSubnormalFloat, NaN) { EXPECT_FALSE(is_subnormal_f(f_nan())); }

TEST(IsSubnormalDouble, Subnormal) { EXPECT_TRUE(is_subnormal_d(D_SUBNORM)); }
TEST(IsSubnormalDouble, Normal) { EXPECT_FALSE(is_subnormal_d(D_NORM_MIN)); }
TEST(IsSubnormalDouble, Zero) { EXPECT_FALSE(is_subnormal_d(0.0)); }
TEST(IsSubnormalDouble, PosInf) { EXPECT_FALSE(is_subnormal_d(D_INF)); }
TEST(IsSubnormalDouble, NaN) { EXPECT_FALSE(is_subnormal_d(d_nan())); }

// ═══════════════════════════════════════════════════════════════════════════════
// is_normal
// ═══════════════════════════════════════════════════════════════════════════════
TEST(IsNormalFloat, Normal) { EXPECT_TRUE(is_normal_f(1.0f)); }
TEST(IsNormalFloat, NormMin) { EXPECT_TRUE(is_normal_f(F_NORM_MIN)); }
TEST(IsNormalFloat, Zero) { EXPECT_FALSE(is_normal_f(0.0f)); }
TEST(IsNormalFloat, Subnormal) { EXPECT_FALSE(is_normal_f(F_SUBNORM)); }
TEST(IsNormalFloat, PosInf) { EXPECT_FALSE(is_normal_f(F_INF)); }
TEST(IsNormalFloat, NaN) { EXPECT_FALSE(is_normal_f(f_nan())); }

TEST(IsNormalDouble, Normal) { EXPECT_TRUE(is_normal_d(1.0)); }
TEST(IsNormalDouble, NormMin) { EXPECT_TRUE(is_normal_d(D_NORM_MIN)); }
TEST(IsNormalDouble, Zero) { EXPECT_FALSE(is_normal_d(0.0)); }
TEST(IsNormalDouble, Subnormal) { EXPECT_FALSE(is_normal_d(D_SUBNORM)); }
TEST(IsNormalDouble, PosInf) { EXPECT_FALSE(is_normal_d(D_INF)); }
TEST(IsNormalDouble, NaN) { EXPECT_FALSE(is_normal_d(d_nan())); }
