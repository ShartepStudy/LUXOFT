#include<iostream>
using namespace std;

struct date 
{
   int day;
   int mounth;
   int year;
};

struct employee 
{
   char name[30];
   int employee_no;
   struct date dob;
};

union myUnion
{
   int intArray[5];
   float floatArray[5];
};

union myUnion unionArray[20];
void * ptr;

class mclass {
   mclass & operator = (const mclass &) ;
   void p(int g) {};
};

   //mclass & mclass::operator = (const mclass &) = delete;

void main() 
{
   int * p = new int[10];

   delete p;
}
