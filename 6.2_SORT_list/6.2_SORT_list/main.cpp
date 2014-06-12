#include <iostream>
using namespace std;

class CData
{
private:
   char * mStr;
   CData * mNext;
public:
   CData(const CData & obj)
      : mNext( obj.mNext )
   {
      mStr = new char[strlen( obj.mStr ) + 1];
      strcpy( mStr, obj.mStr ); 
   }
   CData(char * str, CData * next=0)
      : mNext( next )
   {
      mStr = new char[strlen( str ) + 1];
      strcpy( mStr, str ); 
   }
   ~CData() { if(mStr) delete [] mStr; }

   char * getStr() { return mStr; }
   CData * getNext() { return mNext; } 

   void setStr(char * str) 
   {
      if(mStr) delete [] mStr;
      mStr = new char[strlen( str ) + 1];
      strcpy( mStr, str );
   }
   void setNext(CData * next) { mNext = next; }
};

class CNode 
{
private:
   CData * mFirst;
   CData * mLast;
public:
   CNode();
   ~CNode();

   bool del(CData obj);
   bool search(CData obj, CData *& element, CData *& preElement);
   void push_front(CData obj);
   void push_back(CData obj);
   void push_front(char * str);
   void push_back(char * str);
   void print();
   void sort();
};

bool CNode::del(CData obj)
{
   CData * delElement;
   CData * preDelElement;
   if(search(obj, delElement, preDelElement))
   {
      preDelElement->setNext(delElement->getNext());
      delete delElement;
      return true;
   }
   else
      return false;
}

bool CNode::search(CData obj, CData *& element, CData *& preElement)
{
   element=mFirst;

   while( element && strcmp(element->getStr(), obj.getStr()) != 0 )
   {
      preElement = element;
      element = element->getNext();
   }

   if(element) 
      return true;
   else 
      return false;
}

void CNode::sort()
{
   if(!mFirst) return;
      
   bool changed;
   CData * curElement = mFirst;
   CData * nextElement = curElement->getNext();
   CData * prevElement = 0;

   do
   {
      changed = false;
      while(nextElement)
      {
         if( strcmp( curElement->getStr(), nextElement->getStr() ) > 0 )
         {
            curElement->setNext(nextElement->getNext());
            nextElement->setNext(curElement);
            if(prevElement) 
               prevElement->setNext(nextElement);
            else 
               mFirst=nextElement;

            prevElement = nextElement;
            nextElement = curElement->getNext();
            changed = true;
         }
         else
         {
            prevElement = curElement;
            curElement = curElement->getNext();
            nextElement = curElement->getNext();
         }
      }
      prevElement = 0;
      curElement = mFirst;
      nextElement = curElement->getNext();
   }
   while(changed);
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

void CNode::push_front(CData obj)
{
   CData * newElement = new CData( obj.getStr(), mFirst );
   
   mFirst = newElement;

   if( !mLast )
      mLast = mFirst;
}

void CNode::push_front(char * str)
{
   CData * newElement = new CData( str, mFirst );
   
   mFirst = newElement;
   
   if( !mLast )
      mLast = newElement;
}

void CNode::push_back(CData obj)
{
   CData * newElement = new CData( obj.getStr(), 0 );
   
   if( mLast )
      mLast->setNext(newElement);
   mLast = newElement;
   
   if( !mFirst )
      mFirst = newElement;
}

void CNode::push_back(char * str)
{
   CData * newElement = new CData( str, 0 );
 
   if( mLast )
      mLast->setNext(newElement);
   mLast = newElement;
   
   if( !mFirst )
      mFirst = newElement;
}

CNode::CNode() 
   : mFirst(0)
   , mLast(0)
{}

CNode::~CNode()
{
   while (mFirst)
   {
      CData * curElement = mFirst;
      mFirst = mFirst->getNext();
      delete curElement;
   } 
}

void main() 
{
   CNode L;
   char str[80];
   
   for (int i=0; i<5; i++)
   {
      printf("Enter string: ");
      scanf("%s",str);
      L.push_front(str);
   }
   
   L.print();

   for (int i=0; i<5; i++)
   {
      printf("Enter string: ");
      scanf("%s",str);
      L.push_back(str);
   }

   L.print();

   L.sort();
   L.print();
   
   CData A("Hellow");
   L.push_front(A);
   A.setStr("Back");
   L.push_back(A);

   L.print();
   A.setStr("cc");
   L.del(A);
   L.print();
}