#include <iostream>
#include <math.h>

double mysqrt(double val) {
    /*
    std::cout << "In MathFunctions" << std::endl;
    return sqrt(val/2);
    */
    double result;

#ifdef HAVE_LOG
    std::cout << "smth wrong with defined" << std::endl;
#endif

#if(defined (HAVE_LOG) && defined (HAVE_EXP))
    result = exp(log(val)*0.5);
#else
    result = sqrt(val/2);
#endif
    return result;
}
