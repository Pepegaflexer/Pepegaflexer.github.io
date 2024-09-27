#include "s21_math.h"

long double s21_tan(double x) {
  long double res = 0.0;
  if (s21_fabs(x) == S21_INF || s21_isNan(x)) {
    res = S21_NAN;
  } else {
    res = s21_sin(x) / s21_cos(x);
  }
  return res;
}
