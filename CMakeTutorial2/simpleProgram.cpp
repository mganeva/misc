#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main (int argc, char* argv[]) {

   if(argc < 2) {
       fprintf(stdout, "Usage: %s number\n", argv[0]);
       return 1;
   }

   double inputVal = atof(argv[1]);
   double outputVal = sqrt(inputVal);
   fprintf(stdout, "The square root of %g is %g\n", inputVal, outputVal);
   return 0;

}
