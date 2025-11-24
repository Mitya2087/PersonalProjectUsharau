#ifndef MATHUTILS_H
#define MATHUTILS_H

#include <string>

class MathUtils {
public:
    static const double PI;
    static const double E;

    static double my_abs(double x);
    static double my_sqrt(double x);
    static double my_pow(double base, double exp);
    static double my_exp(double x);
    static double my_log(double x); // Natural log
    static double my_sin(double x);
    static double my_cos(double x);
    static double my_tan(double x);
    
    static long long factorial(int n);
    
    // Helper to convert degrees to radians
    static double to_radians(double degrees);
};

#endif // MATHUTILS_H
