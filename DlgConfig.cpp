// DlgConfig.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "vis_tmsled.h"
#include "DlgConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgConfig ダイアログ


CDlgConfig::CDlgConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgConfig::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgConfig)
	m_strDevice = _T("");
	m_bLed = FALSE;
	m_bTrayVU = FALSE;
	m_bCapsLock1 = FALSE;
	m_bCapsLock2 = FALSE;
	m_bCapsLock3 = FALSE;
	m_bNumLock1 = FALSE;
	m_bNumLock2 = FALSE;
	m_bNumLock3 = FALSE;
	m_bScrollLock1 = FALSE;
	m_bScrollLock2 = FALSE;
	m_bScrollLock3 = FALSE;
	m_bCapsLock0 = FALSE;
	m_bNumLock0 = FALSE;
	m_bScrollLock0 = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgConfig)
	DDX_Control(pDX, IDC_STATIC_DEVICE, m_wndStaticDevice);
	DDX_Control(pDX, IDC_COMBO_DEVICE_LIST, m_wndDeviceList);
	DDX_CBString(pDX, IDC_COMBO_DEVICE_LIST, m_strDevice);
	DDX_Check(pDX, IDC_CHECK_LED, m_bLed);
	DDX_Check(pDX, IDC_CHECK_TRAY_VU, m_bTrayVU);
	DDX_Check(pDX, IDC_CAPSLOCK1, m_bCapsLock1);
	DDX_Check(pDX, IDC_CAPSLOCK2, m_bCapsLock2);
	DDX_Check(pDX, IDC_CAPSLOCK3, m_bCapsLock3);
	DDX_Check(pDX, IDC_NUMLOCK1, m_bNumLock1);
	DDX_Check(pDX, IDC_NUMLOCK2, m_bNumLock2);
	DDX_Check(pDX, IDC_NUMLOCK3, m_bNumLock3);
	DDX_Check(pDX, IDC_SCROLLLOCK1, m_bScrollLock1);
	DDX_Check(pDX, IDC_SCROLLLOCK2, m_bScrollLock2);
	DDX_Check(pDX, IDC_SCROLLLOCK3, m_bScrollLock3);
	DDX_Check(pDX, IDC_CAPSLOCK0, m_bCapsLock0);
	DDX_Check(pDX, IDC_NUMLOCK0, m_bNumLock0);
	DDX_Check(pDX, IDC_SCROLLLOCK0, m_bScrollLock0);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgConfig, CDialog)
	//{{AFX_MSG_MAP(CDlgConfig)
	ON_BN_CLICKED(IDC_CHECK_LED, OnCheckLed)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgConfig メッセージ ハンドラ

BOOL CDlgConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	HKEY	hKey = 0;
	DWORD	dwDisposition = 0;
	if(RegCreateKeyEx(HKEY_LOCAL_MACHINE,
						"HARDWARE\\DEVICEMAP\\KeyboardClass",
						0,
						"",
						REG_OPTION_NON_VOLATILE,
						KEY_READ,
						NULL,
						&hKey,
						&dwDisposition) == ERROR_SUCCESS)
	{
		int index = 0;
		DWORD dwType = REG_SZ;
		char szRetName[255];
		DWORD dwRetNameSize = sizeof(szRetName);
		char szRetValue[255];
		DWORD dwRetValueSize = sizeof(szRetValue);
		while(RegEnumValue(hKey,index++,szRetName,&dwRetNameSize,NULL,&dwType,(BYTE *)&szRetValue,&dwRetValueSize) == ERROR_SUCCESS)
		{
			dwRetNameSize = sizeof(szRetName);
			dwRetValueSize = sizeof(szRetValue);
			TRACE(szRetName);
			m_wndDeviceList.AddString(szRetName);
		}

		RegCloseKey(hKey);
		m_wndDeviceList.SelectString(0,m_strDevice);
	}
	if(m_strDevice.GetLength() == 0)
	{
		m_wndDeviceList.EnableWindow(FALSE);
		m_wndStaticDevice.EnableWindow(FALSE);
//		GetDlgItem(IDC_RADIO_ORDER3)->EnableWindow(FALSE);
	}
	OnCheckLed();
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}


void CDlgConfig::OnCheckLed() 
{
	if(IsDlgButtonChecked(IDC_CHECK_LED))
	{
		if(m_strDevice.GetLength())
		{
			m_wndDeviceList.EnableWindow(TRUE);
			m_wndStaticDevice.EnableWindow(TRUE);
//			GetDlgItem(IDC_RADIO_ORDER3)->EnableWindow(TRUE);
		}
		GetDlgItem(IDC_STATIC_ORDER)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_LEVEL0)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_LEVEL1)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_LEVEL2)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_LEVEL3)->EnableWindow(TRUE);
		GetDlgItem(IDC_SCROLLLOCK0)->EnableWindow(TRUE);
		GetDlgItem(IDC_SCROLLLOCK1)->EnableWindow(TRUE);
		GetDlgItem(IDC_SCROLLLOCK2)->EnableWindow(TRUE);
		GetDlgItem(IDC_SCROLLLOCK3)->EnableWindow(TRUE);
		GetDlgItem(IDC_CAPSLOCK0)->EnableWindow(TRUE);
		GetDlgItem(IDC_CAPSLOCK1)->EnableWindow(TRUE);
		GetDlgItem(IDC_CAPSLOCK2)->EnableWindow(TRUE);
		GetDlgItem(IDC_CAPSLOCK3)->EnableWindow(TRUE);
		GetDlgItem(IDC_NUMLOCK0)->EnableWindow(TRUE);
		GetDlgItem(IDC_NUMLOCK1)->EnableWindow(TRUE);
		GetDlgItem(IDC_NUMLOCK2)->EnableWindow(TRUE);
		GetDlgItem(IDC_NUMLOCK3)->EnableWindow(TRUE);
	}
	else
	{
		m_wndDeviceList.EnableWindow(FALSE);
		m_wndStaticDevice.EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_ORDER)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_LEVEL0)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_LEVEL1)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_LEVEL2)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_LEVEL3)->EnableWindow(FALSE);
		GetDlgItem(IDC_SCROLLLOCK0)->EnableWindow(FALSE);
		GetDlgItem(IDC_SCROLLLOCK1)->EnableWindow(FALSE);
		GetDlgItem(IDC_SCROLLLOCK2)->EnableWindow(FALSE);
		GetDlgItem(IDC_SCROLLLOCK3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CAPSLOCK0)->EnableWindow(FALSE);
		GetDlgItem(IDC_CAPSLOCK1)->EnableWindow(FALSE);
		GetDlgItem(IDC_CAPSLOCK2)->EnableWindow(FALSE);
		GetDlgItem(IDC_CAPSLOCK3)->EnableWindow(FALSE);
		GetDlgItem(IDC_NUMLOCK0)->EnableWindow(FALSE);
		GetDlgItem(IDC_NUMLOCK1)->EnableWindow(FALSE);
		GetDlgItem(IDC_NUMLOCK2)->EnableWindow(FALSE);
		GetDlgItem(IDC_NUMLOCK3)->EnableWindow(FALSE);
	}
}
