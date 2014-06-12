#include<iostream>
using namespace std;

class A 
{
   int x;
   int y;
};

class B 
{
   int x;
   int y;
   int * p;
};

class C 
{
   int x;
   int y;
   int & p;
public:
   C(int h):p(h) {};
};

class D 
{
   int x;
   int y;
   int & f;
   int & p;
public:
   D(int h):p(h), f(h) {};
};

struct Test1
{
   Test1(double pa, double pb) : a(pa), b(pb)
   {
   }
   double a;
   double b;
};

struct Test2
{
   double a;
   double b;
   double &r1;
   double &r2;

   Test2(double pa, double pb):a(pa), b(pb), r1(pa), r2(pb)
   {
   }
};

void main() 
{
   int a = 1;
   int b = 2;
   Test1 t1(a, b);
   Test2 t2(a,a);
   cout << sizeof(t1) << endl;
   cout << sizeof(t2) << endl;

  /* int hj=56;
   A a;
   B b;
   C c(hj);
   D d(hj);

   cout << sizeof(a) << endl ;
   cout << sizeof(b) << endl ;
   cout << sizeof(c) << endl ;
   cout << sizeof(d) << endl ;*/
}