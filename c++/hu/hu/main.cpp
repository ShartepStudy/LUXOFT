#include<iostream>
using namespace std;

class T
{
public:
   int ma;
   char mb;
   double mc;
   T(int a, char b, double c): ma(a), mb(b), mc(c) {};
};

T & f()
{
   T * p=new T(1, 2, 3);
   return *p;
}
void main()
{
   T & s = f();

   cout << s.ma << endl;
   cout << s.mb << endl;
   cout << s.mc << endl;
}