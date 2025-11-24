#include "MathUtils.h"
#include <limits>
#include <stdexcept>

const double MathUtils::PI = 3.14159265358979323846;
const double MathUtils::E = 2.71828182845904523536;

double MathUtils::my_abs(double x) { return (x < 0) ? -x : x; }

double MathUtils::my_sqrt(double x) {
  if (x < 0) {
    throw std::invalid_argument("Square root of negative number");
  }
  if (x == 0)
    return 0;

  double guess = x;
  double epsilon = 1e-10;

  // Newton's method
  while (true) {
    double next_guess = 0.5 * (guess + x / guess);
    if (my_abs(guess - next_guess) < epsilon) {
      return next_guess;
    }
    guess = next_guess;
  }
}

double MathUtils::my_exp(double x) {
  // Taylor series for e^x = 1 + x + x^2/2! + x^3/3! + ...
  // For large x, this can be slow or inaccurate.
  // Optimization: e^x = (e^(x/2))^2

  if (x < 0) {
    return 1.0 / my_exp(-x);
  }

  double sum = 1.0;
  double term = 1.0;
  int n = 1;

  while (my_abs(term) > 1e-15) {
    term *= x / n;
    sum += term;
    n++;
    if (n > 1000)
      break; // Safety break
  }
  return sum;
}

double MathUtils::my_log(double x) {
  if (x <= 0) {
    throw std::invalid_argument("Logarithm of non-positive number");
  }

  // ln(x) = 2 * sum(( (x-1)/(x+1) )^(2n-1) / (2n-1))
  double term = (x - 1) / (x + 1);
  double term_squared = term * term;
  double sum = 0.0;
  double current_term = term;
  int n = 1;

  while (my_abs(current_term) > 1e-15) {
    sum += current_term / (2 * n - 1);
    current_term *= term_squared;
    n++;
    if (n > 1000)
      break;
  }

  return 2 * sum;
}

double MathUtils::my_pow(double base, double exp) {
  if (base == 0)
    return 0;
  if (exp == 0)
    return 1;
  if (base < 0 && exp != (int)exp) {
    throw std::invalid_argument("Negative base with non-integer exponent");
  }

  // x^y = e^(y * ln(x))
  if (base > 0) {
    return my_exp(exp * my_log(base));
  } else {
    // base < 0, exp is integer
    double res = my_exp(exp * my_log(-base));
    return ((int)exp % 2 == 0) ? res : -res;
  }
}

long long MathUtils::factorial(int n) {
  if (n < 0)
    return 0;
  if (n == 0 || n == 1)
    return 1;
  long long res = 1;
  for (int i = 2; i <= n; ++i)
    res *= i;
  return res;
}

double MathUtils::to_radians(double degrees) { return degrees * PI / 180.0; }

double MathUtils::my_sin(double x) {
  // Normalize x to [-PI, PI]
  while (x > PI)
    x -= 2 * PI;
  while (x < -PI)
    x += 2 * PI;

  double sum = 0.0;
  double term = x;
  int n = 1;

  while (my_abs(term) > 1e-15) {
    sum += term;
    term *= -1 * x * x / ((2 * n) * (2 * n + 1));
    n++;
    if (n > 100)
      break;
  }
  return sum;
}

double MathUtils::my_cos(double x) {
  // Normalize x to [-PI, PI]
  while (x > PI)
    x -= 2 * PI;
  while (x < -PI)
    x += 2 * PI;

  double sum = 0.0;
  double term = 1.0;
  int n = 0;

  while (my_abs(term) > 1e-15) {
    sum += term;
    term *= -1 * x * x / ((2 * n + 1) * (2 * n + 2));
    n++;
    if (n > 100)
      break;
  }
  return sum;
}

double MathUtils::my_tan(double x) {
  double c = my_cos(x);
  if (my_abs(c) < 1e-10) {
    throw std::invalid_argument("Tangent undefined");
  }
  return my_sin(x) / c;
}
