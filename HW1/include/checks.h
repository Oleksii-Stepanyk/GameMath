#ifndef CHECKS_H
#define CHECKS_H

#include <inttypes.h>
#include <stdbool.h>

bool is_signed_f(float number);
bool is_signed_d(double number);

bool is_zero_f(float number);
bool is_zero_d(double number);

bool is_pos_zero_f(float number);
bool is_pos_zero_d(double number);

bool is_neg_zero_f(float number);
bool is_neg_zero_d(double number);

bool is_inf_f(float number);
bool is_inf_d(double number);

bool is_pos_inf_f(float number);
bool is_pos_inf_d(double number);

bool is_neg_inf_f(float number);
bool is_neg_inf_d(double number);

bool is_nan_f(float number);
bool is_nan_d(double number);

bool is_finite_f(float number);
bool is_finite_d(double number);

bool is_subnormal_f(float number);
bool is_subnormal_d(double number);

bool is_normal_f(float number);
bool is_normal_d(double number);

#endif // CHECKS_H