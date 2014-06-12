#pragma once

#include "BaseApp.h"
#include "const.h"


class TestApp : public BaseApp
{
	typedef BaseApp Parent;

	private:
		//int mObj1XOld;
		//int mObj1YOld;
		//int mObj1X;
		//int mObj1Y;

		//int mObj2X;
		//int mObj2Y;

		//bool mDirection;
      int mFigureNumb;
      int mNextFigureNumb;

      int mMoveRight;
      int mMoveLeft;

      int mOldX;
      int mOldY;
      
      bool mPressDown;

	public:
		TestApp();
		virtual void KeyPressed(int btnCode);
		virtual void UpdateF(float deltaTime);
};
