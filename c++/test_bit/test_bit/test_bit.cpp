// test_bit.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Cl.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
   cl ob;
   ob.f = 25;
   cout << sizeof(ob) << "\n";
   cout << atoi(ob.f) << "\n";

	return 0;
}

