#include <math.h>
#include <iostream>
using namespace std;

typedef unsigned short ushort;
const char BIT_IN_INT = 32;

class CPackedArray 
{
private:
   unsigned int * mData;
   char mBitPerCell;
   ushort mSize; 

   // ������ CProxy � CProxy2 ���������� ��� ���������� ���������� ��������� [][]
   // ����������� ������������� 
   // � ���� ����������� ���� Array[i][j] = data ������ Array.set(i,j,data) �
   // cout << Array[i][j]() ������ cout << Array.get(i,j)
   class CProxy2
   {
   private:
      CPackedArray *mObj;
      ushort mX;
      ushort mY;
   public:
      CProxy2(CPackedArray *obj, ushort x, ushort y);
      void operator=(int data);
      int operator()();
   };

   class CProxy
   {
   private:
      CPackedArray *mObj;
      ushort mY;
   public:
      CProxy(CPackedArray *obj, ushort y);
      CProxy2 operator[](ushort x);
   };

public:
   CPackedArray(ushort size);
   ~CPackedArray();

   void set(ushort y, ushort x, int data);
   int get(ushort y, ushort x);

   CProxy operator[](ushort y);
};

CPackedArray::CPackedArray(ushort size) 
   : mSize(size)
{
   // ������ ���-�� ��� ����������� ��� �������� ����� �� 0 �� size-1
   mBitPerCell = log( (double)size-1 ) / log( 2.0 ) + 1; 

   // ������ ���-�� ��� ����������� ��� �������� ����� �������
   unsigned long long arrayBitSize = size*size*mBitPerCell;

   // ������ ���-�� ���� ����������� ��� �������� ����� �������, � ����������� � ������� �������
   unsigned long long arraySize = arrayBitSize / BIT_IN_INT;

   // � ������ ���� ��� ���������� �������� �������������� ����������, ����������� ��-�� ���� �� 1
   if ( arrayBitSize % BIT_IN_INT )
      arraySize++;

   // ��������� ������������ ������ ��� �������
   mData = new unsigned int[arraySize];
}

CPackedArray::~CPackedArray() 
{
   // ������������ ������������ ������ ��� �������
   delete [] mData;
}

void CPackedArray::set(ushort y, ushort x, int data) 
{
   // ��������, ��������� ����� �� ��������� � �������� �� 0 �� size-1
   if ( data > pow( 2.0, mBitPerCell ) ) 
   {
      cout << "ERROR!!! Data overflow!";
      exit(0);
   }

   // ������ ������ (�������� ������������ ��������� mData) � ����� (����� ���������� ������)
   unsigned long long bitOffset = ( y*mSize + x )*mBitPerCell;

   // ������ ������ (�������� ������������ ��������� mData) � ������ (����� ���������� ������), 
   // � ����������� � ������� �������
   unsigned long long indexOffset = bitOffset / BIT_IN_INT;

   // ������ �������� � ����� ������������ ������ mData + indexOffset
   char localBitOffset = bitOffset % BIT_IN_INT;

   // �������� ����� (���� 1111 1111 1111 1111 1111 0000 1111 1111, ��� 0000 ��������� ����),
   // � ������� ������� ������ ����� ������� ������ 
   unsigned int clearMask = ~(((unsigned int)pow( 2.0, mBitPerCell ) - 1) << localBitOffset ); 
   *(mData + indexOffset) &= clearMask;        
   
   // ������ ������ � ������
   data <<= localBitOffset;
   *(mData + indexOffset) |= data;        
}

int CPackedArray::get(ushort y, ushort x) 
{
   unsigned long long bitOffset = ( y*mSize + x )*mBitPerCell;
   unsigned long long byteOffset = bitOffset / BIT_IN_INT;
   char localBitOffset = bitOffset % BIT_IN_INT;

   // ���������� ������ �� ������������ ������
   unsigned int data = *(mData + byteOffset) >> localBitOffset;
   
   // �������� ����� (���� 0000 0000 0000 0000 0000 0000 1111 1111, ��� 0000 ��������� ����)
   unsigned int dataMask = 0xFFFFFFFF >> (BIT_IN_INT - mBitPerCell); 

   // ������� ������ �� ������ ���
   return data & dataMask;
}

CPackedArray::CProxy CPackedArray::operator[](ushort y)
{
   // ���������� ����� ������ CProxy, ���������� ����� ������� ���
   // Array[y][x] � proxy[x], y ��������� � ���� mY
   return CProxy(this, y);
}

CPackedArray::CProxy::CProxy(CPackedArray *obj, ushort y)
   : mObj(obj)
   , mY(y)
{}

CPackedArray::CProxy2 CPackedArray::CProxy::operator[](ushort x)
{   
   // ���������� ����� ������ CProxy2, ���������� ����� ������� ���
   // proxy[x] � proxy2, y ��������� � ���� mY, x ��������� � ���� m�
   return CProxy2(mObj, x, mY);
}

CPackedArray::CProxy2::CProxy2(CPackedArray *obj, ushort x, ushort y)
   : mObj(obj)
   , mX(x)
   , mY(y)
{}

void CPackedArray::CProxy2::operator=(int data) 
{
   mObj->set( mY,mX,data );
}

int CPackedArray::CProxy2::operator()() 
{
   return mObj->get( mY,mX );
}

void main() 
{
   int t;
   CPackedArray M(10); // �������� ������� �������� 10
   
   // ���������� ������� ���������� ������� � ����� �� �� �����
   for (int y=0; y<10; y++)
   {
      for (int x=0; x<10; x++)
      {
         t = rand()%10;
         M[y][x] = t;
         cout << t << "  ";
      }
      cout << '\n';
   }

   // ����� ������� �� �����
   cout << "\n\n";
   for (int y=0; y<10; y++)
   {
      for (int x=0; x<10; x++)
         cout << M[y][x]() << "  ";

      cout << '\n';
   }

   cout << "\n\n";
   // ������������� ������� set � get
   M.set(3,6,8);
   cout << M.get(3,6);

   cout << "\n\n\n";
}
