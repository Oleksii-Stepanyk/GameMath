// test_classification.cpp – unit tests for classification.h / classification.c
#include <gtest/gtest.h>
#include <limits>

extern "C"
{
#include "classification.h"
}

static constexpr float F_INF = std::numeric_limits<float>::infinity();
static constexpr float F_NEG_INF = -std::numeric_limits<float>::infinity();
static constexpr double D_INF = std::numeric_limits<double>::infinity();
static constexpr double D_NEG_INF = -std::numeric_limits<double>::infinity();
static constexpr float F_SUBNORM = std::numeric_limits<float>::denorm_min();
static constexpr double D_SUBNORM = std::numeric_limits<double>::denorm_min();

static float f_nan() { return std::numeric_limits<float>::quiet_NaN(); }
static double d_nan() { return std::numeric_limits<double>::quiet_NaN(); }

// ═══════════════════════════════════════════════════════════════════════════════
// classify_f
// ═══════════════════════════════════════════════════════════════════════════════
TEST(ClassifyFloat, PosZero) { EXPECT_EQ(FP_ZERO, classify_f(0.0f)); }
TEST(ClassifyFloat, NegZero) { EXPECT_EQ(FP_ZERO, classify_f(-0.0f)); }
TEST(ClassifyFloat, PosInf) { EXPECT_EQ(FP_INFINITE, classify_f(F_INF)); }
TEST(ClassifyFloat, NegInf) { EXPECT_EQ(FP_INFINITE, classify_f(F_NEG_INF)); }
TEST(ClassifyFloat, NaN) { EXPECT_EQ(FP_NAN, classify_f(f_nan())); }
TEST(ClassifyFloat, Subnormal) { EXPECT_EQ(FP_SUBNORMAL, classify_f(F_SUBNORM)); }
TEST(ClassifyFloat, Normal) { EXPECT_EQ(FP_NORMAL, classify_f(1.0f)); }
TEST(ClassifyFloat, NegNormal) { EXPECT_EQ(FP_NORMAL, classify_f(-42.5f)); }
TEST(ClassifyFloat, SmallNormal) { EXPECT_EQ(FP_NORMAL, classify_f(std::numeric_limits<float>::min())); }
TEST(ClassifyFloat, MaxNormal) { EXPECT_EQ(FP_NORMAL, classify_f(std::numeric_limits<float>::max())); }

// ═══════════════════════════════════════════════════════════════════════════════
// classify_d
// ═══════════════════════════════════════════════════════════════════════════════
TEST(ClassifyDouble, PosZero) { EXPECT_EQ(FP_ZERO, classify_d(0.0)); }
TEST(ClassifyDouble, NegZero) { EXPECT_EQ(FP_ZERO, classify_d(-0.0)); }
TEST(ClassifyDouble, PosInf) { EXPECT_EQ(FP_INFINITE, classify_d(D_INF)); }
TEST(ClassifyDouble, NegInf) { EXPECT_EQ(FP_INFINITE, classify_d(D_NEG_INF)); }
TEST(ClassifyDouble, NaN) { EXPECT_EQ(FP_NAN, classify_d(d_nan())); }
TEST(ClassifyDouble, Subnormal) { EXPECT_EQ(FP_SUBNORMAL, classify_d(D_SUBNORM)); }
TEST(ClassifyDouble, Normal) { EXPECT_EQ(FP_NORMAL, classify_d(1.0)); }
TEST(ClassifyDouble, NegNormal) { EXPECT_EQ(FP_NORMAL, classify_d(-42.5)); }
TEST(ClassifyDouble, SmallNormal) { EXPECT_EQ(FP_NORMAL, classify_d(std::numeric_limits<double>::min())); }
TEST(ClassifyDouble, MaxNormal) { EXPECT_EQ(FP_NORMAL, classify_d(std::numeric_limits<double>::max())); }
