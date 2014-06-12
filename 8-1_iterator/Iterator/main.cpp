#include <iostream>
#include <time.h>
using namespace std;

class CData
{
private:
   int mData;
   CData * mNext;
public:
   CData(const CData & obj);
   CData(int data, CData * next);
   ~CData() {}

   int getStr() { return mData; }
   CData * getNext() { return mNext; } 

   void setStr(int data);
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
   void push_front(int data);
   void push_back(int data);
   void print();
   void sort();

   CData * getFirst();
};

class IIterator 
{
public:
   IIterator() {}

   virtual void rewind() = 0;
   virtual int current() = 0;
   virtual bool hasMore() = 0;
   virtual void next() = 0;
};

class CIterator : public IIterator
{
protected:
   CData * mHead;
   CData * mCurrent;
public:
   CIterator (CNode * list);

   virtual bool hasMore() { return false; }
   virtual void next() { }
   virtual void rewind();
   virtual int current();
};

class CEvenIterator : public CIterator 
{
public:
   CEvenIterator(CNode * list);

   virtual bool hasMore();
   virtual void next();
};

class CNegativeIterator : public CIterator 
{
public:
   CNegativeIterator(CNode * list);

   virtual bool hasMore();
   virtual void next();
};

class CModFiveIterator : public CIterator 
{
public:
   CModFiveIterator(CNode * list);

   virtual bool hasMore();
   virtual void next();
};

CModFiveIterator::CModFiveIterator(CNode * list)
   : CIterator(list)
{
   CData * cur = mHead;

   while (cur && cur->getStr()%5 != 0)
      cur = cur->getNext();

   mHead = cur;
   mCurrent = cur;
}

void CModFiveIterator::next()
{
   CData * cur = mCurrent->getNext();

   while (cur && cur->getStr()%5 != 0)
      cur = cur->getNext();

   mCurrent = cur;
}

bool CModFiveIterator::hasMore()
{
   CData * cur = mCurrent->getNext();

   while (cur && cur->getStr()%5 != 0)
      cur = cur->getNext();

   return cur;
}

CNegativeIterator::CNegativeIterator(CNode * list)
   : CIterator(list)
{
   CData * cur = mHead;

   while (cur && cur->getStr()>0)
      cur = cur->getNext();

   mHead = cur;
   mCurrent = cur;
}

void CNegativeIterator::next()
{
   CData * cur = mCurrent->getNext();

   while (cur && cur->getStr()>0)
      cur = cur->getNext();

   mCurrent = cur;
}

bool CNegativeIterator::hasMore()
{
   CData * cur = mCurrent->getNext();

   while (cur && cur->getStr()>0)
      cur = cur->getNext();

   return cur;
}

void CEvenIterator::next()
{
   CData * cur = mCurrent->getNext();

   while (cur && cur->getStr()%2 != 0)
      cur = cur->getNext();

   mCurrent = cur;
}

bool CEvenIterator::hasMore()
{
   CData * cur = mCurrent->getNext();

   while (cur && cur->getStr()%2 != 0)
      cur = cur->getNext();

   return cur;
}

int CIterator::current()
{
   return mCurrent->getStr();
}

void CIterator::rewind()
{
   mCurrent = mHead;
}

CEvenIterator::CEvenIterator(CNode * list)
   : CIterator(list)
{
   CData * cur = mHead;

   while (cur && cur->getStr()%2 != 0)
      cur = cur->getNext();

   mHead = cur;
   mCurrent = cur;
}

CIterator::CIterator(CNode * list)
{
   mHead = list->getFirst();
   mCurrent = mHead;
}

CData * CNode::getFirst()
{
   return mFirst;
}

CData::CData(const CData & obj)
   : mNext( obj.mNext )
   , mData( obj.mData )
{}

CData::CData(int data, CData * next)
   : mNext( next )
   , mData( data )
{}

void CData::setStr(int data) 
{
   mData = data;
}

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

   while( element && element->getStr()==obj.getStr() )
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

void CNode::print()
{
   CData * curElement = mFirst;
   while (curElement)
   {
      printf( "%d\n", curElement->getStr() );
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

void CNode::push_front(int str)
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

void CNode::push_back(int str)
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
   srand((int)time(NULL));
   
   for (int i=0; i<5; i++)
      L.push_front(rand()%100-50);
   
   L.print();

   for (int i=0; i<5; i++)
      L.push_back(rand()%100-50);

   L.print();
   L.sort();
   L.print();
   
   IIterator * it;
   it = new CEvenIterator(&L);
   cout << "Even digits:" << endl;
   cout << it->current() << endl;
   while (it->hasMore())
   {
      it->next();
      cout << it->current() << endl;
   }
   delete it;
   cout << endl;

   it = new CNegativeIterator(&L);
   cout << "Negative digits:" << endl;
   cout << it->current() << endl;
   while (it->hasMore())
   {
      it->next();
      cout << it->current() << endl;
   }
   delete it;
   cout << endl;

   it = new CModFiveIterator(&L);
   cout << "%5 digits:" << endl;
   cout << it->current() << endl;
   while (it->hasMore())
   {
      it->next();
      cout << it->current() << endl;
   }
   delete it;
   cout << endl;

}