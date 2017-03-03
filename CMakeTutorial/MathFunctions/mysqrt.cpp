#include <iostream>
#include <math.h>

double mysqrt(double val) {
    /*
    std::cout << "In MathFunctions" << std::endl;
    return sqrt(val/2);
    */
    double result;
#if defined (HAVE_LOG) && defined (HAVE_EXP)
    result = exp(log(x)*0.5);
#else
    result = sqrt(val/2);
#endif
    return result;
}
