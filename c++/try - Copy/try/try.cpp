
// try.cpp : ќпредел€ет поведение классов дл€ приложени€.
//

#include "stdafx.h"
#include "try.h"
#include "MainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtryApp

BEGIN_MESSAGE_MAP(CtryApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// создание CtryApp

CtryApp::CtryApp()
{
	// поддержка диспетчера перезагрузки
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: добавьте код создани€,
	// –азмещает весь важный код инициализации в InitInstance
}


// ≈динственный объект CtryApp

CtryApp theApp;


// инициализаци€ CtryApp

BOOL CtryApp::InitInstance()
{
	// InitCommonControlsEx() требуетс€ дл€ Windows XP, если манифест
	// приложени€ использует ComCtl32.dll версии 6 или более поздней версии дл€ включени€
	// стилей отображени€. ¬ противном случае будет возникать сбой при создании любого окна.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ¬ыберите этот параметр дл€ включени€ всех общих классов управлени€, которые необходимо использовать
	// в вашем приложении.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// —оздать диспетчер оболочки, в случае, если диалоговое окно содержит
	// представление дерева оболочки или какие-либо его элементы управлени€.
	CShellManager *pShellManager = new CShellManager;

	// —тандартна€ инициализаци€
	// ≈сли эти возможности не используютс€ и необходимо уменьшить размер
	// конечного исполн€емого файла, необходимо удалить из следующих
	// конкретных процедур инициализации, которые не требуютс€
	// »змените раздел реестра, в котором хран€тс€ параметры
	// TODO: следует изменить эту строку на что-нибудь подход€щее,
	// например на название организации
	SetRegistryKey(_T("SFU-soft"));

	CMainDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

   return FALSE;
}

