const short WORKING_DAYS = 25;
const float SERVANT_PAYMENT_PER_DAY = 200;
const float MANAGER_PAYMENT_PER_DAY = 400;
const float DIRECTOR_PAYMENT_PER_DAY = 600;


class CCalcStrategy 
{
public:
   CCalcStrategy() {};
   virtual ~CCalcStrategy() {};
   virtual float algorithm() = 0;   
};

class CServant: public CCalcStrategy
{
public:
   CServant() 
      : CCalcStrategy()
   {}
   ~CServant() {}
   virtual float algorithm() 
   {
      return WORKING_DAYS * SERVANT_PAYMENT_PER_DAY;
   }
};

class CManager: public CCalcStrategy
{
public:
   CManager() 
      : CCalcStrategy()
   {}
   ~CManager() {}
   virtual float algorithm() 
   {
      return WORKING_DAYS * MANAGER_PAYMENT_PER_DAY;
   }
};

class CDirector: public CCalcStrategy
{
public:
   CDirector() 
      : CCalcStrategy()
   {}
   ~CDirector() {}
   virtual float algorithm() 
   {
      return WORKING_DAYS * DIRECTOR_PAYMENT_PER_DAY;
   }
};

enum EPosition { servant, manager, director };

class CPayrollContext 
{
private:
   CCalcStrategy * mStrategy; 
public:
   CPayrollContext(EPosition pos)
   {
      switch (pos)
      {
      case servant: 
         mStrategy = new CServant;
         break;
      case manager: 
         mStrategy = new CManager;
         break;
      case director: 
         mStrategy = new CDirector;
         break;
      }      
   }
   ~CPayrollContext()
   {
      delete mStrategy;
   }
   float calculation()
   {
      return mStrategy->algorithm();
   }
};


#include <iostream>
using namespace std;

void main ()
{
   CPayrollContext servantContext(servant);
   cout << "Servant payroll: " << servantContext.calculation() << '\n';

   CPayrollContext managerContext(manager);
   cout << "Manager payroll: " << managerContext.calculation() << '\n';

   CPayrollContext directorContext(director);
   cout << "Director payroll: " << directorContext.calculation() << '\n';

}