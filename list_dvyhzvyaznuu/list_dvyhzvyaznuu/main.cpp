#include <iostream>
using namespace std;

class CData
{
private:
   char * mStr;
   CData * mNext;
   CData * mPrevious;
   unsigned int mIndex;
public:
   CData(char * str, CData * next, CData * previous, unsigned int index)
      : mNext( next )
      , mPrevious( previous )
      , mIndex( index )
   {
      mStr = new char[strlen( str ) + 1];
      strcpy( mStr, str ); 
   }
   ~CData() { if(mStr) delete [] mStr; }

   char * getStr() { return mStr; }
   CData * getNext() { return mNext; } 
   CData * getPrevious() { return mPrevious; }
   unsigned int getIndex() { return mIndex; }

   void setStr(char * str) 
   {
      if(mStr) delete [] mStr;
      mStr = new char[strlen( str ) + 1];
      strcpy( mStr, str );
   }
   void setNext(CData * next) { mNext = next; }
   void setPrevious(CData * previous) { mPrevious = previous; }
   void addIndex() { mIndex++; }
   void decIndex() { mIndex--; }
};

class CNode 
{
private:
   CData * mFirst;
   CData * mLast;

   unsigned int mSize;
   void decIndexses(CData * element);
   void addIndexses(CData * element);
public:
   CNode();
   ~CNode();

   void push_front(char * str);
   void push_back(char * str);
   void insert(unsigned int index, char * str);
   bool remove(int index);
   void print();
   unsigned int size() { return mSize; };
};

void CNode::decIndexses(CData * element)
{
   while(element)
   {
      element->decIndex();
      element = element->getNext();
   }
}

void CNode::addIndexses(CData * element)
{
   while(element)
   {
      element->addIndex();
      element = element->getNext();
   }
}

bool CNode::remove(int index)
{
   if( index<0 || index>=mSize )
   {
      printf("Error, element %d doesn't exist\n", index);
      return false;
   }
   
   CData * curElement;
   
   if( mSize==1 )
   {
      curElement = mFirst;
      mLast = 0;
      mFirst = 0;
      delete curElement;
   }
   else if( index == mSize-1 )
   {
      curElement = mLast;
      mLast = mLast->getPrevious();
      mLast->setNext( 0 );
      delete curElement;
   }
   else if ( index==0 )
   {
      curElement = mFirst;
      mFirst = mFirst->getNext();
      mFirst->setPrevious( 0 );
      delete curElement;
      decIndexses(mFirst);
   }
   else 
   {
      curElement = mFirst->getNext();
      while ( curElement )
      {
         if ( curElement->getIndex() == index )
         {
            curElement->getPrevious()->setNext( curElement->getNext() );
            curElement->getNext()->setPrevious( curElement->getPrevious() );

            decIndexses(curElement->getNext());
            delete curElement;
            break;
         }
         curElement = curElement->getNext() ;
      }    
   }
   
   mSize--;
   return true;
}

void CNode::print()
{
   CData * curElement = mFirst;
   while (curElement)
   {
      printf( "%s\n", curElement->getStr() );
      curElement = curElement->getNext() ;
   } 
   printf( "\n" );
}

void CNode::push_front(char * str)
{
   CData * newElement = new CData( str, mFirst, 0, 0 );
   
   if ( mFirst )
      mFirst->setPrevious(newElement);
   mFirst = newElement;
   
   if( !mLast )
      mLast = newElement;

   addIndexses(mFirst->getNext());
   
   mSize++;
}

void CNode::push_back(char * str)
{
   CData * newElement = new CData( str, 0, mLast, mSize );
 
   if( mLast )
      mLast->setNext(newElement);
   mLast = newElement;
   
   if( !mFirst )
      mFirst = newElement;
   
   mSize++;
}

CNode::CNode() 
   : mFirst(0)
   , mLast(0)
   , mSize(0)
{}

CNode::~CNode()
{
   while (mLast)
   {
      CData * curElement = mLast;
      mLast = mLast->getPrevious();
      delete curElement;
   } 
}

void main() 
{
   CNode L;
   char str[80];
   
   L.remove(3);
   for (int i=0; i<5; i++)
   {
      printf("Enter string: ");
      scanf("%s",str);
      L.push_front(str);
      if(!i) L.remove(i);
   }
   
   L.print();

   for (int i=0; i<5; i++)
   {
      printf("Enter string: ");
      scanf("%s",str);
      L.push_back(str);
   }

   L.print();

   L.remove(0);
   L.print();

   L.remove(L.size()-1);
   L.print();
}