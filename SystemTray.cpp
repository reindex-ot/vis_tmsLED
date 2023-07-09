// SystemTray.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "vis_tmsled.h"
#include "SystemTray.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSystemTray ダイアログ

const UINT WM_TASKBARCREATED = ::RegisterWindowMessage(_T("TaskbarCreated"));
const UINT WM_USER_TRAY = WM_USER+1;

CSystemTray::CSystemTray()
{
	memset(&m_tnd,0,sizeof(m_tnd));
	m_hWnd = NULL;
}

CSystemTray::~CSystemTray()
{
	if(m_hWnd)
	{
		DestroyWindow(m_hWnd);
	}
}

bool CSystemTray::Create(HINSTANCE hInstance)
{
	if(m_hWnd)
	{
		return true;
	}
	WNDCLASS wc;
	memset(&wc,0,sizeof(wc));
	wc.style = 0;
	wc.lpfnWndProc = MainProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = AfxGetInstanceHandle();
//	wc.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICONMAIN));
//	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wc.hbrBackground = (void*)COLOR_BTNSHADOW;
//	wc.lpszMenuName =  MAKEINTRESOURCE(200);
	wc.lpszClassName = "tmsVU_TrayWindowClass";
	RegisterClass(&wc);

	m_hWnd = CreateWindow(
		"tmsVU_TrayWindowClass",
		"",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		AfxGetInstanceHandle(),
		(LPVOID )this
		);
	if(!m_hWnd)
	{
		return false;
	}

	return true;
}

LRESULT CSystemTray::MainProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	CSystemTray *mod = (CSystemTray *)GetWindowLong(hWnd,GWL_USERDATA);
/*	if(uMsg == WM_USER_TRAY)
	{
		return mod->OnTrayNotification(wParam,lParam);
	}
	else */if(uMsg == WM_TASKBARCREATED)
	{
		return mod->OnTaskBarCreated(wParam,lParam);
	}

	switch(uMsg){
	case WM_CREATE:		/* ウィンドウ作成時 */
		SetWindowLong(hWnd,GWL_USERDATA,(LONG )((CREATESTRUCT *)lParam)->lpCreateParams);
		break;
/*	
	case WM_COMMAND:
		switch(LOWORD(wParam)){
		case ID_MENUITEM_EXIT:
			MessageBox(hWnd,"OnMenuitemExit()","debug",0);
			break;
		}
		break;
*/
	default:
		return DefWindowProc(hWnd,uMsg,wParam,lParam);
	}

	return 0;
}

LRESULT CSystemTray::OnTaskBarCreated(WPARAM wParam, LPARAM lParam)
{
	ShowIcon();
	return 0;
}

////
void CSystemTray::Init(LPCTSTR szToolTip,HICON icon,UINT uID)
{
	memset(&m_tnd,0,sizeof(m_tnd));
	m_tnd.cbSize= sizeof(NOTIFYICONDATA);
	m_tnd.hWnd	= m_hWnd;
	m_tnd.uID	= uID;
	m_tnd.hIcon	= icon;
	m_tnd.uFlags= NIF_MESSAGE | NIF_ICON | NIF_TIP;
	m_tnd.uCallbackMessage = WM_USER_TRAY;
	_tcscpy(m_tnd.szTip, szToolTip);
	
	Shell_NotifyIcon(NIM_ADD,&m_tnd);
}
/*
LRESULT CSystemTray::OnTrayNotification(UINT wParam,LONG lParam) 
{
	if(wParam != m_tnd.uID)
	{
		return 0L;
	}

	CMenu menu, *pSubMenu;
	switch(LOWORD(lParam)){
	case WM_RBUTTONUP:
	{
		if(!menu.LoadMenu(IDR_MENU_TRAY))
		{
			return 0;
		}
		if(!(pSubMenu = menu.GetSubMenu(0)))
		{
			return 0;
		}

		//デフォルトアイテムの設定
		::SetMenuDefaultItem(pSubMenu->m_hMenu,0,TRUE);

		CPoint pos;
		GetCursorPos(&pos);
		::TrackPopupMenu(pSubMenu->m_hMenu,0,pos.x,pos.y,0,m_hWnd,NULL);

		menu.DestroyMenu();
		break;
	}
	case WM_LBUTTONDBLCLK:
	{
		UINT uItem;
		if(!menu.LoadMenu(IDR_MENU_TRAY))
		{
			return 0;
		}
		if(!(pSubMenu = menu.GetSubMenu(0)))
		{
			return 0;
		}
		uItem = pSubMenu->GetMenuItemID(TRUE);
		switch(uItem){
		case 0:
			break;
		}

		menu.DestroyMenu();

		break;
	}
	}//

	return 1;
}
*/
void CSystemTray::RemoveIcon()
{
	if(!m_tnd.cbSize)
	{
		return;
	}
	m_tnd.uFlags = 0;
	Shell_NotifyIcon(NIM_DELETE,&m_tnd);
}

void CSystemTray::HideIcon()
{
	if(!m_tnd.cbSize)
	{
		return;
	}
	m_tnd.uFlags = NIF_ICON;
	Shell_NotifyIcon (NIM_DELETE,&m_tnd);
}

void CSystemTray::ShowIcon()
{
	if(!m_tnd.cbSize)
	{
		return;
	}
	m_tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	Shell_NotifyIcon(NIM_ADD,&m_tnd);
}

void CSystemTray::SetIcon(HICON hIcon)
{
	if(!m_tnd.cbSize)
	{
		return;
	}
	m_tnd.uFlags = NIF_ICON;
	m_tnd.hIcon = hIcon;

	Shell_NotifyIcon(NIM_MODIFY,&m_tnd);
}

