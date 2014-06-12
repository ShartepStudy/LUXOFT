#include <math.h>
#include <iostream>


void main() 
{
   float a=1, b=8, c=3, d;

   ((d=b*b-4*a*c) >= 0 ) ? 
      (printf("x1=%f  x2=%f\n", (-b + sqrt(d))/(2*a), (-b-sqrt(d))/(2*a) ) ) : 
      printf("error no solutions!\n");
}