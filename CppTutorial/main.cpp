#include <iostream>
#include <fstream>

int main() {
    std::cout << "Enter two numbers:" << std::endl;
    int v1 = 0, v2 = 0;
    std::cin >> v1 >> v2;
    std::cout << "The product of " << v1;
    std::cout << " and " << v2;
    std::cout << " is: " << v1*v2 << std::endl;
    int val0 = 50, result = 0;
    while (val0 <= 100) {
        result += val0;
        val0 ++;
    }
    std::cout << result << std::endl;
    int ex10 = 10;
    while(ex10 >= 0) {
        std::cout << ex10 << " ";
        ex10--;
    }
    std::cout << std::endl;

    std::cout << "Enter two numbers:" << std::endl;
    int v3 = 0, v4 = 0;
    std::cin >> v3 >> v4;
    std::cout << "printing numbers from ";
    if(v3 < v4) {
        std::cout << v3 << " to " << v4 << std::endl;
        while(v3 <= v4) {
            std::cout << v3 << " ";
            v3++;
        }
     } else {
        std::cout << v4 << " to " << v3 << std::endl;
        while(v4 <= v3) {
            std::cout << v4 << " ";
            v4++;
        }
    }
    std::cout << std::endl;
    int sum = 0;

    for(int i = - 100; i <= 100; i++)
        sum +=  i;

    std::cout << sum << std::endl;

    int result2 = 0;
    for (int i = 50; i <= 100; i++) {
        result2 += i;
    }
    std::cout << result2 << std::endl;

    for( int j = 10; j >= 0 ;j--) {
        std::cout << j << " ";
    }
    std::cout << std::endl;

    int currVal = 0, val = 0;
    // read first number and ensure that we have data to process
    if (std::cin >> currVal) {
        int cnt = 1;  // store the count for the current value we're processing
        while (std::cin >> val) { // read the remaining numbers
            if (val == currVal)   // if the values are the same
                ++cnt;            // add 1 to cnt
            else { // otherwise, print the count for the previous value
                std::cout << currVal << " occurs "
                          << cnt << " times" << std::endl;
                currVal = val;    // remember the new value
                cnt = 1;          // reset the counter
            }
        }  // while loop ends here
        // remember to print the count for the last value in the file
        std::cout << currVal <<  " occurs "
                  << cnt << " times" << std::endl;
    } // outermost if statement ends here

   std::ofstream myfile;
   myfile.open ("example.txt");
   myfile << "Writing this to a file.\n";
   myfile.close();

   return 0;
}
