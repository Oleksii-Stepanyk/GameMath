#ifndef MATH_H
#define MATH_H

float abs_f(float number);
double abs_d(double number);

float min_f(float a, float b);
double min_d(double a, double b);

float max_f(float a, float b);
double max_d(double a, double b);

float clamp_f(float number, float min, float max);
double clamp_d(double number, double min, double max);

#endif // MATH_H