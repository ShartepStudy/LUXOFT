
// try1.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// Ctry1App:
// � ���������� ������� ������ ��. try1.cpp
//

class Ctry1App : public CWinApp
{
public:
	Ctry1App();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern Ctry1App theApp;