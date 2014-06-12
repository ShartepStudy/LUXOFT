#include <iostream>

using namespace std;

struct _test1
{
   char a;
   int b;
   int c;
   double d;
} test1;

#pragma pack(push, 4)
struct _test2
{
   char a;
   int b;
   int c;
   double d;
} test2;
#pragma pack(pop)


void main() 
{
   cout << "test1: " << sizeof(test1) << "\n";
   cout << "test2: " << sizeof(test2) << "\n";
}