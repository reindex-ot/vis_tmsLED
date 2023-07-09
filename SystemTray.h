#if !defined(AFX_SYSTEMTRAY_H__73740D81_495A_4E2E_A195_B65661E48807__INCLUDED_)
#define AFX_SYSTEMTRAY_H__73740D81_495A_4E2E_A195_B65661E48807__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SystemTray.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CSystemTray ダイアログ

class CSystemTray
{
public:
	CSystemTray();   // 標準のコンストラクタ
	virtual ~CSystemTray();
	
	bool Create(HINSTANCE hInstance);
	void Release();
	void Init(LPCTSTR szToolTip,HICON icon,UINT uID);
	void RemoveIcon();
	void HideIcon();
	void ShowIcon();
	void SetIcon(HICON hIcon);

private:
	HWND m_hWnd;
	HINSTANCE m_hRes;
	NOTIFYICONDATA	m_tnd;
	static LRESULT __stdcall MainProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
//	LRESULT OnTrayNotification(UINT wParam,LONG lParam);
	LRESULT OnTaskBarCreated(WPARAM wParam, LPARAM lParam);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SYSTEMTRAY_H__73740D81_495A_4E2E_A195_B65661E48807__INCLUDED_)
