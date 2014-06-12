
// bbbb.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CbbbbApp:
// О реализации данного класса см. bbbb.cpp
//

class CbbbbApp : public CWinApp
{
public:
	CbbbbApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CbbbbApp theApp;