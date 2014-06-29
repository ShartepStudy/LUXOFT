#include <iostream>
#include <string>
using namespace std;

template <typename T>
class CData
{
private:
   T mStr;
   CData * mNext;
public:
   CData(const CData & obj)
      : mNext( obj.mNext )
      , mStr(obj.mStr)
   {}
   CData(T str, CData * next=0)
      : mNext( next )
      , mStr( str )
   {}
   ~CData() {}

   T getStr() { return mStr; }
   CData * getNext() { return mNext; } 

   void setStr(T str) { mStr = str; }
   void setNext(CData * next) { mNext = next; }
};

template<typename T>
class CNode 
{
private:
   CData<T> * mFirst;
   CData<T> * mLast;
public:
   CNode();
   ~CNode();

   bool del(CData<T> obj);
   bool search(CData<T> obj, CData<T> *& element, CData<T> *& preElement);
   void push_front(CData<T> obj);
   void push_back(CData<T> obj);
   void push_front(T str);
   void push_back(T str);
   void print();
   void sort();
};

template<typename T>
bool CNode<T>::del(CData<T> obj)
{
   CData<T> * delElement;
   CData<T> * preDelElement;
   if(search(obj, delElement, preDelElement))
   {
      if(preDelElement) 
         preDelElement->setNext(delElement->getNext());
      else 
         mFirst = delElement->getNext();

      delete delElement;
      return true;
   }
   else
      return false;
}

template<typename T>
bool CNode<T>::search(CData<T> obj, CData<T> *& element, CData<T> *& preElement)
{
   element=mFirst;
   preElement=0;

   while( element )
   {
      if (element->getStr()==obj.getStr())
         break;

      preElement = element;
      element = element->getNext();
   }

   return element;
}

template<typename T>
void CNode<T>::sort()
{
   if(!mFirst) return;
      
   bool changed;
   CData<T> * curElement = mFirst;
   CData<T> * nextElement = curElement->getNext();
   CData<T> * prevElement = 0;

   do
   {
      changed = false;
      while(nextElement)
      {
         if( curElement->getStr()>nextElement->getStr() )
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

template<typename T>
void CNode<T>::print()
{
   CData<T> * curElement = mFirst;
   while (curElement)
   {
      cout << curElement->getStr() << endl ;
      curElement = curElement->getNext() ;
   } 
   cout << endl;
}

template<typename T>
void CNode<T>::push_front(CData<T> obj)
{
   CData<T> * newElement = new CData<T>( obj.getStr(), mFirst );
   
   mFirst = newElement;

   if( !mLast )
      mLast = mFirst;
}

template<typename T>
void CNode<T>::push_front(T str)
{
   CData<T> * newElement = new CData<T>( str, mFirst );
   
   mFirst = newElement;
   
   if( !mLast )
      mLast = newElement;
}

template<typename T>
void CNode<T>::push_back(CData<T> obj)
{
   CData<T> * newElement = new CData<T>( obj.getStr(), 0 );
   
   if( mLast )
      mLast->setNext(newElement);
   mLast = newElement;
   
   if( !mFirst )
      mFirst = newElement;
}

template<typename T>
void CNode<T>::push_back(T str)
{
   CData<T> * newElement = new CData<T>( str, 0 );
 
   if( mLast )
      mLast->setNext(newElement);
   mLast = newElement;
   
   if( !mFirst )
      mFirst = newElement;
}

template<typename T>
CNode<T>::CNode() 
   : mFirst(0)
   , mLast(0)
{}

template<typename T>
CNode<T>::~CNode()
{
   while (mFirst)
   {
      CData<T> * curElement = mFirst;
      mFirst = mFirst->getNext();
      delete curElement;
   } 
}

void main() 
{
   CNode<int> L;
   int str;
   
   for (int i=0; i<5; i++)
   {
      printf("Enter string: ");
      cin >> str;
      L.push_front(str);
   }
   
   L.print();

   for (int i=0; i<5; i++)
   {
      printf("Enter string: ");
      cin >> str;
      L.push_back(str);
   }

   L.print();

   L.sort();
   L.print();
   
   CData<int> A(12345);
   L.push_front(A);
   A.setStr(54321);
   L.push_back(A);

   L.print();
   A.setStr(12345);
   L.del(A);
   L.print();

   CNode<string> S;
   S.push_back("string test");
   S.print();
}