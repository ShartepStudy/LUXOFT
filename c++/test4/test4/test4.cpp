// test4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;
//
//class BE {};
//class DE : public BE {};
//void f() 
//{
//   try 
//   {
//      DE de;
//      throw de;
//   }
//   catch( BE & ) 
//   {
//      cout << "BE from f()\n";
//      throw;
//   }
//   catch( DE & ) 
//   {
//      cout << "DE from f()\n";
//      throw;
//   }
//
//}

int _tmain(int argc, _TCHAR* argv[])
{
   try {
      throw string("4");
   }
   catch( string & s)
   {
      try {
         cout << s;
         throw 2;
      }
      catch(int i) 
      {
         cout << i;
      }
      catch(...)
      {
         throw;
      }
      cout << "s" + s;
   }
   catch(...) { cout << "all"; }
   
   return 0;
}

