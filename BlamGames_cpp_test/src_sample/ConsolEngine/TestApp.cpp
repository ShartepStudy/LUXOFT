#include "TestApp.h"
#include <conio.h>
#include <time.h>

TestApp::TestApp() : Parent( 50, 40 )
{
   for (int y=0; y < GAME_SCREEN_HEIGHT; y++)
   {
      for (int x=0; x < GAME_SCREEN_WIDTH; x++) 
      {
         if (y==0 || 
             (y==(GAME_SCREEN_HEIGHT-1) && x>=0 && x<=GAME_POLE_WIDTH) ||
             x==0 || 
             x==GAME_POLE_WIDTH ||
             (x==(GAME_SCREEN_WIDTH-1) && y>=0 && y<=FIGURE_PREVIEW_POLE_HEIGHT) ||
             (y==FIGURE_PREVIEW_POLE_HEIGHT && x>=GAME_POLE_WIDTH && x<(GAME_SCREEN_WIDTH-1)))
                  SetChar(x, y, L'#');
         else if ((y>0 && y<(GAME_POLE_HEIGHT-1) && x>0 && x<GAME_POLE_WIDTH) ||
                  (y>0 && y<FIGURE_PREVIEW_POLE_HEIGHT && x>GAME_POLE_WIDTH && x<(GAME_SCREEN_WIDTH-1)))
                     SetChar(x, y, L'.');
      }
   }
   srand((int)time(NULL));
   mFigureNumb = rand() % 7;
   mNextFigureNumb = rand() % 7;

   mMoveRight = 0;
   mMoveLeft = 0;
   mPressDown = false;

   mOldX = GAME_POLE_WIDTH/2;
   mOldY = 1;

}

void TestApp::KeyPressed(int btnCode)
{
   if ( btnCode == 224 )
      btnCode = getch();
	switch (btnCode)
   {
   case 72: 
//		mObj1Y--;
      break;
   case 80: 
      mPressDown = true;

//		mObj1Y++;
      break;
   case 75:
//		mObj1X--;
      break;
   case 77:
//		mObj1X++;
      break;
   case 32:
//		mObj1X += 5;
      break;
   case 13:
      mNextFigureNumb = rand() % 7;
      break;
   }

	//if (mObj1X < 0)
	//	mObj1X = 0;
	//else if (mObj1X >= X_SIZE)
	//	mObj1X = X_SIZE - 1;

	//if (mObj1Y < 0)
	//	mObj1Y = 0;
	//else if (mObj1Y >=Y_SIZE)
	//	mObj1Y = Y_SIZE - 1;
}

void TestApp::UpdateF(float deltaTime)
{
   
   for (int i=0; i<4; i++)
      for (int j=0; j<2; j++)
      {
         if (FIGURE[mNextFigureNumb][j][i]) SetChar(GAME_POLE_WIDTH + 2 + i, j + 2, L'*');
         else SetChar(GAME_POLE_WIDTH + 2 + i, j + 2, L'.');
      }

   int newX = mOldX + mMoveRight - mMoveLeft;
   int newY = mOldY + 1;

   for (int i=0; i<4; i++)
      for (int j=0; j<2; j++)
         SetChar(mOldX + i, mOldY + j, L'.');

   for (int i=0; i<4; i++)
      for (int j=0; j<2; j++)
         if (FIGURE[mFigureNumb][j][i]) SetChar(newX + i, newY + j, L'*');

   mOldX = newX;
   mOldY = newY;

   if(mOldY > GAME_SCREEN_HEIGHT - 4) 
   {
      mOldY = 1;
      mFigureNumb = mNextFigureNumb;
      mNextFigureNumb = rand() % 7;
      mPressDown = false;
   }

   if(mPressDown) Sleep(40);
   else Sleep(150);
   //SetChar(mObj1XOld, mObj1YOld, L' ');
	//SetChar(mObj1X, mObj1Y, L'O');
//
//	mObj1XOld = mObj1X;
//	mObj1YOld = mObj1Y;
//
//	//-----------------------------
//
//	SetChar(mObj2X, mObj2Y, L' ');
//	if (mDirection)
//	{
//		mObj2X++;
//		if (mObj2X == 20)
//			mDirection = false;
//	}
//	else
//	{
//		mObj2X--;
//		if (mObj2X == 5)
//			mDirection = true;
//	}
//	SetChar(mObj2X, mObj2Y, L'F');
}
