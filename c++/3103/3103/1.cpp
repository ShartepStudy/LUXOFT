#include<iostream>
using namespace std;

class P {
   int a;
public:
   P() { cout << "X()" << endl; }
   P(int n) { cout << "X(int)" << endl; }
   ~P() { cout << "X destr" << endl; }

};
class C: public P {};

void main() 
{
   cout << "jhfjweg \'jdfh\'fjsgfsdgj";
}