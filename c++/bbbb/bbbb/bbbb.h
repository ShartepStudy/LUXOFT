
// bbbb.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CbbbbApp:
// � ���������� ������� ������ ��. bbbb.cpp
//

class CbbbbApp : public CWinApp
{
public:
	CbbbbApp();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CbbbbApp theApp;