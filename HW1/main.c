#include <stdio.h>

#include "checks.h"

#define CHECK(label, expr) printf("  [%s] %s\n", (expr) ? "PASS" : "FAIL", label)

static void test_is_signed(void)
{
    puts("=== is_signed ===");
    CHECK("float:  1.0f  -> false", !is_signed_f(1.0f));
    CHECK("float: -1.0f  -> true",   is_signed_f(-1.0f));
    CHECK("float: +0.0f  -> false", !is_signed_f(0.0f));
    CHECK("float: -0.0f  -> true",   is_signed_f(-0.0f));

    CHECK("double:  1.0  -> false", !is_signed_d(1.0));
    CHECK("double: -1.0  -> true",   is_signed_d(-1.0));
    CHECK("double: +0.0  -> false", !is_signed_d(0.0));
    CHECK("double: -0.0  -> true",   is_signed_d(-0.0));
}

static void test_is_zero(void)
{
    puts("=== is_zero ===");
    CHECK("float: +0.0f -> true",   is_zero_f(0.0f));
    CHECK("float: -0.0f -> true",   is_zero_f(-0.0f));
    CHECK("float:  1.0f -> false", !is_zero_f(1.0f));
    CHECK("float: -1.0f -> false", !is_zero_f(-1.0f));

    CHECK("double: +0.0 -> true",   is_zero_d(0.0));
    CHECK("double: -0.0 -> true",   is_zero_d(-0.0));
    CHECK("double:  1.0 -> false", !is_zero_d(1.0));
    CHECK("double: -1.0 -> false", !is_zero_d(-1.0));
}

static void test_is_pos_zero(void)
{
    puts("=== is_pos_zero ===");
    CHECK("float: +0.0f -> true",   is_pos_zero_f(0.0f));
    CHECK("float: -0.0f -> false", !is_pos_zero_f(-0.0f));
    CHECK("float:  1.0f -> false", !is_pos_zero_f(1.0f));

    CHECK("double: +0.0 -> true",   is_pos_zero_d(0.0));
    CHECK("double: -0.0 -> false", !is_pos_zero_d(-0.0));
    CHECK("double:  1.0 -> false", !is_pos_zero_d(1.0));
}

static void test_is_neg_zero(void)
{
    puts("=== is_neg_zero ===");
    CHECK("float: -0.0f -> true",   is_neg_zero_f(-0.0f));
    CHECK("float: +0.0f -> false", !is_neg_zero_f(0.0f));
    CHECK("float: -1.0f -> false", !is_neg_zero_f(-1.0f));

    CHECK("double: -0.0 -> true",   is_neg_zero_d(-0.0));
    CHECK("double: +0.0 -> false", !is_neg_zero_d(0.0));
    CHECK("double: -1.0 -> false", !is_neg_zero_d(-1.0));
}

int main(void)
{
    test_is_signed();
    test_is_zero();
    test_is_pos_zero();
    test_is_neg_zero();
    return 0;
}