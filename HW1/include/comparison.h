#ifndef COMPARISON_H
#define COMPARISON_H

#include <stdbool.h>

bool equal_f(float a, float b);
bool equal_d(double a, double b);

bool equal_eps_f(float a, float b, float epsilon);
bool equal_eps_d(double a, double b, double epsilon);

bool less_f(float a, float b);
bool less_d(double a, double b);

bool less_eps_f(float a, float b, float epsilon);
bool less_eps_d(double a, double b, double epsilon);

bool greater_f(float a, float b);
bool greater_d(double a, double b);

bool greater_eps_f(float a, float b, float epsilon);
bool greater_eps_d(double a, double b, double epsilon);

#endif // COMPARISON_H