#include <iostream>
#include <stdio.h>
#include "myfunc.h"
//#include"mysqrt.cpp"
#include "TutorialConfig.h"
#ifdef USE_MYMATH
#include "mysqrt.cpp"
#endif

int main(int argc, char *argv[]) {


    std::cout << "Hello Word" << std::endl;
    std::cout << "5 plus 6 is: " << add(5,6) << std::endl;
    std::cout << "Do something with 1234 is: " << dosmth(1234) << std::endl;
/*    std::cout << "Type in a number I will do somthing with it" << std::endl;
    int number;
    std::cin >>  number;
    std::cout << number << " -> " << dosmth(number) << std::endl;
*/
    if(argc < 2) {
        /*
        fprintf(stdout, "%s Version %d.%d\n",
                argv[0],
                Tutorial_VERSION_MAJOR,
                Tutorial_VERSION_MINOR);
                */
        fprintf(stdout, "Usage: %s number\n", argv[0]);
        return 1;
    }
    double inputVal = atof(argv[1]);
#ifdef USE_MYMATH
    double outputVal = mysqrt(inputVal);
#else
    double outputVal =  sqrt(inputVal);
#endif

    fprintf(stdout, "The square root of %g is %g\n", inputVal,outputVal);

    return 0;
}

