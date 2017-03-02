#include <iostream>
#include "myfunc.h"

int main(int argc, char *argv[])
{
    std::cout << "Hello Word" << std::endl;
    std::cout << "5 plus 6 is: " << add(5,6) << std::endl;
    std::cout << "Do something with 1234 is: " << dosmth(1234) << std::endl;
    std::cout << "Type in a number I will do somthing with it" << std::endl;
    int number;
    std::cin >>  number;
    std::cout << number << " -> " << dosmth(number) << std::endl;
    return 0;
}

