#if !defined(AFX_DLGCONFIG_H__2BB4005F_FE68_4EC8_AF0F_B2F34C9B174B__INCLUDED_)
#define AFX_DLGCONFIG_H__2BB4005F_FE68_4EC8_AF0F_B2F34C9B174B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgConfig.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CDlgConfig ダイアログ

class CDlgConfig : public CDialog
{
// コンストラクション
public:
	CDlgConfig(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDlgConfig)
	enum { IDD = IDD_DIALOG_CONFIG };
	CStatic	m_wndStaticDevice;
	CComboBox	m_wndDeviceList;
	CString	m_strDevice;
	BOOL	m_bLed;
	BOOL	m_bTrayVU;
	BOOL	m_bCapsLock1;
	BOOL	m_bCapsLock2;
	BOOL	m_bCapsLock3;
	BOOL	m_bNumLock1;
	BOOL	m_bNumLock2;
	BOOL	m_bNumLock3;
	BOOL	m_bScrollLock1;
	BOOL	m_bScrollLock2;
	BOOL	m_bScrollLock3;
	BOOL	m_bCapsLock0;
	BOOL	m_bNumLock0;
	BOOL	m_bScrollLock0;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDlgConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDlgConfig)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckLed();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DLGCONFIG_H__2BB4005F_FE68_4EC8_AF0F_B2F34C9B174B__INCLUDED_)
