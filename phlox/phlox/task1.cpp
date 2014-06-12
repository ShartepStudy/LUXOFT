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

   // классы CProxy и CProxy2 существуют для реализации перегрузки оператора [][]
   // возможности использования 
   // в коде конструкций типа Array[i][j] = data вместо Array.set(i,j,data) и
   // cout << Array[i][j]() вместо cout << Array.get(i,j)
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
   // расчет кол-ва бит необходимых для хранения числа от 0 до size-1
   mBitPerCell = log( (double)size-1 ) / log( 2.0 ) + 1; 

   // расчет кол-ва бит необходимых для хранения всего массива
   unsigned long long arrayBitSize = size*size*mBitPerCell;

   // расчет кол-ва байт необходимых для хранения всего массива, с округлением в меньшую сторону
   unsigned long long arraySize = arrayBitSize / BIT_IN_INT;

   // в случае если при предыдущей операции присутствовало округление, увеличиваем кл-во байт на 1
   if ( arrayBitSize % BIT_IN_INT )
      arraySize++;

   // выделение динамической памяти для массива
   mData = new unsigned int[arraySize];
}

CPackedArray::~CPackedArray() 
{
   // освобождение динамической памяти для массива
   delete [] mData;
}

void CPackedArray::set(ushort y, ushort x, int data) 
{
   // проверка, вводимого числа на вхождение в диапазон от 0 до size-1
   if ( data > pow( 2.0, mBitPerCell ) ) 
   {
      cout << "ERROR!!! Data overflow!";
      exit(0);
   }

   // расчет адреса (смещения относительно указателя mData) в битах (точка сохранения данных)
   unsigned long long bitOffset = ( y*mSize + x )*mBitPerCell;

   // расчет адреса (смещения относительно указателя mData) в байтах (точка сохранения данных), 
   // с округлением в меньшую сторону
   unsigned long long indexOffset = bitOffset / BIT_IN_INT;

   // расчет смещения в битах относительно адреса mData + indexOffset
   char localBitOffset = bitOffset % BIT_IN_INT;

   // создание маски (вида 1111 1111 1111 1111 1111 0000 1111 1111, где 0000 очищаемая зона),
   // и очистка участка памяти перед записью данных 
   unsigned int clearMask = ~(((unsigned int)pow( 2.0, mBitPerCell ) - 1) << localBitOffset ); 
   *(mData + indexOffset) &= clearMask;        
   
   // запись данных в массив
   data <<= localBitOffset;
   *(mData + indexOffset) |= data;        
}

int CPackedArray::get(ushort y, ushort x) 
{
   unsigned long long bitOffset = ( y*mSize + x )*mBitPerCell;
   unsigned long long byteOffset = bitOffset / BIT_IN_INT;
   char localBitOffset = bitOffset % BIT_IN_INT;

   // считывание данных из динамической памяти
   unsigned int data = *(mData + byteOffset) >> localBitOffset;
   
   // создание маски (вида 0000 0000 0000 0000 0000 0000 1111 1111, где 0000 очищаемая зона)
   unsigned int dataMask = 0xFFFFFFFF >> (BIT_IN_INT - mBitPerCell); 

   // очистка данных от лишних бит
   return data & dataMask;
}

CPackedArray::CProxy CPackedArray::operator[](ushort y)
{
   // возвращает объет класса CProxy, преобразуя таким образом код
   // Array[y][x] в proxy[x], y сохранена в поле mY
   return CProxy(this, y);
}

CPackedArray::CProxy::CProxy(CPackedArray *obj, ushort y)
   : mObj(obj)
   , mY(y)
{}

CPackedArray::CProxy2 CPackedArray::CProxy::operator[](ushort x)
{   
   // возвращает объет класса CProxy2, преобразуя таким образом код
   // proxy[x] в proxy2, y сохранена в поле mY, x сохранена в поле mХ
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
   CPackedArray M(10); // создание массива размером 10
   
   // заполнение массива случайными числами и вывод их на экран
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

   // вывод массива на экран
   cout << "\n\n";
   for (int y=0; y<10; y++)
   {
      for (int x=0; x<10; x++)
         cout << M[y][x]() << "  ";

      cout << '\n';
   }

   cout << "\n\n";
   // использование методов set и get
   M.set(3,6,8);
   cout << M.get(3,6);

   cout << "\n\n\n";
}
