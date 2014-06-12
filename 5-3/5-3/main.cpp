#include <iostream>
using namespace std;

class CMatrix 
{
   int mData[5][5];
public:
   void CMatrix::init();
   void print();
   void setData(int i, int j, int data) { mData[i][j]=data; }
   int getData(int i, int j) { return mData[i][j]; }

   CMatrix operator~();
   CMatrix operator+(CMatrix obj2);
   CMatrix operator-(CMatrix obj2);
   CMatrix operator+(int data);
};

void CMatrix::init() 
{
   for (int i=0; i<5; i++)
   {
      for (int j=0; j<5; j++)
      {
         mData[i][j] = rand() % 10;
      }
   }
}

void CMatrix::print() 
{
   for (int i=0; i<5; i++)
   {
      for (int j=0; j<5; j++)
      {
         printf("%5d", mData[i][j]);
      }
      printf("\n");
   }
}

CMatrix CMatrix::operator~() 
{
   CMatrix result;
   for (int i=0; i<5; i++)
   {
      for (int j=0; j<5; j++)
      {
         result.setData(i, j, mData[j][i]);
      }
   }
   return result;
}

CMatrix CMatrix::operator+(CMatrix obj2) 
{
   CMatrix result;
   for (int i=0; i<5; i++)
   {
      for (int j=0; j<5; j++)
      {
         result.setData(i, j, mData[i][j] + obj2.mData[i][j]);
      }
   }
   return result;
}

CMatrix CMatrix::operator-(CMatrix obj2) 
{
   CMatrix result;
   for (int i=0; i<5; i++)
   {
      for (int j=0; j<5; j++)
      {
         result.setData(i, j, mData[i][j] - obj2.mData[i][j]);
      }
   }
   return result;
}

CMatrix CMatrix::operator+(int data) 
{
   CMatrix result;
   for (int i=0; i<5; i++)
   {
      for (int j=0; j<5; j++)
      {
         result.setData(i, j, mData[i][j] + data);
      }
   }
   return result;
}

CMatrix operator+(int data, CMatrix obj) 
{
   CMatrix result;
   for (int i=0; i<5; i++)
   {
      for (int j=0; j<5; j++)
      {
         result.setData(i, j, obj.getData(i,j) + data);
      }
   }
   return result;
}

void main() 
{
   CMatrix a, b;

   a.init();
   a.print();
   printf("\n");

   b.init();
   b.print();

   CMatrix e;
   e = ~a;
   printf("\n~A\n");
   e.print();

   CMatrix c;
   c = a + b;
   printf("\nA + B \n");
   c.print();

   CMatrix f;
   f = a - b;
   printf("\nA - B \n");
   f.print();

   CMatrix d;
   d = a + 5;
   printf("\nA + 5 \n");
   d.print();

   CMatrix g;
   g = 5 + a ;
   printf("\n 5 + A \n");
   g.print();

}